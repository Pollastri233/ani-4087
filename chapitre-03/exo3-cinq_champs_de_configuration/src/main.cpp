#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig config;
    config.title = "Ma salle";
    config.width = 1200;
    config.height = 720;

    config.centered = false;     // nécessaire pour que x soit pris en compte
    config.x = 0;                // champ 1
    config.resizable = false;    // champ 2
    config.bgColor = 0xFF0000FF; // champ 3
    config.opacity = 0.5f;       // champ 4
    config.alwaysOnTop = true;   // champ 5

    NkWindow fenetre(config);
    if (!fenetre.IsValid()) {
        return 1;
    }

    while (fenetre.IsOpen()) {
        NkEvents().PollEvents();
    }

    return 0;
}