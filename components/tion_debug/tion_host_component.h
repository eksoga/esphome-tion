#pragma once
#include "esphome/core/defines.h"

#include "esphome/components/uart/uart_component.h"
#include "esphome/components/vport/vport_uart.h"
#include "../tion/tion_vport.h"

namespace esphome {
namespace tion {

template<class io_t, class component_t = Component>
class TionVPortHostComponent : public vport::VPortUARTComponent<io_t, typename io_t::frame_spec_type, component_t> {
  using super_t = vport::VPortUARTComponent<io_t, typename io_t::frame_spec_type, component_t>;

 public:
  explicit TionVPortHostComponent(io_t *io) : super_t(io) {}
  TionVPortType get_type() const { return TionVPortType::VPORT_UART; }
};

}  // namespace tion
}  // namespace esphome
