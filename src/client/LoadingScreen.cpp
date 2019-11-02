//
// Created by javier on 2/11/19.
//

#include "LoadingScreen.h"

LoadingScreen::LoadingScreen() : showing(false){}

void LoadingScreen::hide() {
    showing = false;
}

void LoadingScreen::show() {
    showing = true;
}

void LoadingScreen::draw(Camera& camera) {
    if (showing)
        camera.drawLoadingScreen();
}
