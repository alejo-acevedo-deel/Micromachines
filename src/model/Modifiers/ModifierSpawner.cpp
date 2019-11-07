#include <random>
#include <iostream>
#include "ModifierSpawner.h"
#include <common/MsgTypes.h>
#include <model/RacingTrack.h>
#include <common/Sizes.h>
#include <common/EntityType.h>

#define TIME_OF_LIFE 6000 //10 sec

double get_uniform_number() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(mt);
}

ModifierSpawner::ModifierSpawner(float probability, RacingTrack &racing_track):
    racing_track(racing_track)
{
    this->probability = probability;
}

UpdateClient ModifierSpawner::get_update_modifiers() {
    double number = get_uniform_number();

    if (number < this->probability) {
        std::cout << "AGREGUE UN MODIFIER \n";
        return this->spawn_modifier();
    } else {
        return this->despawn_modifier();
    }
}

void ModifierSpawner::update() {
    for (auto& modifier : this->spawned_modifiers) {
        modifier.update_remaining_life();
    }
}

UpdateClient ModifierSpawner::despawn_modifier() {
    for (auto modifier = this->spawned_modifiers.begin(); modifier != this->spawned_modifiers.end();) {
        if ((*modifier).is_dead()) {
            Coordinate dead_modifier_pos = (*modifier).get_coordinate();

            int32_t x_upd = (dead_modifier_pos.get_x() * TILE_TERRAIN_SIZE * METER_TO_PIXEL) - (TILE_TERRAIN_SIZE * METER_TO_PIXEL)/2;
            int32_t y_upd = (dead_modifier_pos.get_y() * TILE_TERRAIN_SIZE * METER_TO_PIXEL) - (TILE_TERRAIN_SIZE * METER_TO_PIXEL)/2;

            this->spawned_modifiers.erase(modifier);
            std::cout << "ELIMINE UN MODIFIER \n";
            return UpdateClient({MSG_REMOVE_MODIFIER, x_upd, y_upd});
        } else {
            modifier++;
        }
    }
    return UpdateClient({NULL_UPDATE});
}

UpdateClient ModifierSpawner::spawn_modifier() {
    Coordinate modifier_spawn_pos = this->racing_track.get_random_track_position();

    float x_map = modifier_spawn_pos.get_x();
    float y_map = modifier_spawn_pos.get_y();

    this->spawned_modifiers.emplace_back(TIME_OF_LIFE, x_map, y_map);

    int32_t x_upd = (x_map * TILE_TERRAIN_SIZE * METER_TO_PIXEL) - (TILE_TERRAIN_SIZE * METER_TO_PIXEL)/2;
    int32_t y_upd = (y_map * TILE_TERRAIN_SIZE * METER_TO_PIXEL) - (TILE_TERRAIN_SIZE * METER_TO_PIXEL)/2;

    return UpdateClient({MSG_ADD_MODIFIER, TYPE_BOOST, x_upd, y_upd});
}