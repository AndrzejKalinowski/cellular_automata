# cellular_automata
**Conway’s Game of Life** This is an end-of-semester project for dr Gepner’s Programming 1 course at the MEiL Faculty at WUT.

## Installation, compiling , running and environment
### Environment
I'm using Ubuntu 24.04 LTS under WSL2 (WSLg required) running on Windows 11 25H2.
Compilation is done using GCC and a Makefile.
Visual Studio Code, connected to the WSL environment, is used as the editor, GIT gui and debugger.
### Installation
```
git clone https://github.com/AndrzejKalinowski/cellular_automata.git
sudo apt install gcc
sudo apt install make
sudo apt install gdb    ## compiler, omit if unused
sudo apt install libsdl2-dev
```
### Compiling
Compilation is usually performed through Visual Studio Code using tasks and extensions, but can also be done manually:
```
make
```
### Running
Also could be done through the debugger:
```
make run
```
### Debugging
Debugging is done through VS code (as almost everything else). A Task is created to compile using the Makefile. Suitable launch configuration was also created for debugging. All of this is managed though VSC gui and json files. For starting the debugger just click on the launch configuration in the run tab.

## General working principle

_todo_

## Research and Resources 
Some of the resources that I've used for making this project.

<https://pl.wikipedia.org/wiki/Gra_w_%C5%BCycie>

<https://ccfd.github.io/courses/info1_lab08.html>

<https://www.youtube.com/watch?v=FWSR_7kZuYg>

<https://www.youtube.com/watch?v=mxWkj0KiICk>
