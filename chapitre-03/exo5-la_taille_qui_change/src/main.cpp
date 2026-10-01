#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKPlatform/NkFoundationLog.h"

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
    int compteur = 0;

    auto gardeFermeture = NkEvents().AddEventCallbackGuard<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent* ev) {
            enMarche = false;
        });

    auto gardeClavier = NkEvents().AddEventCallbackGuard<NkKeyPressEvent>(
        [&](NkKeyPressEvent* ev) {
            if (ev->GetKey() == NkKey::NK_ESCAPE) {
                enMarche = false;
            }
        });

    auto gardeTaille = NkEvents().AddEventCallbackGuard<NkWindowResizeEvent>(
        [&](NkWindowResizeEvent* ev) {
            compteur++;
            NK_FOUNDATION_LOG_INFO("#%d : %u x %u", compteur,
                                   (unsigned)ev->GetWidth(),
                                   (unsigned)ev->GetHeight());
        });

    while (enMarche) {
        NkEvents().PollEvents();
    }

    return 0;
}