#ifndef __MONITOR_ROBOT_AGENT__H
#define __MONITOR_ROBOT_AGENT__H 


#include <string>
#include <math.h>
#include "enviro.h"

namespace {

    using namespace enviro;

    // Forward class defines the forward speed and makes the robot
    // move in the forward direction.
    class Forward : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            // Similar to the camera, guards will detect if the player Agent
            // collides with them. This will emit an event that the player Agent
            // can watch for and respond to. 
            notice_collisions_with("playerAgent", [&](Event &e) {
                emit(Event("caught"));
            });
        }
        // In during() all its implemented is the forward motion and what to do when
        // the robot is about to hit a wall which is detected by the sensors.
        void during() { 
            track_velocity(5,0);
            if ( sensor_value(0) < 30 || sensor_value(1) < 8 || sensor_value(2) < 8 || 
            sensor_value(3) < 8 || sensor_value(4) < 8) {
                emit(Event(tin));
            }            
        }
        void exit(const Event& e) {}
        void tin_ring(std::string s) { tin = s; }
        std::string tin;
    };

    // Angular class defines the angular (rotating) speed and makes the
    // robot turn right or left in a randomized way. There is no forward
    // movement when this class is in-place.
    class Angular : public State, public AgentInterface {
        public:
        void entry(const Event& e) { 
            randAngSpeed = rand() % 2 == 0 ? 2 : -2; 
        }
        void during() {
            track_velocity(0, randAngSpeed);
            if ( sensor_value(0) > 60 ) {
                emit(Event(tin));
            }
        }
        void exit(const Event& e) {}
        double randAngSpeed;
        void tin_ring(std::string s) { tin = s; }
        std::string tin;        
    };

    // The monitorRobotController defines the states and transitions that the 
    // state machine will have. Once an event is passed, the controller inficates
    // to which class will the agent now respond. In this case, between Forward and 
    // Angular class.
    class monitorRobotController : public StateMachine, public AgentInterface {

        public:
        monitorRobotController() : StateMachine() {

            set_initial(moveForward);
            tin = "tin" + std::to_string(rand()%1000);
            add_transition(tin, moveForward, moveAngular); // When "tin" is heard, it moves from one class
                                                           // to another (Forward -> Angular)
            add_transition(tin, moveAngular, moveForward);
            moveForward.tin_ring(tin);
            moveAngular.tin_ring(tin);

        }

        Forward moveForward;
        Angular moveAngular;
        std::string tin;

    };

    class monitorRobot : public Agent {

        public:
        monitorRobot(json spec, World& world) : Agent(spec, world) {
            add_process(c);
        }
        monitorRobotController c;
    };

    DECLARE_INTERFACE(monitorRobot);

}

#endif