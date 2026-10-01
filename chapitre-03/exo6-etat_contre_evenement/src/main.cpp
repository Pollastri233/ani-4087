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