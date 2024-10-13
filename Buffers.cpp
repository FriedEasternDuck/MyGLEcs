//
// Created by rooster on 09/10/24.
//

#include "Buffers.h"

#include "Primitives.h"


Buffers::Buffers() {
    cubeBuffer = std::make_shared<BufferContainer>();
    cubeBuffer = genCubeBuffer();
}

std::shared_ptr<BufferContainer> Buffers::genCubeBuffer() {
    auto &cube = cubeBuffer;
    glGenVertexArrays(1, &cube->VAO);
    glBindVertexArray(cube->VAO);

    //VBO
    glGenBuffers(1, &cube->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, cube->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Primitives::cubeVertices.size(), Primitives::cubeVertices.data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //EBO
    glGenBuffers(1, &cube->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Primitives::cubeIndices.size(),
                 Primitives::cubeIndices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0); // Unbind the VAO

    return cube;
}

