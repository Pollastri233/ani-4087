#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkEventDispatcher.h"
#include "NKPlatform/NkFoundationLog.h"
#include <chrono>
#include <fstream>
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

    std::ofstream sortie("serie.txt");
    int image = 0;

    while (enMarche) {
        NkEvents().PollEvents();
        image++;

        int dx = (int)NkInput.MouseRawDeltaX();
        sortie << image << " : rawDX=" << dx << std::endl;
        NK_FOUNDATION_LOG_INFO("image %d : rawDX=%d", image, dx);

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}