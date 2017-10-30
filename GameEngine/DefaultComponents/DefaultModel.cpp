//
// Created by 张程易 on 29/10/2017.
//

#include "DefaultModel.h"

void DefaultModel::start() {

}

void DefaultModel::update() {

}

void DefaultModel::destroy() {

}

DefaultModel::~DefaultModel() {
    for(auto &x : meshes){
        delete x;
    }
}
