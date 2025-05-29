#pragma once

#include "esphome/core/helpers.h"

namespace esphome {
namespace tion {

inline uint8_t fan_mode_to_speed(const char *fan_mode) { return *fan_mode - '0'; }
inline uint8_t fan_mode_to_speed(const std::string &fan_mode) { return fan_mode_to_speed(fan_mode.c_str()); }
inline uint8_t fan_mode_to_speed(const optional<std::string> &fan_mode) {
  return fan_mode.has_value() ? fan_mode_to_speed(fan_mode.value()) : 0;
}

inline std::string fan_speed_to_mode(uint8_t fan_speed) { return std::string(1, '0' + fan_speed); }

}  // namespace tion
}  // namespace esphome
