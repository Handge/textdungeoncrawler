// Monster Class

#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>

class Monster {
public:
	// Generic Functions
	Monster();
	void randomEnemy(int);
	bool isAlive();

	// Setting Functions
	void setName(std::string);
	void setHealth(int);

	// Getting Functions
	std::string getName();
	std::string getType();
	int getMaxHealth();
	int getHealth();
	int getMinDamage();
	int getMaxDamage();
	int getLevel();

private:
	// Strings
	std::string name;
	std::string type;

	// Integers
	int max_health;
	int health;
	int min_damage;
	int max_damage;
	int level;
};

#endif MONSTER_H