#include "Texture.h"
#include <glm/gtc/noise.hpp>
#include <stbimage/stb_image.h>
#include <algorithm>
#include <stdexcept>

CheckerTexture::CheckerTexture(float cellSize, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd)
    : cellSize(cellSize), even(even), odd(odd)
{
    if (cellSize <= 0) throw std::invalid_argument("checker cell size must be positive");
}

glm::vec3 CheckerTexture::Value(glm::vec2 uv, const glm::vec3& p) const
{
    glm::ivec3 cell(glm::floor(p / cellSize));
    return ((cell.x + cell.y + cell.z) % 2 == 0 ? even : odd)->Value(uv, p);
}

ImageTexture::ImageTexture(const std::string& filename)
{
    int channels;
    std::unique_ptr<stbi_uc, decltype(&stbi_image_free)> data(
        stbi_load(filename.c_str(), &width, &height, &channels, 3), stbi_image_free);
    if (!data) throw std::runtime_error("cannot load texture: " + filename);
    rgb.assign(data.get(), data.get() + size_t(width) * height * 3);
}

glm::vec3 ImageTexture::Value(glm::vec2 uv, const glm::vec3&) const
{
    int x = std::clamp(int(uv.x * width), 0, width - 1);
    int y = std::clamp(int((1 - uv.y) * height), 0, height - 1);
    auto i = (size_t(y) * width + x) * 3;
    return glm::vec3(rgb[i], rgb[i + 1], rgb[i + 2]) / 255.0f;
}

glm::vec3 MarbleTexture::Value(glm::vec2, const glm::vec3& p) const
{
    auto sample = p;
    float turbulence = 0, weight = 1;
    for (int octave = 0; octave < 7; ++octave) {
        turbulence += weight * glm::perlin(sample);
        sample *= 2.0f;
        weight *= 0.5f;
    }
    return glm::vec3(0.5f * (1 + std::sin(scale * p.z + 10 * std::abs(turbulence))));
}
