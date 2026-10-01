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

    fenetre.ShowMouse(false);          // cache le curseur
    fenetre.ClipMouseToClient(true);   // le confine dans la fenetre

    while (enMarche) {
        NkEvents().PollEvents();

        NK_FOUNDATION_LOG_INFO("x=%d y=%d | rawDX=%d rawDY=%d",
                               (int)NkInput.MouseX(),
                               (int)NkInput.MouseY(),
                               (int)NkInput.MouseRawDeltaX(),
                               (int)NkInput.MouseRawDeltaY());

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    // On rend la souris au systeme avant de quitter
    fenetre.ClipMouseToClient(false);
    fenetre.ShowMouse(true);
    return 0;
}