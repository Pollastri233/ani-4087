#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkMouseEvent.h"
#include "NKEvent/NkEventDispatcher.h"
#include "NKPlatform/NkFoundationLog.h"
#include <chrono>
#include <fstream>
#include <thread>

using namespace nkentseu;

// Interrupteur : true = version A (avec remise a zero au focus perdu)
//                false = version B (sans remise a zero)
const bool REMISE_A_ZERO_SANS_FOCUS = false;

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
    bool aLeFocus = true;

    int accX = 0;
    int accY = 0;
    int nbEvenements = 0;
    int totalEvenements = 0;
    long long sommeConsommee = 0;

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

    auto gardeBrut = NkEvents().AddEventCallbackGuard<NkMouseRawEvent>(
        [&](NkMouseRawEvent* ev) {
            accX += ev->GetDeltaX();
            accY += ev->GetDeltaY();
            nbEvenements++;
            totalEvenements++;
        });

    auto gardePerte = NkEvents().AddEventCallbackGuard<NkWindowFocusLostEvent>(
        [&](NkWindowFocusLostEvent* ev) {
            aLeFocus = false;
        });

    auto gardeGain = NkEvents().AddEventCallbackGuard<NkWindowFocusGainedEvent>(
        [&](NkWindowFocusGainedEvent* ev) {
            aLeFocus = true;
        });

    std::ofstream sortie("serie.txt");
    int image = 0;

    while (enMarche) {
        NkEvents().PollEvents();
        image++;

        // Remise a zero quand la fenetre n'a pas le focus
        if (REMISE_A_ZERO_SANS_FOCUS && !aLeFocus) {
            accX = 0;
            accY = 0;
        }

        int totalX = accX;
        accX = 0;
        accY = 0;
        int evts = nbEvenements;
        nbEvenements = 0;
        sommeConsommee += totalX;

        int brutX = (int)NkInput.MouseRawDeltaX();

        sortie << image << " : focus=" << (aLeFocus ? 1 : 0)
               << " brut=" << brutX
               << " acc=" << totalX
               << " evts=" << evts << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    NK_FOUNDATION_LOG_INFO("Images : %d", image);
    NK_FOUNDATION_LOG_INFO("Evenements NkMouseRawEvent recus : %d", totalEvenements);
    NK_FOUNDATION_LOG_INFO("Somme des totaux consommes (X) : %lld", sommeConsommee);
    return 0;
}