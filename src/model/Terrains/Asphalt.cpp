#include <cstdint>
#include "Asphalt.h"
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include <common/EntityType.h>

Asphalt::Asphalt(int32_t x, int32_t y, int32_t rotation, int32_t ID):
    Terrain(x, y, rotation, ID)
{}

UpdateClient Asphalt::get_to_send() {
    int32_t x = METER_TO_PIXEL * ((this->map_x * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    int32_t y = METER_TO_PIXEL * ((this->map_y * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    std::vector<int32_t> update_info {MSG_SEND_TILE, this->ID, x, y, this->rotation};
    return UpdateClient(std::move(update_info));
}

void Asphalt::apply_terrain_effect(Body* wheel) {
    ((Wheel*)wheel)->restore_specs();
}

void Asphalt::set_terrain_user_data() {
    this->terrain_fixture->SetUserData(this);
}
