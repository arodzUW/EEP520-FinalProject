#ifndef __PLAYER_AGENT_AGENT__H
#define __PLAYER_AGENT_AGENT__H 

#include "enviro.h"

using namespace enviro;

class playerAgentController : public Process, public AgentInterface {

    public:
    playerAgentController() : Process(), AgentInterface() {}

    void init() {
        watch("keyup", [&](Event &e) {
            auto pk = e.value()["key"].get<std::string>();
            if (pk == "w") {
                xf = 0;
                yf = -f;
            } else if (pk == "m") {
                xf = 0;
                yf = f;
            } else if (pk == "a") {
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