//
// Created by rooster on 10/10/24.
//

#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H
#include <memory>
#include <utility>

#include "Components.h"
#include "EntityManager.h"
#include "fwd.h"
#include "Input.h"


class World;

class System {
private:
protected:
public:
    virtual ~System() = default;
    virtual void update(World &world, double dt) =0;
};

struct ControlledEntity {
    Entity controlledEntity{0};
    PositionComponent *controlledPosition{nullptr};
    MovementComponent *controlledMovement{nullptr};
};

class MovementSystem final : public System {
private:
    KeyInput keyInput;
    MouseInput mouseInput;
    ControlledEntity activeEntity;

    //glm::vec3 cameraFront{0.0f, 0.0f, -1.0f};
    //const glm::vec3 cameraUp{0.0f, 1.0f, 0.0f};

public:
    explicit MovementSystem();

    void setControlledEntity(Entity entity, const std::shared_ptr<World> &world);

    void update(World &world, double dt) override;

    //const glm::vec3 &getCameraFront() const;
};
#endif //MOVEMENTSYSTEM_H
