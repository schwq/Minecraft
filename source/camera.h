#ifndef CAMERA_INCLUDE
#define CAMERA_INCLUDE
#include "include.h"

class Camera {
    public:
    
    bool firstMouseInput = true;
    float yaw = -90.0f;
    float pitch = 0.0f;
    float lastX = 800.0 / 2.0f;
    float lastY = 800.0 / 2.0f;
    float cameraFov = 45.0f;

    Camera(unsigned int cameraID, glm::vec3 cameraPosition, glm::vec3 cameraFront, glm::vec3 cameraUP);
    void cameraLookAt(glm::vec3 )
};

#endif 