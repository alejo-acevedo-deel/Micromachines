#ifndef MICROMACHINES_ROCKEFFECT_H
#define MICROMACHINES_ROCKEFFECT_H

#include "Effect.h"
#include "NoEffect.h"
#include <common/MsgTypes.h>

#define ROCK_EFFECT_DURATION 90 //1.5sec

class RockEffect : public Effect {

    public:
        RockEffect(): Effect(0.9f, 0.1f, 0.1f, 0.0f, ROCK_EFFECT_DURATION) {};

        std::unique_ptr<Effect> get_next_effect() override {
            return std::unique_ptr<Effect>(new NoEffect());
        }

        void send_effect_update(int32_t ID, ClientUpdater& updater) override {
            UpdateClient effect_info({MSG_COUNTDOWN, 2});
            updater.send_to(ID, effect_info);
        };
};


#endif //MICROMACHINES_ROCKEFFECT_H
