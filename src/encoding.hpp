#pragma once

#include <string>
#include <vector>

#include "export.hpp"

DllExport std::string base64_encode(const std::vector<uint8_t>&);