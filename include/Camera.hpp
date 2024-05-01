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
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.1f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
    ~Camera();
    glm::mat4 getViewMatrix();
    virtual glm::mat4 getProjectionMatrix();
    
    void processKeyboard(Camera_Movement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void processMouseScroll(float yoffset);

private:
    void updateCameraVectors();

public:
    glm::vec3 mPosition{0.0f, 0.0f, 0.1f};
    glm::vec3 mUp{0.0f, 1.0f, 0.0f};
    glm::vec3 mFront{0.0f, 0.0f, -1.0f};
    glm::vec3 mRight{1.0f, 0.0f, 0.0f};

    glm::vec3 mWorldUp{mUp};

    float sensitivity{0.05f}; // 灵敏度值。

    float yaw{-90.0f};         // 偏航角  x
    float pitch{0.0f};       // 俯仰角  y

    float fov{45.0f};         // 视锥体的角度

    float MovementSpeed{2.5f}; // 移动速度
};

class OrthograhicCamera : public Camera {
public:
    OrthograhicCamera(float left, float right, float top, float bottom, float near, float far);
    ~OrthograhicCamera();
    glm::mat4 getProjectionMatrix() override;

private:
    float mLeft{0.0f};
    float mRight{0.0f};
    float mTop{0.0f};
    float mBottom{0.0f};
    float mNear{0.0f};
    float mFar{0.0f};
};

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(float fovy, float aspect, float near, float far);
    ~PerspectiveCamera();
    glm::mat4 getProjectionMatrix() override;

private:
    float mFovy{45.0f};
    float mAspect{0.0f};
    float mNear{0.0f};
    float mFar{0.0f};
};

#endif