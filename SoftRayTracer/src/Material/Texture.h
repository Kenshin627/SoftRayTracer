#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

class Texture {
public:
    virtual ~Texture() = default;
    virtual glm::vec3 Value(glm::vec2 uv, const glm::vec3& p) const = 0;
};

class SolidColor : public Texture {
public:
    explicit SolidColor(glm::vec3 color) : color(color) {}
    glm::vec3 Value(glm::vec2, const glm::vec3&) const override { return color; }
private:
    glm::vec3 color;
};

class CheckerTexture : public Texture {
public:
    CheckerTexture(float cellSize, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd);
    glm::vec3 Value(glm::vec2 uv, const glm::vec3& p) const override;
private:
    float cellSize;
    std::shared_ptr<Texture> even, odd;
};

class ImageTexture : public Texture {
public:
    explicit ImageTexture(const std::string& filename);
    glm::vec3 Value(glm::vec2 uv, const glm::vec3& p) const override;
private:
    int width, height;
    std::vector<unsigned char> rgb;
};

class MarbleTexture : public Texture {
public:
    explicit MarbleTexture(float scale) : scale(scale) {}
    glm::vec3 Value(glm::vec2 uv, const glm::vec3& p) const override;
private:
    float scale;
};
