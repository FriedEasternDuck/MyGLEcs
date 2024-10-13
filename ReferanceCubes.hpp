//
// Created by rooster on 12/10/24.
//

#ifndef REFERANCECUBES_HPP
#define REFERANCECUBES_HPP
#include <glm/vec3.hpp>

class ReferenceCubes {
private:
    const glm::vec3 cube1Pos{0, 0, 0};
    const glm::vec3 cube2Pos{0, 0, 5};
    const glm::vec3 cube3Pos{0, 5, 0};
    const glm::vec3 cube4Pos{5, 0, 0};
    const glm::vec3 cube5Pos{-5, 0, 0};
    const glm::vec3 cube6Pos{0, -5, 0};
    const glm::vec3 cube7Pos{0, 0, -5};

public:
    ReferenceCubes() {
        cubes.push_back(cube1Pos);
        cubes.push_back(cube2Pos);
        cubes.push_back(cube3Pos);
        cubes.push_back(cube4Pos);
        cubes.push_back(cube5Pos);
        cubes.push_back(cube6Pos);
        cubes.push_back(cube7Pos);
    }

    std::vector<glm::vec3> cubes{};
};


#endif //REFERANCECUBES_HPP
