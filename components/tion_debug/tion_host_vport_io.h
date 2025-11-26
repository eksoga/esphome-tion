#pragma once

#include "esphome/components/vport/vport_uart.h"

#include "../tion-api/tion-api-uart-lt.h"
#include "../tion-api/tion-api-lt.h"
#include "../tion/tion_vport.h"

namespace esphome {
namespace tion {

class TionLtHostIO : public TionIO<dentra::tion_lt::TionLtUartProtocol>, public dentra::tion::TionUartReader {
 public:
  explicit TionLtHostIO() {
    this->protocol_.set_protocol_writer([this](const uint8_t *data, size_t size) { return this->write_(data, size); });
  }

  void poll() { this->protocol_.read_uart_data(this); }
  int available() override;
  bool read_array(void *data, size_t size) override;

 protected:
  std::string state_{};

  bool power_{};
  int speed_{1};
  int t_set_{20};
  int heat_{};

  bool write_(const uint8_t *data, size_t size);
  void update_state_();
};

}  // namespace tion
}  // namespace esphome
