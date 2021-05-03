#ifndef GAMEBASE_H
#define GAMEBASE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

//SCREEN
const int SCREEN_WIDTH = 1055;
const int SCREEN_HEIGHT = 524;

//OBSTACLE PATH
const std::string CRYSTAL_OBSTACLE = "Image/Obstacle/Crystal.png";
const std::string STONE_OBSTACLE = "Image/Obstacle/Stone.png";
const std::string BUSH_OBSTACLE = "Image/Obstacle/Bush.png";

#define POSX_SANTA 240
#define GROUND 380 

#endif // !GAMEBASE_H