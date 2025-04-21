#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>


namespace Rutan::Scene::Components
{

struct Transform
{
    glm::vec3 Translation;
    float     Scale;
    glm::quat Rotation;
    
    // NOTE: Transform vs separate Translation, Scale and Rotation?
    Transform();
};

struct Velocity
{
    glm::vec3 Velocity;
};

struct Camera
{
    void Move(const glm::vec3& velocity);
    void Rotate(float yaw, float pitch, float roll);
    void FocusOn(const glm::vec3 location);
    const glm::mat4x4 BuildProjectionMatrix() const;
    const glm::mat4x4 BuildViewMatrix() const;

    inline glm::vec3 Forward() const { return glm::vec3(0.f, 0.f, 1.f); }
    inline glm::vec3 Up()      const { return glm::vec3(0.f, 1.f, 0.f); }
    inline glm::vec3 Right()   const { return glm::vec3(1.f, 0.f, 0.f); }

    glm::uvec2 Resolution = glm::uvec2(1920, 1080);     // TODO: What if we get a resize
    glm::vec3 Position    = glm::vec3(0.f, 0.f, -5.f);
    glm::vec3 Target      = glm::vec3(0.f, 0.f,  0.f);

    float FieldOfView     = 0.f;   // Degrees
    float NearPlane       = 0.1f;
    float FarPlane        = 1000.f;
    bool Active           = false;
    bool NeedUpdate       = true;
    // Perspective / ortographic
};

// Model     - resourceID
// Animation - resourceID
// Sound     - resourceID
// RenderObject?
// Physics
// Collider
// Script


}
