#pragma once

#include <cstdint>
#include <string>
#include <variant>

using DSValue = std::variant<bool, int64_t, double, std::string>;
