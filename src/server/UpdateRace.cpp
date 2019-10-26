#include <map>
#include <string>
#include "model/Vehicle/Car.h"
#include "UpdateRace.h"

UpdateRace::UpdateRace(int32_t client_ID, int32_t key, int32_t key_state) {
    this->key = key;
    this->client_ID = client_ID;
    this->key_state = key_state;
}

void UpdateRace::update_cars(std::unordered_map<int32_t, Car>& cars) {
    if (this->key_state == KEY_PRESSED) {
        cars.at(this->client_ID).press_key(key);
    } else /*KEY_UNPRESSED*/ {
        cars.at(this->client_ID).release_key(key);
    }
}
