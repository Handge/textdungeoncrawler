// Monster Class

#include <iostream>
#include <string>
#include "monster.h"

Monster::Monster() { }

void Monster::randomEnemy(int player_level) {
	int rnd = rand() % 1 + 1;
	switch (rnd) {
	case 1:
		// Setting Name & Type
		name = "Bear";
		type = "bear";

		// Setting Level
		level = rand() % (player_level - 2) + 2;
		if (level <= 0) { level = 1; }

		// Setting Health
		max_health = rand() % (level * 50) + (level * 25);
		health = max_health;

		// Setting Damage
		min_damage = rand() % (level * 2) + (level);
		max_damage = rand() % (level * 3) + (level * 2);
		break;
	}
}

bool Monster::isAlive() {
	if (health >= 0) {
		return true;
	} else {
		return false;
	}
}

void Monster::setName(std::string new_name) { name = new_name; }
void Monster::setHealth(int new_health) { health = new_health; }
std::string Monster::getName() { return name; }
std::string Monster::getType() { return type; }
int Monster::getMaxHealth() { return max_health; }
int Monster::getHealth() { return health; }
int Monster::getMinDamage() { return min_damage; }
int Monster::getMaxDamage() { return max_damage; }
int Monster::getLevel() { return level; }