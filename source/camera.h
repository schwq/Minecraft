#ifndef CAMERA_INCLUDE
#define CAMERA_INCLUDE
#include "include.h"

enum cameraMovement {
        Forward,
        Backward,
        Left,
        Right
};

const float CAMERASPEED =  2.5f;
const float SENSITIVITY =  0.1f;
const float CAMERAFOV   =  45.0f;

class Camera {
    public:
    float camerafov = CAMERAFOV;
    
    float Yaw;
    float Pitch;
    float CameraFov;
    float CameraSpeed;
    float MouseSensitivity;
    float XOFFSET;
    float YOFFSET;

    glm::vec3 cameraPosition;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;
    glm::vec3 WorldUp;

Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f) : cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), CameraSpeed(CAMERASPEED), MouseSensitivity(SENSITIVITY), CameraFov(CAMERAFOV){
    cameraPosition = position;
    cameraUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVecs();
}; 
    void cameraKeyboardProcess(cameraMovement direction, float deltaTime);
    void cameraMouseProcess(float xoffset, float yoffset, GLboolean pitchconstrain);
    glm::mat4 getCameraViewMat();
    
    private:
    void updateCameraVecs();
    
};

#endif 