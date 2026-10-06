#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

static const std::unordered_map<std::string, std::string> kReadableNames = {
    {"VULKAN", "Vulkan"},
    {"DX12", "DirectX 12"},
    {"DX11", "DirectX 11"},
    {"OPENGL", "OpenGL"},
    {"METAL", "Metal"},
    {"SOFTWARE", "Software"}
};

static std::vector<std::string> OrderForPlatform(const std::string& platform) {
    if (platform == "WINDOWS") {
        return {"VULKAN", "DX12", "DX11", "OPENGL", "SOFTWARE"};
    }
    if (platform == "MACOS") {
        return {"METAL", "OPENGL", "SOFTWARE"};
    }
    if (platform == "IOS") {
        return {"METAL", "SOFTWARE"};
    }
    if (platform == "ANDROID") {
        return {"VULKAN", "OPENGL", "SOFTWARE"};
    }
    return {"VULKAN", "OPENGL", "SOFTWARE"};
}

int main() {
    int n = 0;
    std::cin >> n;

    int ignorees = 0;
    int logiciel = 0;
    std::set<std::string> distinctReadable;

    for (int i = 0; i < n; ++i) {
        std::string name;
        std::string platform;
        int k = 0;
        std::cin >> name >> platform >> k;

        std::set<std::string> apis;
        for (int j = 0; j < k; ++j) {
            std::string api;
            std::cin >> api;
            apis.insert(api);
        }

        std::vector<std::string> order = OrderForPlatform(platform);

        for (const std::string& api : apis) {
            bool inOrder = false;
            for (const std::string& o : order) {
                if (o == api) {
                    inOrder = true;
                    break;
                }
            }
            if (!inOrder) {
                ++ignorees;
            }
        }

        std::string chosen = "SOFTWARE";
        for (const std::string& o : order) {
            if (o == "SOFTWARE") {
                continue;
            }
            if (apis.count(o) > 0) {
                chosen = o;
                break;
            }
        }

        if (chosen == "SOFTWARE") {
            ++logiciel;
        }

        const std::string& readable = kReadableNames.at(chosen);
        distinctReadable.insert(readable);

        std::cout << name << " " << readable << "\n";
    }

    std::cout << "IGNOREES " << ignorees << "\n";
    std::cout << "LOGICIEL " << logiciel << "\n";
    std::cout << "DIFFERENTES " << distinctReadable.size() << "\n";

    return 0;
}