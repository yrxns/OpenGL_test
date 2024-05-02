#ifndef __CAMERA__
#define __CAMERA__
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.1f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f));
    ~Camera();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    
    void processKeyboard(Camera_Movement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void processMouseScroll(float yoffset);

private:
    void updateCameraVectors();

public:
    glm::vec3 mPosition{0.0f, 0.0f, 3.0f};
    glm::vec3 mUp{0.0f, 1.0f, 0.0f};
    glm::vec3 mRight{1.0f, 0.0f, 0.0f};
    glm::vec3 mFront{0.0f, 0.0f, -1.0f};
    glm::vec3 mWorldUp{0.0f, 1.0f, 0.0f};

    float sensitivity{0.05f}; // 灵敏度值。
    float yaw{-90.0f};         // 偏航角  x
    float pitch{0.0f};       // 俯仰角  y 
    float MovementSpeed{2.5f}; // 移动速度

    float mFovy{45.0f};     // 视锥体的角度
    float mAspect{800.0f / 600.0f};
    float mNear{0.1f};
    float mFar{1000.0f};

    float lastX = 800.0f / 2.0f;
    float lastY = 600.0f / 2.0f;
    bool firstMouse = true;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
};

#endif