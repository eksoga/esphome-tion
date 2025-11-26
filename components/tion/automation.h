#pragma once

#include "esphome/core/automation.h"
#include "tion_component.h"

namespace esphome {
namespace tion {

class StateTrigger : public Trigger<const dentra::tion::TionState &> {
 public:
  explicit StateTrigger(TionApiComponent *api) {
    api->add_on_state_callback([this](const auto *state) {
      if (state) {
        this->trigger(*state);
      }
    });
  }
};

// Power

template<typename... Ts> class PowerToggleAction : public Action<Ts...> {
 public:
  explicit PowerToggleAction(TionApiComponent *tion) : tion_(tion) {}

  void play(Ts... x) override {
    auto *call = this->tion_->make_call();
    call->set_power_state(!this->tion_->state().power_state);
    call->perform();
  }

 protected:
  TionApiComponent *tion_;
};

template<typename... Ts> class PowerTurnOnAction : public Action<Ts...> {
 public:
  explicit PowerTurnOnAction(TionApiComponent *tion) : tion_(tion) {}

  void play(Ts... x) override {
    auto *call = this->tion_->make_call();
    call->set_power_state(true);
    call->perform();
  }

 protected:
  TionApiComponent *tion_;
};

template<typename... Ts> class PowerTurnOffAction : public Action<Ts...> {
 public:
  explicit PowerTurnOffAction(TionApiComponent *tion) : tion_(tion) {}

  void play(Ts... x) override {
    auto *call = this->tion_->make_call();
    call->set_power_state(false);
    call->perform();
  }

 protected:
  TionApiComponent *tion_;
};

template<typename... Ts> class PowerCondition : public Condition<Ts...> {
 public:
  PowerCondition(TionApiComponent *tion, bool state) : tion_(tion), state_(state) {}
  bool check(Ts... x) override { return this->tion_->state().power_state == this->state_; }

 protected:
  TionApiComponent *tion_;
  bool state_;
};

// Heater

template<typename... Ts> class HeaterToggleAction : public Action<Ts...> {
 public:
  explicit HeaterToggleAction(TionApiComponent *tion) : tion_(tion) {}

  void play(Ts... x) override {
    auto *call = this->tion_->make_call();
    call->set_heater_state(!this->tion_->state().heater_state);
    call->perform();
  }

 protected:
  TionApiComponent *tion_;
};

template<typename... Ts> class HeaterTurnOnAction : public Action<Ts...> {
 public:
  explicit HeaterTurnOnAction(TionApiComponent *tion) : tion_(tion) {}

  void play(Ts... x) override {
    auto *call = this->tion_->make_call();
    call->set_heater_state(true);
    call->perform();
  }

 protected:
  TionApiComponent *tion_;
};

template<typename... Ts> class HeaterTurnOffAction : public Action<Ts...> {
 public:
  explicit HeaterTurnOffAction(TionApiComponent *tion) : tion_(tion) {}

  void play(Ts... x) override {
    auto *call = this->tion_->make_call();
    call->set_heater_state(false);
    call->perform();
  }

 protected:
  TionApiComponent *tion_;
};

template<typename... Ts> class HeaterCondition : public Condition<Ts...> {
 public:
  HeaterCondition(TionApiComponent *tion, bool state) : tion_(tion), state_(state) {}
  bool check(Ts... x) override { return this->tion_->state().heater_state == this->state_; }

 protected:
  TionApiComponent *tion_;
  bool state_;
};

//  Boost

template<typename... Ts> class BoostToggleAction : public Action<Ts...> {
 public:
  explicit BoostToggleAction(TionApiComponent *tion) : tion_(tion) {}

  void play(Ts... x) override { this->tion_->boost_enable(!this->tion_->api()->is_boost_running()); }

 protected:
  TionApiComponent *tion_;
};

template<typename... Ts> class BoostTurnOnAction : public Action<Ts...> {
 public:
  explicit BoostTurnOnAction(TionApiComponent *tion) : tion_(tion) {}

  void play(Ts... x) override { this->tion_->boost_enable(true); }

 protected:
  TionApiComponent *tion_;
};

template<typename... Ts> class BoostTurnOffAction : public Action<Ts...> {
 public:
  explicit BoostTurnOffAction(TionApiComponent *tion) : tion_(tion) {}

  void play(Ts... x) override { this->tion_->boost_enable(false); }

 protected:
  TionApiComponent *tion_;
};

template<typename... Ts> class BoostCondition : public Condition<Ts...> {
 public:
  BoostCondition(TionApiComponent *tion, bool state) : tion_(tion), state_(state) {}
  bool check(Ts... x) override { return this->tion_->api()->is_boost_running() == this->state_; }

 protected:
  TionApiComponent *tion_;
  bool state_;
};

// Auto

template<typename... Ts> class AutoToggleAction : public Action<Ts...> {
 public:
  explicit AutoToggleAction(TionApiComponent *tion) : tion_(tion) {}

  void play(Ts... x) override {
    auto *call = this->tion_->make_call();
    call->set_auto_state(!this->tion_->state().auto_state);
    call->perform();
  }

 protected:
  TionApiComponent *tion_;
};

template<typename... Ts> class AutoTurnOnAction : public Action<Ts...> {
 public:
  explicit AutoTurnOnAction(TionApiComponent *tion) : tion_(tion) {}

  void play(Ts... x) override {
    auto *call = this->tion_->make_call();
    call->set_auto_state(true);
    call->perform();
  }

 protected:
  TionApiComponent *tion_;
};

template<typename... Ts> class AutoTurnOffAction : public Action<Ts...> {
 public:
  explicit AutoTurnOffAction(TionApiComponent *tion) : tion_(tion) {}

  void play(Ts... x) override {
    auto *call = this->tion_->make_call();
    call->set_auto_state(false);
    call->perform();
  }

 protected:
  TionApiComponent *tion_;
};

template<typename... Ts> class AutoCondition : public Condition<Ts...> {
 public:
  AutoCondition(TionApiComponent *tion, bool state) : tion_(tion), state_(state) {}
  bool check(Ts... x) override { return this->tion_->state().auto_state == this->state_; }

 protected:
  TionApiComponent *tion_;
  bool state_;
};

// Fan Speed

template<typename... Ts> class FanSpeedSetAction : public Action<Ts...> {
 public:
  explicit FanSpeedSetAction(TionApiComponent *tion) : tion_(tion) {}

  TEMPLATABLE_VALUE(uint8_t, value)

  void play(Ts... x) override {
    auto *call = this->tion_->make_call();
    call->set_fan_speed(this->value_.value(x...));
    call->perform();
  }

 protected:
  TionApiComponent *tion_;
};

}  // namespace tion
}  // namespace esphome
