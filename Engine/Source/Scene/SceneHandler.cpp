#include "EnginePCH.h"
#include <Scene/SceneHandler.h>
#include <Scene/Systems.h>

namespace Rutan::Scene
{


SceneHandler::SceneHandler()
{
}

void SceneHandler::UpdateSystems()
{
    for (auto [entity, camera] : m_Registry.view<Components::Camera>().each())
    {
        // Camera is not active, skip it
        if (!camera.Active)
        {
            continue;
        }

        if (camera.NeedUpdate)
        {
            const auto& projectMat = camera.BuildProjectionMatrix();
            const auto& viewMat = camera.BuildViewMatrix();
            m_CameraMatrix = projectMat * viewMat;
            camera.NeedUpdate = false;
        }
    }
}

Entity SceneHandler::CreateEntity()
{
    Entity entity = m_Registry.create();

    m_Registry.emplace<Components::Transform>(entity);
    
    return entity;
}

void SceneHandler::DestroyEntity(Entity entity)
{
    m_Registry.destroy(entity);
}


}