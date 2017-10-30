//
// Created by 张程易 on 30/10/2017.
//

#include "Entry.h"
#include "Scenes/DemoScene.h"

void Entry::start() {
    // TODO:: Write the Global Bootstrap Code here

}

Scene *Entry::getDefaultScene() {
    // TODO:: Return your Default Scene
    return new DemoScene();
}
