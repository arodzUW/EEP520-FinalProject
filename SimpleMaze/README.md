Simple Maze
===

Description
---

This project implements a robot "car" that navigates from beginning to end through a pre-defined maze with dead ends. The robot relies on the wall distance that sees on the front and sides of the car to determine where should it turn to when traveling through the maze. This implementation was made possible through the use of ELMA and ENVIRO packages which have been further explained and discussed in the main directory of this repository. Several maze configurations were tested and the robot made its way through the end. Note that on sharp turns, due to slow angular speed to avoid excessive forces acting on the object, it may be the case that the robot appears to be stuck in a turn, but it will always get back on track after a few seconds of orientation correcting. 

Installation
---

Please follow the installation instructions provided in the `README.md` file in the main directory of the repository. Once Docker has been installed and the command: <br />
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source - it klavins/enviro:v1.1 bash
```
has been successfully run, proceed to move to the `SimpleMaze` directory using `cd` and `ls` as needed. Once there, the simulation is ready to be launched. 

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
At this point you should see in the `localhost` webpage the simulation running and the robot making it's way through the maze. Once desired, the simulation can be stopped by using `ctrl` + `c`. If need to re-run, just re enter `enviro` into the terminal.

Functionality
---

The main functionality and control of the Robot's movement through the maze is being handled by two classes: `Forward` and `Angular`. Below a visual peek at the contents of both classes: <br /> 

```c++
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
```
Another controller class called `RobotController` defines the events that these two classes shown above are sending. By default the robot will move forward but once the distance between the front of the car and the next wall drops below 30, or if the angled sensors detect a distance of less than 10, an event will ementually be sent to stop moving forward and move with an angular speed (rotate). Similar logic is used inside the `Angular` class. The robot will turn either left or right (depending on which side has more clearance) and will continue to do so until the front sensor detects a space greater than 60 to the next wall. Then an event emits which makes the transition back to forward movement. <br />

Note that the objects in the map (car and walls) are defined in the `config.json` and `my_robot.json` files.