#include "esphome/core/defines.h"

#ifndef USE_HOST
#error "Only for host platform"
#endif

#include "esphome/core/log.h"
#include "esphome/core/log.h"
#include "tion_host_vport_io.h"

namespace esphome {
namespace tion {

static const char *const TAG = "tion_host_io";

int TionLtHostIO::available() { return this->state_.size(); }

bool TionLtHostIO::read_array(void *data, size_t size) {
  if (size == 0) {
    return true;
  }
  if (size > this->state_.size()) {
    return false;
  }
  std::memcpy(data, this->state_.data(), size);
  this->state_ = this->state_.substr(size);
  return true;
}

bool TionLtHostIO::write_(const uint8_t *data, size_t size) {
  // ESP_LOGD(TAG, "TX: len: %zu, %s", size, format_hex_pretty(data, size).c_str());
  std::string cmd(reinterpret_cast<const char *>(data), size);
  if (cmd[cmd.size() - 1] == '\n') {
    cmd = cmd.substr(0, cmd.size() - 1);
  }
  if (cmd[cmd.size() - 1] == '\r') {
    cmd = cmd.substr(0, cmd.size() - 1);
  }
  ESP_LOGD(TAG, "TX: %s", cmd.c_str());

  if (cmd == "logenable noit") {
    // skip
  } else if (cmd == "getstate") {
    this->update_state_();
  } else if (cmd == "pon") {
    if (!this->power_ && this->speed_ == 0) {
      this->speed_ = 1;
    }
    this->power_ = true;
    this->update_state_();
  } else if (cmd == "stby") {
    this->power_ = false;
    this->update_state_();
  } else if (cmd == "set_heater_state 1") {
    this->heat_ = 1;
    this->update_state_();
  } else if (cmd == "set_heater_state 0") {
    this->heat_ = 0;
    this->update_state_();
  } else if (str_startswith(cmd, "set_speed ")) {
    const char *speed = cmd.c_str() + sizeof("set_speed ") - 1;
    this->speed_ = std::strtoul(speed, nullptr, 10);
    this->update_state_();
  } else {
    ESP_LOGW("HOST", "Unknown command: %s", cmd.c_str());
  }
  return true;
}

void TionLtHostIO::update_state_() {
  uint32_t work_time = esphome::millis() / 1000;
  this->state_ = str_sprintf(  //
      "\r\n"
      "Current Mode: %s\r\n"
      "Speed: %d\r\n"
      "Sensors T_set: %d, T_In: 20, T_out: 20\r\n"
      "PID_Value: %d %d\r\n"
      "Filter Time: 0\r\n"
      "Working Time: %" PRIu32 "\r\n"
      "Power On Time: %" PRIu32 "\r\n"
      "Error register: 0\r\n"
      "MAC: 0 0 0 0 0 0\r\n"
      "Firmware Version 0xFFFF\r\n",
      this->power_ ? "Work" : "StandBy", this->speed_, this->t_set_, this->heat_ ? 123 : 0, this->heat_, work_time,
      work_time);
}

}  // namespace tion
}  // namespace esphome
