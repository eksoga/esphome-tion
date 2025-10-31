#pragma once

#include <cinttypes>
#include <functional>

namespace dentra {
namespace tion {

// NOLINTNEXTLINE(readability-identifier-naming)
template<class data_type> struct tion_frame_t {
  uint16_t type;
  data_type data;
  constexpr static size_t head_size() { return sizeof(type); }
} __attribute__((__packed__));
using tion_any_frame_t = tion_frame_t<uint8_t[0]>;

// NOLINTNEXTLINE(readability-identifier-naming)
template<class data_type> struct tion_ble_frame_t {
  uint16_t type;
  uint32_t ble_request_id;  // always 1
  data_type data;
  constexpr static size_t head_size() { return sizeof(type) + sizeof(ble_request_id); }
} __attribute__((__packed__));

using tion_any_ble_frame_t = tion_ble_frame_t<uint8_t[0]>;

template<class frame_spec_t> class TionProtocol {
 public:
  using frame_spec_type = frame_spec_t;

  using reader_type = std::function<void(const frame_spec_t &data, size_t size)>;
  void set_protocol_reader(reader_type &&reader) { this->reader_ = std::move(reader); }

  using writer_type = std::function<bool(const uint8_t *data, size_t size)>;
  void set_protocol_writer(writer_type &&writer) { this->writer_ = std::move(writer); }

 protected:
  reader_type reader_{};
  writer_type writer_{};
};

}  // namespace tion
}  // namespace dentra
