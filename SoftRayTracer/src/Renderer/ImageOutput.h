#pragma once
#include <cstdint>
#include <filesystem>
#include <vector>

void WriteImage(const std::filesystem::path& path, int width, int height, const std::vector<uint8_t>& pixels);
