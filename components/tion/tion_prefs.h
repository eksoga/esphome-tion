#pragma once

#include "esphome/core/preferences.h"

namespace esphome {
namespace tion {

// Extension to ESPPreferenceObject with initialization detection.
class TionPreferenceObject : public ESPPreferenceObject {
 public:
  TionPreferenceObject() = default;
  TionPreferenceObject(const ESPPreferenceObject &pref)
      : ESPPreferenceObject(TionPreferenceObject::get_backend_(pref)) {}

  inline bool is_initialized() const { return this->backend_ != nullptr; }

 protected:
  static ESPPreferenceBackend *get_backend_(const ESPPreferenceObject &obj) {
    return obj.*(&TionPreferenceObject::backend_);
  }
};

}  // namespace tion
}  // namespace esphome
