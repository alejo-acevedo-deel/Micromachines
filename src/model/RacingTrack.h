#ifndef MICROMACHINES_RACINGTRACK_H
#define MICROMACHINES_RACINGTRACK_H

#include <list>
#include <memory>
#include "Box2D/Box2D.h"
#include <common/ProtocolSocket.h>
#include <model/FinishLine.h>
#include "model/Terrains/Terrain.h"
#include "ContactListener.h"
#include "StaticTrackObject.h"

class RacingTrack {
    b2World racing_track;

    float32 time_step;
    int32 velocity_iterations;
    int32 position_iterations;

    int32_t track_terrain;
    int32_t height;
    int32_t width;

    std::list<std::unique_ptr<Terrain>> terrains;
    std::list<StaticTrackObject> static_track_objects;
    FinishLine* finish_line;

    ContactListener contact_listener;

    public:
        explicit RacingTrack();

        void update();

        b2World& get_world();

        b2Body* add_body(b2BodyDef& body);

        void send(ProtocolSocket& p_socket);

        void set_track_terrain(int32_t terrain);

        void set_track_size(int32_t height, int32_t track_width);

        void add_terrain(std::unique_ptr<Terrain>&& terrain);

        void set_finish_line(Coordinate begin, Coordinate end);

        void add_static_track_object(StaticTrackObject&& object);

        ~RacingTrack();
};


#endif //MICROMACHINES_RACINGTRACK_H
