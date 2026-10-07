#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

int main() {
    const uint32_t RENDER2D = 1u;
    const uint32_t RENDER3D = 2u;
    const uint32_t TEXT = 4u;
    const uint32_t UI = 8u;
    const uint32_t SHADOW = 16u;
    const uint32_t POST_PROCESS = 32u;
    const uint32_t VFX = 64u;
    const uint32_t ANIMATION = 128u;
    const uint32_t OVERLAY = 256u;
    const uint32_t SIMULATION = 512u;
    const uint32_t OFFSCREEN = 1024u;
    const uint32_t RAYTRACING = 2048u;
    const uint32_t GPU_CULLING = 4096u;
    const uint32_t ALL = 4294967295u;

    std::unordered_map<std::string, uint32_t> table = {
        {"RENDER2D", RENDER2D}, {"RENDER3D", RENDER3D}, {"TEXT", TEXT},
        {"UI", UI}, {"SHADOW", SHADOW}, {"POST_PROCESS", POST_PROCESS},
        {"VFX", VFX}, {"ANIMATION", ANIMATION}, {"OVERLAY", OVERLAY},
        {"SIMULATION", SIMULATION}, {"OFFSCREEN", OFFSCREEN},
        {"RAYTRACING", RAYTRACING}, {"GPU_CULLING", GPU_CULLING},
        {"NONE", 0u},
        {"2D_ESSENTIALS", RENDER2D | TEXT},
        {"3D_BASE", RENDER3D | SHADOW | POST_PROCESS},
        {"DEBUG", OVERLAY | SIMULATION},
        {"ALL", ALL}
    };

    int n = 0;
    std::cin >> n;

    uint32_t value = 0;
    std::vector<std::string> inconnus;

    if (n == 0) {
        value = ALL;
    } else {
        for (int i = 0; i < n; ++i) {
            std::string name;
            std::cin >> name;
            auto it = table.find(name);
            if (it == table.end()) {
                inconnus.push_back(name);
            } else {
                value |= it->second;
            }
        }
    }

    for (const auto& s : inconnus) {
        std::cout << "INCONNU " << s << "\n";
    }

    std::cout << "VALEUR " << value << "\n";

    std::cout << "HEXA 0x" << std::uppercase << std::hex << std::setfill('0')
               << std::setw(8) << value << std::nouppercase << std::dec << "\n";

    struct Dep {
        std::string flagName;
        uint32_t flagBit;
        std::vector<std::pair<std::string, uint32_t>> deps;
    };

    std::vector<Dep> depsList = {
        {"TEXT", TEXT, {{"RENDER2D", RENDER2D}}},
        {"UI", UI, {{"RENDER2D", RENDER2D}, {"TEXT", TEXT}}},
        {"SHADOW", SHADOW, {{"RENDER3D", RENDER3D}}},
        {"OVERLAY", OVERLAY, {{"RENDER2D", RENDER2D}, {"TEXT", TEXT}}}
    };

    for (const auto& d : depsList) {
        if (value & d.flagBit) {
            for (const auto& dep : d.deps) {
                if (!(value & dep.second)) {
                    std::cout << "MANQUE " << d.flagName << " " << dep.first << "\n";
                }
            }
        }
    }

    int allumes = 0;
    uint32_t simpleFlags[] = {RENDER2D, RENDER3D, TEXT, UI, SHADOW, POST_PROCESS,
                               VFX, ANIMATION, OVERLAY, SIMULATION, OFFSCREEN,
                               RAYTRACING, GPU_CULLING};
    for (uint32_t f : simpleFlags) {
        if (value & f) {
            ++allumes;
        }
    }
    int eteints = 13 - allumes;

    std::cout << "ALLUMES " << allumes << "\n";
    std::cout << "ETEINTS " << eteints << "\n";

    return 0;
}