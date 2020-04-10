//
// Created by mehdi on 09/04/2020.
//

#include "marchglew.hh"

void MarchGlew::init() {
    if (glewInit())
        std::cerr << " Error while initializing glew";
}
