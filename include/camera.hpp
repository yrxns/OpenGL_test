#ifndef __CAMERA__
#define __CAMERA__
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Application.hpp"


enum class Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f)) {
        mPosition = position;
        mWorldUp = worldUp;
        updateCameraVectors();
    }
    ~Camera() {};
    glm::mat4 getViewMatrix() {
        return glm::lookAt(mPosition, mPosition + mFront, mUp);
    }
    glm::mat4 getProjectionMatrix(float fovy, float aspect, float near, float far) {
        // return glm::identity<glm::mat4>();
        return glm::perspective(glm::radians(fovy), aspect, near, far);
    }
    
    void processKeyboard(Camera_Movement direction, float deltaTime) {
        float velocity = MouseSensitivity * deltaTime;
        if (direction == Camera_Movement::FORWARD)
            mPosition += mFront * velocity;
        if (direction == Camera_Movement::BACKWARD)
            mPosition -= mFront * velocity;
        if (direction == Camera_Movement::LEFT)
            mPosition -= mRight * velocity;
        if (direction == Camera_Movement::RIGHT)
            mPosition += mRight * velocity;
    }
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
        xoffset *= MovementSpeed;
        yoffset *= MovementSpeed;

        yaw   += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }
    void processMouseScroll(float yoffset) {
        mFovy -= (float)yoffset;
        if (mFovy < 1.0f) {
            mFovy = 1.0f;
        }  
        if (mFovy > 45.0f) {
            mFovy = 45.0f;
        }
    }

private:
    void updateCameraVectors() {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        mFront = glm::normalize(front);
        // also re-calculate the Right and Up vector
        mRight = glm::normalize(glm::cross(mFront, mWorldUp)); 
        mUp    = glm::normalize(glm::cross(mRight, mFront));
    }

public:
    glm::vec3 mPosition{0.0f, 0.0f, 5.0f};
    glm::vec3 mUp{0.0f, 1.0f, 0.0f};
    glm::vec3 mRight{1.0f, 0.0f, 0.0f};
    glm::vec3 mFront{0.0f, 0.0f, -1.0f};
    glm::vec3 mWorldUp{0.0f, 1.0f, 0.0f};

    float MouseSensitivity{10.0f}; // 灵敏度值。
    float yaw{-90.0f};         // 偏航角  x
    float pitch{0.0f};       // 俯仰角  y 
    float MovementSpeed{0.1f}; // 移动速度

    float mFovy{45.0f};     // 视锥体的角度

    float lastX = 800.0f / 2.0f;
    float lastY = 600.0f / 2.0f;
    bool firstMouse = true;
};

namespace cameraNS {

    Camera *camera = nullptr;int s = 3;

    void on_key(GLFWwindow *window, int key, int action, int mods) {
        std::cout << key << std::endl;
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->processKeyboard(Camera_Movement::FORWARD, gl_app->frame.deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->processKeyboard(Camera_Movement::BACKWARD, gl_app->frame.deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->processKeyboard(Camera_Movement::LEFT, gl_app->frame.deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->processKeyboard(Camera_Movement::RIGHT, gl_app->frame.deltaTime);
    }

    void on_mouse(int button, int action, int mods) {
        std::cout << "鼠标点击：(" << button << ", " << action << ", " << mods << ")" << std::endl;
    }

    void on_cursor(double xposIn, double yposIn) {
        std::cout << "鼠标移动：(" << xposIn << ", " << yposIn << ")" << std::endl;
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (camera->firstMouse)
        {
            camera->lastX = xpos;
            camera->lastY = ypos;
            camera->firstMouse = false;
        }

        float xoffset = xpos - camera->lastX;
        float yoffset = camera->lastY - ypos; // reversed since y-coordinates go from bottom to top

        camera->lastX = xpos;
        camera->lastY = ypos;

        camera->processMouseMovement(xoffset, yoffset);
    }

    void on_scroll(double xoffset, double yoffset) {
    std::cout << "鼠标滚轮: x offset = " << xoffset << ", y offset = " << yoffset << std::endl;
        camera->processMouseScroll(static_cast<float>(yoffset));
    }
}

#endif