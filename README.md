MazEscape - EE P 520: Final Project
===

Software Engineering For Embedded Applications
---

This repository contains the full implementation of the final project developed for the EEP520 course; Software Engineering for Embedded Applications offered at the University of Washington. The project implements a user-controlled agent that navigates through a maze while other automatic agents move through the maze counting you down and monitoring the maze halls. It is the player's duty to move through the maze without before the time runs out! Please refer to the `Usage` section for more in-depth explanation on what the simulation does and the video game instructions. The user controlled robots moves omni-directional while the automated robots, some move unidirectional and other don't move at all. The implementation of this project was possible due to the use of `ELMA` and `ENVIRO` packages which are further explained in the installation section of this `README.md` file. 

Installation - MacOS
---

Please note that the instructions that follow were put together after following the process in a Mac computer. Windows computer follow similar steps but some might slightly differ; the overall process, however, remains the same for both systems. <br />

First make sure you have `git` installed in your computer (write `git` on a terminal window and run it). If not installed, installing Xcode command line tools should install git. Then create a directory for this repository in your computer and make it your working directory. Clone this repository into your computer directory by running:
```bash
git clone https://github.com/arodzUW/EEP520-FinalProject.git
cd EEP520-FinalProject
```
Now you should have all the contents of this repository in your computer. <br />
<br />
As stated, this project makes use of `ELMA` and `ENVIRO` packages. Both repositories and information on how to use them, call them, and implement them can be found in the links displayed below: <br />

- [ELMA](https://github.com/klavinslab/elma)<br />
- [ENVIRO](https://github.com/klavinslab/enviro) <br />

This next set of instructions is on how to set up your developing environment with ENVIRO/ELMA built-in without having to clone the two packages that make ENVIRO and ELMA. For this, make sure to have [Docker](https://www.docker.com) installed in your computer. Both `ELMA` and `ENVIRO` have been preloaded to a Docker image / container which makes calling these packages easier. Once Docker is installed in your computer, go to the directory where the project has been copied and simply do on the terminal window: <br />
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.4 bash
```
*Please note that at the time these projects were created ENVIRO's version 1.4 was used and that, since then, other versions might have been uploaded since then. Please refer to ENVIRO's repository for more information on the latest version and updates. Should you face compiling issues, ensure you are using a compatible ENVIRO version. <br />

Once these steps have been completed, your terminal should be running under "root@...", which means you're working from within the container. You are now ready to run this project.

Usage
---

In this video game you will attempt to escape prison! You (the round object) are a prisioner on the run. It is your job to make it to the end of the maze before the Commisioner (red-squared automated robot), who has found that you escaped, puts the prison on lockdown and you'll spent a lifetime sentence. Beware, however, the prison is full of monitoring, yet crooked, guards (blue-squared automated robots). They can tolerate seeing you running around, but they won't tolerate you touching them. Touch them, and you're back in jail where you started! Think you got what it takes? Beat the Commisioner, beat the guards... Oh!... and don't let yourself get caught by the cameras (brown-triangles in map)! Touch a camera, and the non-crooked guard who's vigilant will bring you back to where you started. Once you complete the maze (if you do), wait for the commisioner to put the prison on lockdown. This alerts all guards to focus on the inside leaving you the chance to escape.  Could you make it, or will you stay in jail forever? <br />

To run the game / simulation: in the terminal, within the `EEP520-FinalProject` directory run: <br />
```bash
cd MazEscape
esm start
```
For an in-depth explanation of what does `esm start` does, refer to ENVIRO's documentation. Simply put, it begins "broadcasting" to `localhost` webpage the simulation. To test, go to your web-browser and enter `localhost`. Now you should see a message in the screen stating: "Enviro Error: No connection. Is the server running?...". This error appears because the simulation has not yet been ran. To run the simulation, from inside the `MazEscape` directory run: <br />
```bash
enviro
```
At this point you should see in the `localhost` webpage the simulation running and the automated robots moving around. Once in the simulation, you are attempting to escape the prison and the Commisioner has already started making his way to the lockdown button.

To manually control the prisoner (circled robot) use keys `I` for moving up, `K` for down, `J` for left, and `L` for right. The simulation can be stopped at any time by using `ctrl + c` in the terminal. If need to re-run the simulation, simply run `enviro` in the terminal. 

The red automated robot is the counter. Once the robot reaches the end of the hall, if you have not yet reached your destination, you lose and a message stating that you didn't make it will appear on top of your robot. If you make it to the end, and wait until the Commisioner reaches the end, a message stating that you escaped will appear over your robot. Happy games! 

Project Functionality
===

Prisioner
---

The player agent is you, the prisioner, the user controlled robot. The `player_agent.h` file controls the functonality of the robot. Simply, the robot has one major class defining its behavior once the simulation has started: "playerAgentController". PlayerAgentController class defines what the robot should do when pressing the keys on the keyboard and at what force / direction should the robot move when the keys are pressed. The class also 'watches' for events being sent from other classes and responds to them as appropriate. For more details, please refer to the in-code comments left in the `.h` file. Below the playerAgentController's class. <br /> 

```c++
class playerAgentController : public Process, public AgentInterface {

    public:
    playerAgentController() : Process(), AgentInterface() {}

    void init() {
        watch("caught", [this](Event e) {
            teleport(-364, 270, -1.57);
        });
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
```
Note that the objects in the map (robots and walls) are defined in the `config.json`, `player_agent.json`, `camera_robot.json`, `time_robot.json`, and `monitor_robot.json` files.

The Commisioner
---

The Commisioner is the red automated robot that moves toward the end of the hall at the left in the simulation. The code name for the Commissioner is "time_robot" and all its functionality is controlled by the `time_robot.h` file. Two main classes control what the Commisioner does, moveF and Stopped. 'moveF' class controls the speed of the forward movement of the robot and 'Stoppped' controls what to do once the end of the hall is reached. For more details, please refer to the in-code comments left in the `.h` file. Below a representation of both classes.

```c++
class moveF : public State, public AgentInterface {
        public:
        void entry(const Event& e) {}
        void during() {
            track_velocity(1,0);
            if (sensor_value(0) < 3) {
                emit(Event(tin));
            }
        }
        void exit(const Event& e) {}
        void set_tin_name(std::string s) {tin = s;}
        string tin;
    };

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
```

The Guards
---

The guards are the scattered blue automated robots navigating through the map. The code name for the guards is "monitor_robot" and all of their functionality is controlled by the `monitor_robot.h` class. Two main classes control what the guards do: Forward and Angular. Forward controls the forward motion of the robot and Angular the rotating motion of the robot. For more details, please refer to the in-code comments left in the `.h` file. Below a representation of both classes.

```c++
class Forward : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            notice_collisions_with("playerAgent", [&](Event &e) {
                emit(Event("caught"));
            });
        }
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
```

The Cameras
---

The cameras are programmed differently than all the other robots given that these are static "robots" and don't need to move through the map. Using the default classes auto-generated when ENVIRO's `esm generate` function is called, the ability to detect when another objects interact with it its possible. All the functions for the camera were built in in the class: __. For more details, please refer to the in-code comments left in the `.h` file. Below a representation of the class.

```c++
class cameraRobotController : public Process, public AgentInterface {

    public:
    cameraRobotController() : Process(), AgentInterface() {}

    void init() {
        notice_collisions_with("playerAgent", [&](Event &e) {
            emit(Event("caught"));
        });
    }
    void start() {}
    void update() {}
    void stop() {}

};
```

General Information
===

Visuals
---

Please refer to the `Images` directory of this repository to see images depicting what you as a user should see when running the simulation.

Contributing
---

This project was completed as part of the final requirements for the completion of EEP520 course; ECE Department at the University of Washington. At this point, the project is not open for external contributions.

License
---

All contents of this repository are open source and uses the MIT license. Refer to the `LICENSE` file for more information.

Project Supplementary Information
===

Key Development Challenges
---

During the development of this project I faced several challenges that did took me some time to figure out. In full disclosure, and as a Chemical Engineer by education, this course was my first course ever on programming and C / C++. What is a challenge for me might not have been a challenge at all for a more experienced programmer. Please see below for a list of the major challenges faced: <br />

- Monitor robots wandering: Before having the final code as it is, I attemped to have more sensors and logic behind the control of the monitoring robots. The re-occuring problem I had was the the robots would continually get stuck around the edges or once hit a dead end, they would not turn 180 degrees to return, but simply stop moving. The problem was addressed by randomizing the left / right turns. Original logic implemented by turning the robot based on the available space left or right, did not worked. <br />

- Collision detection: It took me some time to figure out how to emit and watch for an event between different classes. I knew that part of the functionality I wanted the game to have was that if the user touches the cameras in the game or the guards, it would instantaneously return to the initial position. Being able to send that message between different classes, was not easy to solve (for me).

- Developing the maze: Although hw8 was cancelled, for it I had developed a maze with a bot that would autonomously navigate through it. Figuring out the coordinates and shape of the maze along with the program behind having a bot autonomously navigate through it was definitely a challenge.

Sources Used
---

The project was fully developed using as a baseline the pre-loaded `ENVIRO` examples along with the documentation for functionalities implementation. Other minor sources from Google searches were referenced to search for more basing functionalities and C++ documentation. 
