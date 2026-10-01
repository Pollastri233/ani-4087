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

    // Accumulateur : le rappel ajoute, la boucle consomme
    int accX = 0;
    int accY = 0;
    int nbEvenements = 0;     // evenements recus pendant l'image courante
    int totalEvenements = 0;  // tous les evenements recus
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

    std::ofstream sortie("serie.txt");
    int image = 0;

    while (enMarche) {
        NkEvents().PollEvents();
        image++;

        // Consommation : on prend le total et on remet a zero
        int totalX = accX;
        accX = 0;
        accY = 0;
        int evts = nbEvenements;
        nbEvenements = 0;
        sommeConsommee += totalX;

        // Valeur brute fournie par le kit, pour comparer
        int brutX = (int)NkInput.MouseRawDeltaX();

        sortie << image << " : brut=" << brutX
               << " acc=" << totalX
               << " evts=" << evts << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    NK_FOUNDATION_LOG_INFO("Images : %d", image);
    NK_FOUNDATION_LOG_INFO("Evenements NkMouseRawEvent recus : %d", totalEvenements);
    NK_FOUNDATION_LOG_INFO("Somme des totaux consommes (X) : %lld", sommeConsommee);
    return 0;
}