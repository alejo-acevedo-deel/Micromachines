//
// Created by javier on 24/10/19.
//

#include "Map.h"

void Map::draw(Camera& camera) {
    float tile_width = TILE_TERRAIN_SIZE*METER_TO_PIXEL;
    for (int i=0; i < back.width; i++)
        for (int j=0; j < back.height; j++)
            camera.drawWorldTexture(back.type, tile_width*i,
                    tile_width*j, tile_width+5, tile_width+5, 0);
    for (auto& tile : tiles){
        tile.draw(camera);
    }
}

void Map::addTile(TileInfo &info) {
    tiles.emplace_back(info);
}

void Map::setBackground(int32_t type, int32_t width, int32_t height) {
    back = {type, width, height};
}

Map::Map() : back({0, 0, 0}){}
