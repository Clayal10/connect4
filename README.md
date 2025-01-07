# Connect 4 AI
This is a project in which you can play against an AI in connect 4.
Windows Download: https://isoptera.lcsc.edu/~cshumaker/connect_4.zip

## Details
The AI used is Minimax. This is an interesting selection algorithm for this game due to the many, many branching paths that can be taken. Each turn has 7 options for play with a max number of 42 turns. This is a bit too much to compute for each turn (depending on your computer), so for playability on non-optimal machines, the algorithm will only traverse through 8 possible turns per action. It is easy to boost this number (and theoretically the intelligence) by modifying it in the 'minimax' function in game.cpp.

## The Plan
Currently a 2d Connect 4 game. The graphics are a bit rough, but that will be improved on for future releases. 

For graphics I will use OpenGl and GLWF since I have experience with those frameworks.

## Play Now!
Curretly graphically playable.

This repo contains the visual studio solution, so you can boot that right up if you have MSVC installed, or you could clone it into a linux distro and build it with the included Makefile inside the connect4 directory.
### Controls
The start screen will display the controls in the terminal.

### Linux Dependancies
To compile on linux, you will need to install a few OpenGL dependancies. You can do this with this command:
```
sudo apt install libglew-dev libglm-dev libglfw3-dev
```
