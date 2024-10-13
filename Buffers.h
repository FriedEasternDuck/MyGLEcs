//
// Created by rooster on 09/10/24.
//

#ifndef BUFFERS_H
#define BUFFERS_H
#include <glad/glad.h>
#include "Components.h"

enum class CoreBuffers {
    CUBE
};

class Buffers {
public:
    std::shared_ptr<BufferContainer> cubeBuffer;

    std::shared_ptr<BufferContainer> genCubeBuffer();
    Buffers();
    template<CoreBuffers T>
    void setBufferComponent(BufferContainer &bufferComponent);
};

template<>
inline void Buffers::setBufferComponent<CoreBuffers::CUBE>(BufferContainer& bufferComponent) {
    bufferComponent.VAO = cubeBuffer->VAO;
    bufferComponent.VBO = cubeBuffer->VBO;
    bufferComponent.EBO = cubeBuffer->EBO;
}


#endif //BUFFERS_H
