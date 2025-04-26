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

    void Camera::Rotate(float yaw, float pitch, float roll)
    {
        Yaw   = glm::mod(Yaw + yaw, 360.f);
        Pitch += pitch;
        Pitch = glm::clamp(Pitch, -89.9f, 89.9f);

        Forward.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Forward.y = sin(glm::radians(Pitch));
        Forward.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Forward = glm::normalize(Forward);
        Right   = glm::normalize(glm::cross(Up, Forward));

        NeedUpdate = true;
    }
    const glm::mat4x4 Camera::BuildProjectionMatrix() const
    {
        return glm::perspectiveFovLH(glm::radians(FieldOfView), (float)Resolution.x, (float)Resolution.y, NearPlane, FarPlane);
    }
    const glm::mat4x4 Camera::BuildViewMatrix() const
    {
        return glm::lookAtLH(Position, Position + Forward, Up);
    }
}