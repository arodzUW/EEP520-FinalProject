#ifndef __PLAYER_AGENT_AGENT__H
#define __PLAYER_AGENT_AGENT__H 

#include "enviro.h"
#include <vector>
#include <iostream>

using namespace enviro;
using namespace std;

class playerAgentController : public Process, public AgentInterface {

    public:
    playerAgentController() : Process(), AgentInterface() {}

    void init() {
        // This watch is looking for collisions that took place
        // between the agent and the guards or the cameras. If the
        // event "caught" is heard, the player returns to the 
        // starting point.
        watch("caught", [this](Event e) {
            teleport(-364, 270, -1.57);
        });
        // If the time_robot (Commisioner) reached the end, it'll
        // display that you did not make it.
        watch("lockdown", [this](Event e) {
            cpVect vect = position();
            double x = vect.x;
            double y = vect.y;
            if (x > 330 && y > 260) {
                label("I escaped!!!", 15, 0);
                teleport(360, 320, 1.57);
            } else {
                label("Didn't make it!", 0, 0);
                teleport(-364, 270, -1.57);
            }
        });
        watch("keyup", [&](Event &e) {
            auto pk = e.value()["key"].get<std::string>();
            if (pk == "i") {
                xf = 0;
                yf = -f;
            } else if (pk == "k") {
                xf = 0;
                yf = f;
            } else if (pk == "j") {
                xf = -f;
                yf = 0;
            } else if (pk == "l") {
                xf = f;
                yf = 0;
            } else {
                xf = 0;
                yf = 0;
            }
            omni_apply_force(xf,yf);
        });
    }
    void start() {
        xf = 0;
        yf = 0;
    }
    void update() {
        omni_damp_movement();
    }
    void stop() {}
    double xf, yf;
    const double f = 50;

};

class playerAgent : public Agent {
    public:
    playerAgent(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    playerAgentController c;
};

DECLARE_INTERFACE(playerAgent)

#endif