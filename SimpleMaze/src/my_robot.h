#ifndef __MY_ROBOT_AGENT__H
#define __MY_ROBOT_AGENT__H 

#include "enviro.h"
#include <iostream>
#include <math.h>

namespace{
    using namespace enviro;
    using namespace std;

    class Forward : public State, public AgentInterface {
        public:
        void entry(const Event& e) {}
        void during() {
            track_velocity(10,0);
            if ( sensor_value(0) < 30 || sensor_value(1) < 10 || sensor_value(2) < 10 ) {
                emit(Event(tin));
            }
        }
        void exit(const Event& e) {}
        void set_tin_name(std::string s) {tin = s;}
        string tin;
    };

    class Angular : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            rateR = 1.0;
            rateL = -1.0;
        }
        void during() {
            if (sensor_value(1) > sensor_value(2)) {
                track_velocity(0,rateR);
                if (sensor_value(0) > 60) {
                    emit(Event(tin));
                }
            } else if (sensor_value(1) == sensor_value(2)) {
                if (sensor_value(3) > sensor_value(4)) {
                    track_velocity(0, rateR);
                    if (sensor_value(0) > 60) {
                        emit(Event(tin));
                    }
                } else {
                    track_velocity(0,rateL);
                    if (sensor_value(0) > 60) {
                        emit(Event(tin));
                    }
                }
            } else {
                track_velocity(0,rateL);
                if (sensor_value(0) > 60) {
                    emit(Event(tin));
                }
            }
        }
        void exit(const Event& e) {}
        double rateR;
        double rateL;
        void set_tin_name(std::string s) { tin = s; }
        std::string tin;
    };

    class MyRobotController : public StateMachine, public AgentInterface {

    public:
    MyRobotController() : StateMachine() {
        set_initial(mForward);
        theEvent = "tin_" + std::to_string(rand()%1000);
        add_transition(theEvent, mForward, angled);
        add_transition(theEvent, angled, mForward);
        mForward.set_tin_name(theEvent);
        angled.set_tin_name(theEvent);
    }
    
    Forward mForward;
    Angular angled;
    string theEvent;
    
    };
    
    class MyRobot : public Agent {
        public:
        MyRobot(json spec, World& world) : Agent(spec, world) {
        add_process(c);
        
        }
        
        MyRobotController c;
    };
    
    DECLARE_INTERFACE(MyRobot)

}
#endif