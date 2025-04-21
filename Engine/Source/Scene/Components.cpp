#include "EnginePCH.h"
#include <Scene/Components.h>

namespace Rutan::Scene::Components
{
    Transform::Transform()
        : Translation(0.f, 0.f, 0.f)
        , Scale(1.f)
        , Rotation(0.f, 0.f, 0.f, 0.f)
    {   
    }

    void Camera::Move(const glm::vec3& velocity)
    {
        Position += velocity;
        Target += velocity;

        // Update the GPU
        NeedUpdate = true;
    }
    const glm::mat4x4 Camera::BuildProjectionMatrix() const
    {
        return glm::perspectiveFovLH(glm::radians(FieldOfView), (float)Resolution.x, (float)Resolution.y, NearPlane, FarPlane);
    }
    const glm::mat4x4 Camera::BuildViewMatrix() const
    {
        return glm::lookAtLH(Position, Target, Up());
    }
}