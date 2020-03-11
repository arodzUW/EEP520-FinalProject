MazEscape
===

Description
---

This project implements a manually-controlled "agent", or robot, which navigates through a maze all the while another automated robot moves towards a goal. If the automated robot reaches its goal without the user having completed the maze, the user loses. It has been setup as a simple video-game. The automated robot moves forward in a single axis while the user-controlled agent is 'omni-directional' with physical forces acting on it. The implementation of this project was possible due to the use of ELMA and ENVIRO packages which  have been further explained and discussed in the main directory of this repository. 

Installation
---

Please follow the installation instructions provided in the `README.md` file in the main directory of the repository. Once Docker has been installed and the command: <br />
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source - it klavins/enviro:v1.3 bash
```
has been successfully run, proceed to move to the `MazEscape` directory using `cd` and `ls` as needed. Once there, the simulation is ready to be launched. 

Usage
---

Once all the installations steps have been completed, to run the simulation run in the terminal: <br />
```bash
esm start
```
and open a web browser with `localhost` as the webpage. Finally run: <br />
```bash
enviro
``` 
At this point you should see in the `localhost` webpage the simulation running and the automated robot making it's way to the end (timer automatically starts). To manually control the omni-directional robot, use keys `W` for up, `M` for down, `A` for left, and `L` for right. If the red (automated) robot reaches the end before you have finished, you have lost. Once the automated robot reaches the end, an automatic message is displayed in the terminal indicating the time is over. Once desired, the simulation can be stopped by using `ctrl` + `c`. If need to re-run, just re-enter `enviro` into the terminal.

Functionality
---

The main functionality and control of the automated robot's movement is being controlled in a similar way as was done with the Robot in SimpleMaze; refer to SimpleMaze for more details. The manually-controlled Robot functionality is mainly being handled by one class: `PlayerAgentController`.  Below a visual peek at the contents of the class: <br /> 

```c++
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
```
By using this class and `PlayerAgent` class, the manual control of the robot is made possible. <br />

Note that the objects in the map (robots and walls) are defined in the `config.json`, `player_agent.json`, and `time_robot.json` files.

Visuals
---

Please refer to the `Images` directory in the main directory of this repository to see images depicting what you as a user should see when running the simulation. For this `MazEscape` project you should see two images: (1) an image of the maze with the two robots in it, and (2) an image of the message displayed in the terminal when the automated robot reaches the end.