// Player Class

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

class Player {
public:
	Player();
	// Generic Functions
	void levelUp();
	bool isAlive();

	// Setting Functions
	void setName(std::string);
	void setHealth(int);
	void setStrength(int);
	void setAgility(int);
	void setIntelligence(int);
	void setPosition(int);
	void setLevel(int);
	void setMaxHealth(int);

	// Getting Functions
	std::string getName();
	int getHealth();
	int getMaxHealth();
	int getStrength();
	int getAgility();
	int getIntelligence();
	int getPosition();
	int getLevel();

private:
	// Strings
	std::string name;

	// Integers
	int health;
	int max_health;
	int strength;
	int agility;
	int intelligence;
	int level;
	int xp;
	int xp_required;
	int position;
};

struct Class {
	std::string name;
	std::string ability_name[4];
	int ability_damage[4];

	void display_abilities() {
		for (int i = 0; i < ARRAY_SIZE(ability_name); i++) {
			std::cout << "[" << i + 1 << "] " << ability_name[i] << std::endl;
		}
	}
};

#endif