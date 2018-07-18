// Player Class

#include <iostream>
#include <string>
#include "player.h"

Player::Player() { }

void Player::setName(std::string new_name) { name = new_name; }
void Player::setStrength(int new_strength) { strength = new_strength;  }
void Player::setAgility(int new_agility) { agility = new_agility; }
void Player::setIntelligence(int new_intelligence) { intelligence = new_intelligence; }
void Player::setPosition(int new_position) { position = new_position;  }
void Player::setLevel(int new_level) { level = new_level; }
void Player::setMaxHealth(int new_maxhealth) { max_health = new_maxhealth; }
std::string Player::getName() { return name;  }
int Player::getHealth() { return health; }
int Player::getMaxHealth() { return max_health; }
int Player::getStrength() { return strength; }
int Player::getAgility() { return agility; }
int Player::getIntelligence() { return intelligence; }
int Player::getPosition() { return position; }
int Player::getLevel() { return level; }

void Player::setHealth(int new_health) { 
	health = new_health;
	if (health > max_health) {
		health = max_health;
	}
}

void Player::levelUp() {
	level += 1;
	health = max_health;
}

bool Player::isAlive() {
	if (health >= 0) {
		return true;
	} else {
		return false;
	}
}