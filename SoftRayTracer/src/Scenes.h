#pragma once
#include "Renderer/RayTracer.h"
#include <filesystem>
#include <string>

void BuildScene(RayTracer& renderer, const std::string& name, float aspect, const std::filesystem::path& earthMap);
