#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch) {
    mPosition = position;
    mWorldUp = worldUp;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

Camera::~Camera() {}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::identity<glm::mat4>();
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = sensitivity * deltaTime;
    glm::vec3 front = glm::cross(mUp, mRight);
    if (direction == Camera_Movement::FORWARD)
        mPosition += front * velocity;
    if (direction == Camera_Movement::BACKWARD)
        mPosition -= front * velocity;
    if (direction == Camera_Movement::LEFT)
        mPosition -= mRight * velocity;
    if (direction == Camera_Movement::RIGHT)
        mPosition += mRight * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= sensitivity;
    yoffset *= sensitivity;

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

void Camera::processMouseScroll(float yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f) {
        fov = 1.0f;
    }  
    if (fov > 45.0f) {
        fov = 45.0f;
    }
}

void Camera::updateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    mFront = glm::normalize(front);
    // also re-calculate the Right and Up vector
    mRight = glm::normalize(glm::cross(mFront, mWorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    mUp    = glm::normalize(glm::cross(mRight, mFront));
}

OrthograhicCamera::OrthograhicCamera(float left, float right, float top, float bottom, float near, float far) {
    mLeft = left;
    mRight = right;
    mTop = top;
    mBottom = bottom;
    mNear = near;
    mFar = far;
}

OrthograhicCamera::~OrthograhicCamera() {}

glm::mat4 OrthograhicCamera::getProjectionMatrix() {
    return glm::ortho(mLeft, mRight, mBottom, mTop, mNear, mFar);
}

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float near, float far) {
    mFovy = fovy;
    mAspect = aspect;
    mNear = near;
    mFar = far;
}

PerspectiveCamera::~PerspectiveCamera() {}

glm::mat4 PerspectiveCamera::getProjectionMatrix() {
    return glm::perspective(glm::radians(fov), mAspect, mNear, mFar);
}