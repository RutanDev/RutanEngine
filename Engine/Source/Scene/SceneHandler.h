#include <entt/entt.hpp>
#include <Scene/Components.h>

namespace Rutan::Scene
{

typedef entt::entity Entity;


// - Handling all the entities
// - Updating the systems


class SceneHandler
{
public:
    SceneHandler();
    ~SceneHandler() = default;

    void UpdateSystems();

    Entity CreateEntity();
    void DestroyEntity(Entity entity);

    template<typename Component>
    inline Component& AddComponent(Entity entity) 
    {
        return m_Registry.emplace<Component>(entity);
    }
    template<typename Component>
    inline Component* GetComponent(Entity entity)
    {
        return m_Registry.try_get<Component>(entity);
    }

private:
    entt::registry m_Registry;

    // Array with all the systems - hardcoded limit to avoid vector

};

}