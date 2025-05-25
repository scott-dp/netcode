//
// Created by scott on 20.05.2025.
//
#include <iostream>
#include "../../include/Game/LocalState.h"

Player *LocalState::getMyPlayer() {
    for (auto &player : currentState.players) {
        if (player.getId() == thisPlayerId) {
            return &player;
        }
    }
    return nullptr;
}

LocalState::LocalState(int playerId) {
    auto *myPlayer = new Player(playerId, 10, 10);
    this->currentState.addPlayer(*myPlayer);
    thisPlayerId = playerId;
}

void LocalState::setGamerId(int id) {
    Player *player = getMyPlayer();
    player->setId(id);
    this->thisPlayerId = id;
}

State *LocalState::getState() {
    return &currentState;
}
