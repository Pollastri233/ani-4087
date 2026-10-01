# Exo 6 : État contre événement
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkEventDispatcher.h"
#include "NKPlatform/NkFoundationLog.h"
#include <chrono>
#include <thread>

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig config;
    config.title = "Ma salle";
    config.width = 1200;
    config.height = 720;

    NkWindow fenetre(config);
    if (!fenetre.IsValid()) {
        return 1;
    }

    bool enMarche = true;
    int images = 0;             // nombre d'images (tours de boucle)
    int compteurEtat = 0;       // images où Espace est tenue (IsKeyDown)
    int compteurEvenement = 0;  // tous les NkKeyPressEvent sur Espace

    auto gardeFermeture = NkEvents().AddEventCallbackGuard<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent* ev) {
            enMarche = false;
        });

    auto gardeClavier = NkEvents().AddEventCallbackGuard<NkKeyPressEvent>(
        [&](NkKeyPressEvent* ev) {
            if (ev->GetKey() == NkKey::NK_ESCAPE) {
                enMarche = false;
            }
            if (ev->GetKey() == NkKey::NK_SPACE) {
                compteurEvenement++;
            }
        });

    while (enMarche) {
        NkEvents().PollEvents();
        images++;
        if (NkInput.IsKeyDown(NkKey::NK_SPACE)) {
            compteurEtat++;
        }
        // environ 60 images par seconde, pour que "une image" ait un sens
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    NK_FOUNDATION_LOG_INFO("Images : %d", images);
    NK_FOUNDATION_LOG_INFO("Etat (IsKeyDown) : %d images", compteurEtat);
    NK_FOUNDATION_LOG_INFO("Evenements (NkKeyPressEvent) : %d", compteurEvenement);
    return 0;
}


## Ce que j'ai fait

J'ai écrit deux compteurs dans une boucle qui tourne à environ 60 images par seconde (pause de 16 ms à chaque tour) :

- **Compteur d'état** : à chaque image, je demande `NkInput.IsKeyDown(NkKey::NK_SPACE)`. Si Espace est enfoncée à cet instant, j'incrémente.
- **Compteur d'événements** : un callback sur `NkKeyPressEvent` incrémente à chaque événement dont la touche est Espace.

Test : je clique sur la fenêtre, j'appuie sur Espace environ une seconde, je relâche, puis j'appuie sur Échap pour afficher les nombres.

## Résultats

| Essai | Compteur d'état (images) | Compteur d'événements |
|---|---|---|
| 1 | 51 | 1 |
| 2 | 56 | 1 |
| 3 | 72 | 1 |

Le nombre d'images varie d'un essai à l'autre, parce que je ne maintiens pas la touche exactement le même temps à la main. Le nombre d'événements est toujours 1.

## Explication de l'écart

- **`IsKeyDown` lit un état.** Il répond à la question « la touche est-elle enfoncée maintenant ? ». Comme je pose la question à chaque image, le compteur grandit tant que la touche reste enfoncée. Sa valeur est proportionnelle à la durée de l'appui multipliée par le nombre d'images par seconde : environ 50 à 70 images pour une seconde à ~60 images par seconde.
- **`NkKeyPressEvent` signale un changement.** Il arrive une seule fois, au moment où la touche passe de « relâchée » à « enfoncée ». Ensuite, tant que je la maintiens, il ne se passe plus rien de nouveau, donc le compteur reste à 1, quelle que soit la durée de l'appui.

L'écart vient donc de ce que les deux compteurs ne mesurent pas la même chose : l'un mesure **combien de temps** la touche est tenue, l'autre **combien de fois** elle a été pressée.

## Observation sur les répétitions du clavier

Avec une touche maintenue environ une seconde, je ne reçois qu'un seul événement. En général, le système d'exploitation envoie des appuis répétés quand on maintient une touche. Ici, je n'en vois aucun. Je n'ai pas vérifié dans le code du kit s'il les filtre ou s'il ne les transmet pas : c'est une observation, pas une explication démontrée.

## Conclusion

- Pour une action **continue** (avancer tant qu'on tient une touche, charger un tir), on lit l'**état** à chaque image avec `IsKeyDown`.
- Pour une action **ponctuelle** (sauter, ouvrir un menu, tirer une fois), on utilise l'**événement**, qui ne se déclenche qu'une fois par appui.
- Compter des événements pour mesurer une durée ne marche pas, et lire l'état pour compter des appuis non plus : un seul appui long donnerait des dizaines de comptes.

*Limites : trois essais faits à la main, avec des durées d'appui un peu différentes. C'est l'ordre de grandeur (des dizaines d'images contre 1 événement) qui compte.*