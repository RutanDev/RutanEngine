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
    inline void MoveForward(float velocity)  { Position += (Forward * velocity); NeedUpdate = true; }
    inline void MoveBackward(float velocity) { Position -= (Forward * velocity); NeedUpdate = true; }
    inline void MoveRight(float velocity)    { Position += (Right * velocity);   NeedUpdate = true; }
    inline void MoveLeft(float velocity)     { Position -= (Right * velocity);   NeedUpdate = true; }
    inline void MoveUp(float velocity)       { Position += (Up * velocity);      NeedUpdate = true; }
    inline void MoveDown(float velocity)     { Position -= (Up * velocity);      NeedUpdate = true; }

    void Rotate(float yaw, float pitch, float roll);

    const glm::mat4x4 BuildProjectionMatrix() const;
    const glm::mat4x4 BuildViewMatrix() const;

    glm::vec3 Position    = glm::vec3(0.f, 0.f, -5.f);
    glm::vec3 Forward     = glm::vec3(0.f, 0.f, 1.f);
    glm::vec3 Up          = glm::vec3(0.f, 1.f, 0.f);
    glm::vec3 Right       = glm::cross(Up, Forward);

    // Orientation
    float Yaw   = 90.0f;
    float Pitch = 0.0f;

    // Frustum
    glm::uvec2 Resolution = glm::uvec2(1920, 1080);     // TODO: What if we get a resize
    float FieldOfView     = 0.f;   // Degrees
    float NearPlane       = 0.1f;
    float FarPlane        = 1000.f;

    bool Active           = false;
    bool NeedUpdate       = true;   //True = update GPU
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
