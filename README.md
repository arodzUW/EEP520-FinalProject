EE P 520: Final Project
===

Software Engineering For Embedded Applications
---

This repository contains the full implementation of the final project developed for the EEP520 course, Software Engineering for Embedded Applications offered at the University of Washington. The contents of this repository are: (1) the SimpleMaze project which, using ELMA and ENVIRO, creates a robot that navigates through a maze from beginning to end autonomously, and (2) MazEscape which also makes use of ELMA and ENVIRO but makes the user manually solve a maze while another robot counts down. If the countdown finishes before the maze has been completed, the user gets a message indicating it has lost. Please note that each of the folders on this repository hold individual `README.md` files that further expand on the project implementation, use, and development. 

Installation
---

As stated, both projects make use of ELMA and ENVIRO packages. Both repositories and information on how to use these packages can be found in the links displayed below.

[ELMA](https://github.com/klavinslab/elma)<br />
[ENVIRO](https://github.com/klavinslab/enviro) <br />

Once this full repository has been downloaded, make sure to have [Docker](https://www.docker.com) installed in your computer. Both elma and enviro have been preloaded to a Docker image which makes calling these packages easier. More information can be found in ELMA and ENVIRO's repository. Once Docker is installed simply do: <br />
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source - it klavins/enviro:v1.3 bash
```
*Please note that at the time these projects were created, ENVIRO's latest version was v1.3. Please refer to ENVIRO's repository for more information on the latest version and updates. Should you face compiling issues, ensure you are using a compatible ENVIRO version.

Usage
---

Please refer to each project's individual folder for more information on how to run the code and see the robot simulation. See the details on the maze simulation in the `SimpleMaze` folder and the details for the MazEscape simulation in the `MazEscape` folder. 

Contributing
---

This project was completed as part of the final requirements for the completion of EEP520 course; ECE Department at the University of Washington. At this point, the project is not open for external contributions.

License
---

All contents of this repository are open source and uses the MIT license. Refer to the `LICENSE` file for more information.
