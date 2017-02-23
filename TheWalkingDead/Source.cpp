#include <iostream>
#include <string>
#include <ctime>

enum class Weapon{FISTS, GUN, SHOTGUN, REVOLVER, SNIPER, MACHINE_GUN, MAX};

int randomNumber(int min, int max) {
	int n = (rand() % (max + 1 - min)) + min;
	return n;
}
class Zombie;
class Player;
class Player {
	public:
	Weapon weapon;
	float precision;
	int life;
	void attack(Zombie&);
	bool isAlive();
};


class Zombie {
public:
	int distanceToPlayer;
	float speed;
	float damage;
	int life;
	void attack(Player&);
	bool isAlive();
};


void Player::attack(Zombie & enemigo) {
	enemigo.life = enemigo.life - ((int (weapon) * 10)*precision);
}

void Zombie::attack(Player & jugador) {
	if (distanceToPlayer <= 0) {
		jugador.life = jugador.life - damage;
	}
	else {
		distanceToPlayer--;
	}
}

bool Player::isAlive() {
	if (life > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Zombie::isAlive() {
	if (life > 0) {
		return true;
	}
	else {
		return false;
	}
}

void main() {
	Player jugador;
	Zombie arr[10];

	srand(time(nullptr));

	for (int i = 0; i < 10;i++) {
		arr[i].distanceToPlayer = randomNumber(20, 200);
		arr[i].speed = rand() % 21;
		arr[i].damage = rand() % 21;
		arr[i].life = randomNumber(1, 100);
	}

	jugador.weapon = Weapon(rand() % 6);
	jugador.precision = rand() % 2;
	jugador.life = rand() % 101;

	bool zombiesAreAlive = true;

	do {

		for (int i = 0; i < 10;i++) {
			if (arr[i].isAlive == true && jugador.isAlive == true) {
				jugador.attack(arr[i]);
				arr[i].attack(jugador);
				break;
			}
			else {
				zombiesAreAlive = false;
			}

		} while (jugador.isAlive == true && zombiesAreAlive == true)
			if (jugador.isAlive == true) {
				std::cout << "WIN" << std::endl;
			}
			else {
				std::cout << "YOU LOSE" << std::endl;
			}
	}
}