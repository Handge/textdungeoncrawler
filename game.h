// Game Class

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>

class Game {
public:
	Game();
	// Generic Functions
	bool isRunning();

	// Get Functions
	std::string getState();

	// Set Functions
	void setState(std::string);
	void setRunning(bool);

private:
	bool running;
	std::string state;
};

struct Arena {
	std::string state;

	std::string getState() { return state; }
	void setState(std::string new_state) { state = new_state; }
};

#endif GAME_H