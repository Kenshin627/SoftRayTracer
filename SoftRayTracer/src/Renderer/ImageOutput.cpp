#include "ImageOutput.h"
#define STBI_WRITE_NO_STDIO
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stbimage/stb_image_write.h>
#include <fstream>
#include <stdexcept>

void WriteImage(const std::filesystem::path& path, int width, int height, const std::vector<uint8_t>& pixels)
{
    auto ext = path.extension();
    if (ext != ".png" && ext != ".ppm")
        throw std::invalid_argument("output extension must be .png or .ppm");
    std::ofstream file(path, std::ios::binary);
    if (!file) throw std::runtime_error("cannot open output: " + path.string());
    if (ext == ".ppm") {
        file << "P6\n" << width << " " << height << "\n255\n";
        file.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());
    } else {
        auto write = [](void* context, void* data, int bytes) {
            static_cast<std::ofstream*>(context)->write(static_cast<char*>(data), bytes);
        };
        if (!stbi_write_png_to_func(write, &file, width, height, 3, pixels.data(), width*3))
            throw std::runtime_error("PNG encoding failed");
    }
    file.close();
    if (!file) throw std::runtime_error("could not finish writing: " + path.string());
}
