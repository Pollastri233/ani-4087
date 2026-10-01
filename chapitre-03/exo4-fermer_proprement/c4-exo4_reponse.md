# Chapitre 3 - Exercice 4 : Fermer proprement

## Code (`src/main.cpp`)

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkKeyboardEvent.h"

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

    // Chemin 1 : clic sur la croix
    auto gardeFermeture = NkEvents().AddEventCallbackGuard<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent* ev) {
            enMarche = false;
        });

    // Chemin 2 : touche Échap
    auto gardeClavier = NkEvents().AddEventCallbackGuard<NkKeyPressEvent>(
        [&](NkKeyPressEvent* ev) {
            if (ev->GetKey() == NkKey::NK_ESCAPE) {
                enMarche = false;
            }
        });

    while (enMarche) {
        NkEvents().PollEvents();
    }

    return 0;
}
```

## Ce que j'ai observé
- La croix ferme la fenêtre et le programme s'arrête. Avec la boucle
  sur `IsOpen()` (exercice 1), elle ne la fermait pas.
- La touche Échap ferme aussi la fenêtre et arrête le programme.

## Pourquoi les deux chemins doivent aboutir au même endroit
Les deux événements (clic sur la croix, touche Échap) sont des demandes
de sortie différentes, mais le programme doit y réagir de la même
façon : les deux mettent le même booléen `enMarche` à faux, et la
boucle est la seule à décider de s'arrêter. Ainsi il n'y a qu'un seul
point de sortie : le code qui suit la boucle (nettoyage, libération des
ressources) s'exécute dans tous les cas. Si chaque chemin fermait à sa
manière, il faudrait dupliquer ce nettoyage, et il suffirait d'en
oublier un pour qu'une des sorties laisse le programme dans un état
incohérent (ressources non libérées, fenêtre à moitié fermée). Avec un
seul booléen, ajouter une troisième façon de quitter (un menu, une
touche) revient à mettre ce même booléen à faux, sans toucher au reste.

## Note
Les dossiers `include/` et `lib/` du kit sont copiés dans l'exercice
mais ne sont pas versionnés. Pour recompiler, il faut les copier depuis
le kit.