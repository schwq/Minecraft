#include "camera.h"

glm::mat4 Camera::getCameraViewMat() {
    return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

void Camera::cameraKeyboardProcess(cameraMovement direction, float deltaTime){
    float velocity = deltaTime * CameraSpeed;
    if(direction == Forward) cameraPosition += cameraFront * velocity;
    if(direction == Backward) cameraPosition -= cameraFront * velocity;
    if(direction == Left) cameraPosition -= cameraRight * velocity;
    if(direction == Right) cameraPosition += cameraRight * velocity;
}

void Camera::cameraMouseProcess(float xoffset, float yoffset, GLboolean pitchconstrain){
    xoffset *= SENSITIVITY;
    yoffset *= SENSITIVITY;
    Yaw += xoffset;
    Pitch += yoffset;
    XOFFSET = xoffset;
    YOFFSET = yoffset;

    if(pitchconstrain){
    if (Pitch > 89.0f) Pitch = 89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;
    }

    Camera::updateCameraVecs();
}

void Camera::updateCameraVecs() {
    glm::vec3 frontView;
    frontView.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    frontView.y = sin(glm::radians(Pitch));
    frontView.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    cameraFront = glm::normalize(frontView);
    cameraRight = glm::normalize(glm::cross(cameraFront, WorldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}
