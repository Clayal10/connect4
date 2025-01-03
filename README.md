# Connect 4 AI
This is a project in which you can play against an AI in connect 4.

## Details
The AI used is Minimax. 

## The Plan
This will turn into a 2d graphical game, but for now it is text based. My plan also includes creating a release version with an easily executable '.exe' file.

For graphics I will use OpenGl and GLWF since I have experience with those frameworks.

## Play Now!
I will try to keep the main branch mostly playable, so the initial release uses the fairly crummy AI that makes mistakes and needs to be led to a victory. Probably about as good as a 4 year old. (UPDATE) now about as good as an 8 year old.

This repo contains the visual studio solution, so you can boot that right up if you have MSVC installed, or you could clone it into a linux distro and build it with the included Makefile inside the connect4 directory.

### Linux Dependancies
To compile on linux, you will need to copy the files in the 'dependencies/' directory into your 'usr/include/' directory. Here is a command for that:
In Solution Directory ```sudo cp -r ./dependencies/include/* /usr/include/```

### Cross Platform Hassle
Since I am developing this on both a windows and linux machine depending on the situation, there are a few issues. These come up with the VS compiler not liking 'unsafe' C operations such as fopen. The warnings for these are going to need to be modified depending on the platform during production.
