MazEscape - EE P 520: Final Project
===

Software Engineering For Embedded Applications
---

This repository contains the full implementation of the final project developed for the EEP520 course; Software Engineering for Embedded Applications offered at the University of Washington. The project hereby presented and developed implements a user-controlled agent, or robot, which navigates through a maze. At the same time, there is another automated agent that "counts down" by moving towards a goal along with another automated "monitoring-robot" which is the user's goal to avoid touching. Overall, during the simulation, it is the user's goal to reach the end of the maze before the "count-down" robot reaches the goal and without touching the auto-monitoring robots. Further information on the game is discussed in the 'Usage' section. The auto-controlled robots move in a single axis while the user-controlled robot moves in an 'omni-directional' way. The implementation of this project was possible due to the use of ELMA and ENVIRO packages which are further explained in the installation section of this `README.md` file. 

Installation - MacOS
---

First make sure you have `git` installed in your computer (write `git` on the terminal and run it). If not installed, installing Xcode command line tools should install git. Then create a directory for this repository and make it your working directory. Clone this repository into your computer directory by running:
```bash
git clone https://github.com/arodzUW/EEP520-FinalProject.git
cd EEP520-FinalProject
```
Now you should have all the contents of this repository in your computer. <br />
<br />
As stated, this project makes use of `ELMA` and `ENVIRO` packages. Both repositories and information on how to use them, call them, and implement them can be found in the links displayed below: <br />

- [ELMA](https://github.com/klavinslab/elma)<br />
- [ENVIRO](https://github.com/klavinslab/enviro) <br />

This next set of instructions is on how to set up your developing environment with ENVIRO/ELMA built-in without having to clone these two packages. For this, make sure to have [Docker](https://www.docker.com) installed in your computer. Both `ELMA` and `ENVIRO` have been preloaded to a Docker image /container which makes calling these packages easier. Once Docker is installed in your computer, simply do: <br />
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.3 bash
```
*Please note that at the time these projects were created, ENVIRO's latest version was v1.3. Please refer to ENVIRO's repository for more information on the latest version and updates. Should you face compiling issues, ensure you are using a compatible ENVIRO version. <br />

Once these steps have been completed, your terminal should be running under "root@...", which means you're working from within the container. You are now ready to run this project.

Usage
---

To run the simulation in the terminal, within the `EEP520-FinalProject` directory run: <br />
```bash
cd MazEscape
esm start
```
For an in-depth explanation of what does `esm start` does, refer to ENVIRO's documentation. Simply put, it begins "broadcasting" to `localhost` webpage the simulation. To test, go to your web-browser and enter `localhost`. Now you should see a message in the screen stating: "Enviro Error: No connection. Is the server running?...". This error appears because the simulation has not yet been ran. To run the simulation, from inside the `MazEscape` directory run: <br />
```bash
enviro
```
At this point you should see in the `localhost` webpage the simulation running and the automated robots moving around. Once in the simulation, you are attempting to escape the prison. The Commissioner has found your cell empty and is on it's way to put the entire prison cell in lockdown (red automated robot). It is your job to reach the end of the maze without being caught by the police officers making their rounds. If you let a police officer touch you, you'd automatically go back to jail. If you let the Commissioner reach the end of the hall, you lose. What's it gonna be?

To manually control the prisoner (circled robot) use keys `W` for moving up, `M` for down, `A` for left, and `L` for right. The simulation can be stopped at any time by using `ctrl + c`. If need to re-run the simulation, simply run `enviro` in the terminal. 

The red automated robot is the counter. Once the robot reaches the end of the hall, if you have not yet reached your destination, you lose. 

Functionality
---

The code has been properly commented throughout the `.h` files with in-code explanation of what bits of the code are doing. All automated robots are controlled in a similar fashion. The manually-controlled Robot functionality is mainly being handled by one class: `PlayerAgentController`.  Below a visual peek at the contents of the class: <br /> 

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

Please refer to the `Images` directory of this repository to see images depicting what you as a user should see when running the simulation.

Contributing
---

This project was completed as part of the final requirements for the completion of EEP520 course; ECE Department at the University of Washington. At this point, the project is not open for external contributions.

License
---

All contents of this repository are open source and uses the MIT license. Refer to the `LICENSE` file for more information.
