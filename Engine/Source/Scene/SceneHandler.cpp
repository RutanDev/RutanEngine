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
    // Some systems NOT specific for your application

    // More like move every entity with: transform + velocity-components
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