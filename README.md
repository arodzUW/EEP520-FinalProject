EE P 520: Final Project
===

Software Engineering For Embedded Applications
---

This repository contains the full implementation of the final project developed for the EEP520 course, Software Engineering for Embedded Applications. The contents of this repository are: (1) the SimpleMaze project which, using ELMA and ENVIRO creates a robot that navigates through a maze, and (2) XXX which also makes use of ELMA and ENVIRO and XXX. Please note that each of the folders on this repository hold individual `README.md` files that further expand on the project implementation, use, and development. 

Installation
---

As stated, both projects make use of ELMA and ENVIRO. Both repositories and information on how to use these can be found in the links displayed below. 

Repository and further information on both can be found in the following links:

[ELMA](https://github.com/klavinslab/elma)<br />
[ENVIRO](https://github.com/klavinslab/enviro) <br />

Once this full repository has been downloaded, make sure to have [Docker](https://www.docker.com) installed in your computer. Both elma and enviro have been preloaded to a Docker image which makes calling these packages easier. More information can be found in ELMA and ENVIRO's repo. Once Docker is installed simply do: <br />
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source - it klavins/enviro:v1.1 bash
```
*Please note that at the time this file was created, ENVIRO's latest version was v1.1. Please refer to ENVIRO's repository for more information on the latest version and updates.

Usage
---

Please refer to each project's individual folder for more information on how to run the code and see the robot simulation. See the details on the maze simulation in the `SimpleMaze` folder and the details for the XXX simulation in the `XXX` folder. 

Contributing
---

This project was completed as part of the final requirements for the completion of EEP520 course. At this point, the project is not open for external contributions.

License
---

All contents of this repository are open source and uses the MIT license. 
