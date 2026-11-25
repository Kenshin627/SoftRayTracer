#include "Scenes.h"
#include "Renderer/ImageOutput.h"
#ifdef SOFTRAY_SDL
#include "window/Window.h"
#endif
#include <charconv>
#include <iostream>
#include <stdexcept>

static int Number(const std::string& value, int min, int max)
{
    int result;
    auto end = value.data() + value.size();
    auto parsed = std::from_chars(value.data(), end, result);
    if (parsed.ec != std::errc() || parsed.ptr != end || result < min || result > max)
        throw std::invalid_argument("number outside supported range: " + value);
    return result;
}

int main(int argc, char** argv)
{
    try {
        int width = 600, height = 600, samples = 50, depth = 50, seed = 1;
        bool importance = true;
        std::string scene = "smoke";
        std::filesystem::path output;
        auto earth = std::filesystem::absolute(argv[0]).parent_path() / "assets" / "earthmap.jpg";
        for (int i = 1; i < argc; ++i) {
            std::string option = argv[i];
            if (option == "--help") {
                std::cout << "SoftRayTracer [--scene random|textures|motion|quads|smoke|cornell|final]\n"
                             "  [--width N] [--height N] [--spp N] [--depth N] [--seed N]\n"
                             "  [--sampling mixture|material] [--earth FILE] [--output FILE.png|FILE.ppm]\n";
                return 0;
            }
            if (++i == argc) throw std::invalid_argument("missing value for " + option);
            std::string value = argv[i];
            if (option == "--scene") scene = value;
            else if (option == "--output") output = value;
            else if (option == "--earth") earth = value;
            else if (option == "--width") width = Number(value, 1, 16384);
            else if (option == "--height") height = Number(value, 1, 16384);
            else if (option == "--spp") samples = Number(value, 1, 1000000);
            else if (option == "--depth") depth = Number(value, 1, 256);
            else if (option == "--seed") seed = Number(value, 0, 2147483647);
            else if (option == "--sampling" && (value == "material" || value == "mixture"))
                importance = value == "mixture";
            else throw std::invalid_argument("unknown option or value: " + option + " " + value);
        }

        Tool::Generator().seed(seed);
        auto rt = std::make_shared<RayTracer>(width, height, depth, samples, seed);
        BuildScene(*rt, scene, float(width)/height, earth);
        rt->SetImportanceSampling(importance);
#ifdef SOFTRAY_SDL
        if (output.empty()) {
            Window window("SoftRayTracer", width, height);
            window.SetRayTracer(rt);
            window.Run();
            return 0;
        }
#else
        if (output.empty()) output = "render.png";
#endif
        WriteImage(output, width, height, rt->Render());
        std::cout << scene << " " << width << "x" << height << " " << samples << " spp -> " << output << "\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "SoftRayTracer: " << e.what() << "\n";
        return 1;
    }
}
