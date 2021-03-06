// Rouglike Dungeon Crawler
// (c) 2018 Silas Carlson

#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
#include "game.h"
#include "player.h"
#include "functions.h"
#include "monster.h"

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

// Global Variables
Game game;
Player player;
Class player_class;
Monster monster;
Arena arena;

std::string map[] = { "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
					  " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
					  " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
					  " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
					  " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
					  " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
					  " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
					  " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
					  " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
					  " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " " };

std::string map_background[] = { " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
								 " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
								 " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
							     " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
								 " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
								 " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
								 " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
								 " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
								 " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
								 " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " " };

int map_height = 10;
int map_width = 18;

void setup_classes(int class_number) {
	clear();

	switch (class_number) {
	case 1:
		player_class.name = "Champion";
		player_class.ability_name[0] = "Savage Cleave";
		player_class.ability_name[1] = "Rapturing Strike";
		player_class.ability_name[2] = "Ravish";
		player_class.ability_name[3] = "Mammothic Smash";

		player_class.ability_damage[0] = player.getStrength() * 2;
		player_class.ability_damage[1] = player.getAgility() * 3;
		player_class.ability_damage[2] = player.getIntelligence() * 4;
		player_class.ability_damage[3] = player.getStrength() * 3;

		game.setState("main area");
		break;
		
	default:
		std::cout << "You have entered an invalid input please try again." << std::endl;
		pause();
		break;
	}
}

bool map_has_enemy() {
	bool enemy_check = false;
	for (int i = 0; i < ARRAY_SIZE(map_background); i++) {
		if (map[i] == "@") {
			enemy_check = true;
		}
	}

	return enemy_check;

}

void update_map() {
	for (int i = 0; i < ARRAY_SIZE(map_background); i++) {
		map[i] = map_background[i];
	}

	map[player.getPosition()] = "X";
}

void random_terrain() {
	for (int i = 0; i < ARRAY_SIZE(map_background); i++) {
		int rnd = rand() % 5 + 1;
		int rnd2 = rand() % 100 + 1;
		switch (rnd) {
		case 1:
			map_background[i] = ",";
			break;

		case 2:
			map_background[i] = ";";
			break;

		case 3:
			map_background[i] = ":";
			break;

		case 4:
			map_background[i] = "`";
			break;

		case 5:
			if (rnd2 >= 90) {
				map_background[i] = "@";
			} else {
				map_background[i] = "'";
			}
			break;

		default:
			map_background[i] = " ";
			break;
		}

		update_map();

	}

}

void displayMap() {
	// Draw "+===+" depending on width
	std::cout << "+";
	for (int i = 0; i < map_width; i++) {
		std::cout << "=";
	}

	// Draw the body of the map with "|" and "|" on outside
	std::cout << "+" << std::endl;
	for (int i = 0; i < map_height; i++) {
		std::cout << "|";
		for (int u = 0; u < map_width; u++) {
			std::cout << map[u + (i * map_width)];
		}
		std::cout << "|";
		std::cout << std::endl;
	}

	// Draw "+===+" depending on width
	std::cout << "+";
	for (int i = 0; i < map_width; i++) {
		std::cout << "=";
	}
	std::cout << "+" << std::endl;
}

int get_player_row() {
	for (int i = 0; i < map_height; i++) {
		for (int u = 0; u < map_width; u++) {
			if (map[u + (i * map_width)] == "X") {
				return i;
			}
		}
	}
}

void stateMachine() {
	clear();

	std::string input; // User Input
	if (game.isRunning()) {
		if (game.getState() == "creation") { // Creation Stuff
			std::cout << "Rougelike Dungeon Crawler by Silas Carlson" << std::endl;
			std::cout << "YOUR ADVENTURE AWAITS YOU" << std::endl;
			std::cout << std::endl;
			std::cout << "Pick a class" << std::endl;
			std::cout << "-([1])- Champion" << std::endl;
			std::cout << "-([2])- Wizard [ Coming Soon ]" << std::endl;
			std::cout << "-([3])- Cleric [ Coming Soon ]" << std::endl;
			std::cout << "-([4])- Rogue [ Coming Soon ]" << std::endl;
			input = get_input();

			setup_classes(atoi(input.c_str()));

		} else if (game.getState() == "main area") {
			std::string input;

			displayMap();
			std::cout << "CONTROLS [ W - UP | S - DOWN | D - RIGHT | A - LEFT ]" << std::endl;

			// Stuff
			while (!_kbhit()) {}
			char character = _getch();

			int player_row = get_player_row();

			if (character == 'w' || character == 'W') {
				if (player.getPosition() - map_width >= 0) {
					map[player.getPosition()] = " ";
					player.setPosition(player.getPosition() - map_width);
					map[player.getPosition()] = "X";
				}
			} else if (character == 's' || character == 'S') {
				if (player.getPosition() + map_width <= map_height * map_width - 1) {
					map[player.getPosition()] = " ";
					player.setPosition(player.getPosition() + map_width);
					map[player.getPosition()] = "X";
				}
			} else if (character == 'd' || character == 'D') {
				if (player.getPosition() + 1 <= player_row * map_width + (map_width - 1)) {
					map[player.getPosition()] = " ";
					player.setPosition(player.getPosition() + 1);
					map[player.getPosition()] = "X";
				}
			} else if (character == 'a' || character == 'A') {
				if (player.getPosition() - 1 >= player_row * map_width) {
					map[player.getPosition()] = " ";
					player.setPosition(player.getPosition() - 1);
					map[player.getPosition()] = "X";
				}
			}

			if (map_background[player.getPosition()] == "@") {
				game.setState("arena");
				arena.setState("encounter");
				map_background[player.getPosition()] = " ";
			}

		} else if (game.getState() == "arena") {
			std::string input;
			if (arena.getState() == "encounter") {
				monster.randomEnemy(player.getLevel());
				draw_textfile(monster.getType() + ".txt");
				std::cout << "You have encountered a level " << monster.getLevel() << " " << monster.getName() << std::endl;
				reset_pause();
				pause();
				arena.setState("arena menu");
			} else if (arena.getState() == "arena menu") {
				std::cout << "Level " << monster.getLevel() << " " << monster.getName() << std::endl;
				std::cout << "Health " << monster.getHealth() << "/" << monster.getMaxHealth() << std::endl;
				std::cout << "Damage " << monster.getMinDamage() << " - " << monster.getMaxDamage() << std::endl;
				std::cout << std::endl;
				std::cout << std::endl;
				std::cout << "Health " << player.getHealth() << "/" << player.getMaxHealth() << std::endl;
				player_class.display_abilities();
				input = get_input();

				if (input == "1" || input == "2" || input == "3" || input == "4") {
					arena.setState("player attack");
				} else {
					clear();
					std::cout << "Invalid Input!" << std::endl;
					std::cout << "You entered : " << input << std::endl;
					reset_pause(); 
					pause();
				}
			} else if (arena.getState() == "player attack") {
				int index = 0;
				if (input == "2") { index = 1; }
				else if (input == "3") { index = 2; }
				else if (input == "4") { index = 3; }

				int damage = random_number(player_class.ability_damage[index] / 2, player_class.ability_damage[index] * 2);
				std::cout << "You casted " << player_class.ability_name[index] << " which dealt " << damage << " damage" << std::endl;
				std::cout << "The " << monster.getName() << " went from " << monster.getHealth() << " health down to " << monster.getHealth() - damage << " health" << std::endl;
				monster.setHealth(monster.getHealth() - damage);

				reset_pause();
				pause();

				if (monster.isAlive()) {
					arena.setState("monster attack");
				} else {
					arena.setState("player win");
				}
			} else if (arena.getState() == "monster attack") {
				int damage = random_number(monster.getMinDamage(), monster.getMaxDamage());
				std::cout << "The " << monster.getName() << " dealt " << damage << " to you" << std::endl;
				std::cout << "Yout went from " << player.getHealth() << " health down to " << player.getHealth() - damage << " health" << std::endl;
				player.setHealth(player.getHealth() - damage);

				reset_pause();
				pause();

				if (player.isAlive()) {
					arena.setState("arena menu");
				} else {
					arena.setState("player lose");
				}
			} else if (arena.getState() == "player win") {
				std::cout << "You WIN!" << std::endl;
				reset_pause();
				pause();
			} else if (arena.getState() == "player lose") {
				std::cout << "You LOST!" << std::endl;
				reset_pause();
				pause();
			}
		}
	}
}

int main() {
	srand(time(NULL));

	game.setState("creation");
	game.setRunning(true);

	// Set Player Stats
	player.setPosition(0);
	player.setLevel(1);
	player.setStrength(10);
	player.setIntelligence(10);
	player.setAgility(10);
	player.setMaxHealth((player.getStrength() + player.getIntelligence() + player.getAgility()) * 3);
	player.setHealth(player.getMaxHealth());

	random_terrain();

	while (!map_has_enemy()) {
		random_terrain();
	}

	while (game.isRunning()) {
		stateMachine();
	}

    return 0;
}