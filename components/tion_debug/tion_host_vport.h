#pragma once
#include "esphome/core/defines.h"

#include "tion_host_component.h"
#include "tion_host_vport_io.h"

namespace esphome {
namespace tion {

class TionHostVPort : public TionVPortHostComponent<TionLtHostIO> {
 public:
  constexpr static const char *TAG = "tion_host";
  explicit TionHostVPort(TionLtHostIO *io) : TionVPortHostComponent(io) {}
  void dump_config() override { VPORT_UART_LOG("Tion Host"); }
  void set_api(void *api) {}
};

}  // namespace tion
}  // namespace esphome
