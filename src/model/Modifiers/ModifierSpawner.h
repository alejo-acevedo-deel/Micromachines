#ifndef MICROMACHINES_MODIFIERSPAWNER_H
#define MICROMACHINES_MODIFIERSPAWNER_H

#include "Modifier.h"
#include <model/RacingTrack.h>

class ModifierSpawner {

    float probability;
    RacingTrack& racing_track;
    std::vector<Modifier> spawned_modifiers;

    private:
        UpdateClient spawn_modifier();

        UpdateClient despawn_modifier();

    public:
        ModifierSpawner(float probability, RacingTrack& racing_track);

        UpdateClient get_update_modifiers();

        void update();
};


#endif //MICROMACHINES_MODIFIERSPAWNER_H