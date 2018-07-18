// Game Class

#include <iostream>
#include <string>
#include "game.h"
#include "player.h"

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

Game::Game() { }

bool Game::isRunning() { return running; }
std::string Game::getState() { return state; }
void Game::setState(std::string new_state) { state = new_state; }
void Game::setRunning(bool new_running) { running = new_running; }