#ifndef __TIME_ROBOT_AGENT__H
#define __TIME_ROBOT_AGENT__H 

#include "enviro.h"
#include <iostream>
#include <math.h>

namespace {
    using namespace enviro;
    using namespace std;

    // This class makes the robot move forward. Same functionality as
    // Forward class in monitor_robot.
    class moveF : public State, public AgentInterface {
        public:
        void entry(const Event& e) {}
        void during() {
            track_velocity(5,0);
            if (sensor_value(0) < 3) {
                emit(Event(tin));
            }
        }
        void exit(const Event& e) {}
        void set_tin_name(std::string s) {tin = s;}
        string tin;
    };

    // Once the robot reaches the end of the hall, you want it to stop moving.
    // This class stops the robot and lets the player-agent, through an Event,
    // that the prison is in lockdown. 
    class Stopped : public State, public AgentInterface {
        public:
        void entry(const Event& e) {}
        void during() {
            emit(Event("lockdown"));
            track_velocity(0,0);
            label(s, -5, 5);
        }
        void exit(const Event& e) {}
        std::string s = "Prison in Lockdown!!";
    };

    // The timeRobotController class simply defines the states and transitions of
    // the state machine
    class timeRobotController : public StateMachine, public AgentInterface {
        public:
        timeRobotController() : StateMachine () {
            set_initial(moveForward);
            theEvent = "tin_" + std::to_string(rand()%1000);
            add_transition(theEvent, moveForward, stop);
            moveForward.set_tin_name(theEvent);
        }

        moveF moveForward;
        Stopped stop;
        string theEvent;
    };

    class timeRobot : public Agent {
        public:
        timeRobot(json spec, World& world) : Agent(spec, world) {
            add_process(c);
        }

        timeRobotController c;
    };
    
    DECLARE_INTERFACE(timeRobot)
}
#endif