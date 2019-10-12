#include <common/Socket.h>
#include <string>
#include <iostream>
#include "Player.h"

Player::Player(Socket&& socket, GameMode game_mode, std::string username, std::string match_name):
    socket(std::move(socket)),
    game_mode(game_mode)
{
    this->username = username;
    this->match_name = match_name;
}

Player::Player(Player&& other) noexcept:
    socket(std::move(other.socket)),
    game_mode(other.game_mode),
    username(other.username),
    match_name(other.match_name)
{}

bool Player::is_on_join_mode() {
    return this->game_mode.is_join();
}

std::string Player::get_match_name() {
    return this->match_name;
}

std::string Player::get_username() {
    return this->username;
}

void Player::send(std::string& msg) {
    this->socket.send((uint8_t*)msg.data(), msg.length());
}

uint8_t Player::receive_option() {
    uint8_t option;
    this->socket.receive(&option, 1);
    return option;
}


