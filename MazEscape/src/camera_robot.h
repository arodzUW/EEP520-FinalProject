#ifndef __CAMERA_ROBOT_AGENT__H
#define __CAMERA_ROBOT_AGENT__H 

#include "enviro.h"

using namespace enviro;

class cameraRobotController : public Process, public AgentInterface {

    public:
    cameraRobotController() : Process(), AgentInterface() {}

    void init() {
        // By using notice_collisions_with it is possible to emit an
        // event that another class can watch and catch. In this case,
        // all the cameras care about is collisions with the playerAgent. 
        // Collisions with the guards (should it happen) won't trigger anything.
        notice_collisions_with("playerAgent", [&](Event &e) {
            emit(Event("caught"));
        });
    }
    void start() {}
    void update() {}
    void stop() {}

};

class cameraRobot : public Agent {
    public:
    cameraRobot(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    cameraRobotController c;
};

DECLARE_INTERFACE(cameraRobot)

#endif