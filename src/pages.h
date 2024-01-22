#pragma once

#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>
#include "board.h"

extern double lastUpdateTime;
extern Color bgcolor;
extern Color buttoncolor;
extern Color textcolor;
extern Game game;
extern int rotationMain;
extern float fSpeed;
extern bool playMusic;
extern Music music;

bool EventTriggered(double interval);
void playGame();
void openSettings();
void menu();

 