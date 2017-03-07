#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
enum class Weapon
{
	FISTS,
	GUN,
	SHOTGUN,
	REVOLVER,
	SNIPER,
	MACHINE_GUN,
	MAX
};
std::ostream& operator<< (std::ostream &os, const Weapon &weapon) {
	switch (weapon) {
	case Weapon::GUN: return os << "gun";
	case Weapon::SHOTGUN: return os << "shotgun";
	case Weapon::REVOLVER: return os << "revolver";
	case Weapon::SNIPER: return os << "sniper";
	case Weapon::MACHINE_GUN: return os << "machine gun";
	default: return os << "fists";
	}
}
class Zombie;
class Player
{
public:
	Weapon weapon;
	float precision;
	int life;
	Player() :
		weapon(static_cast<Weapon>(rand() % static_cast<int>(Weapon::MAX))),
		precision((rand() % 10) / 10.f),
		life(100) {};
	Player(const Weapon &t_weapon, float t_precision, int t_life) :
		weapon(t_weapon),
		precision(t_precision),
		life(t_life) {};
	void attack(Zombie &zombie) const;
	bool isAlive() const;
};
class Zombie
{
public:
	int distanceToPlayer;
	float speed;
	float damage;
	int life;
	Zombie() :
		distanceToPlayer(rand() % 180 + 20),
		speed((rand() % 20) / 10.f),
		damage((rand() % 20) / 10.f),
		life(100) {};
	Zombie(int t_distanceToPlayer, float t_speed, float t_damage, int t_life) :
		distanceToPlayer(t_distanceToPlayer),
		speed(t_speed),
		damage(t_damage),
		life(t_life) {};
	void attack(Player &player);
	bool isAlive() const;
};
void Player::attack(Zombie &zombie) const
{
	zombie.life -= static_cast<int>(static_cast<int>(weapon) * precision);
}
bool Player::isAlive() const
{
	return life > 0;
}
void Zombie::attack(Player &player)
{
	if (distanceToPlayer <= 0)
		player.life -= static_cast<int>(damage);
	else
		distanceToPlayer--;
}
bool Zombie::isAlive() const
{
	return life > 0;
}
int main()
{
	srand(static_cast<unsigned>(time(nullptr)));
	Player player;
	const int MAX_ZOMBIES{ 10 };
	Zombie zombies[MAX_ZOMBIES];
	std::cout << "Player\n\tinitial life: " << player.life <<
		", weapon: " << player.weapon <<
		", precision: " << player.precision << std::endl;
	std::cout << "ZOMBIES ARE COMING!" << std::endl;
	bool zombiesAreAlive;
	do {
		zombiesAreAlive = false;
		std::cout << "Player\n\tlife: " << player.life << std::endl;
		for (int i{ 0 }; i < MAX_ZOMBIES; ++i)
		{
			std::cout << "Zombie[" << i <<
				"]\n\tlife: " << zombies[i].life <<
				", distance: " << zombies[i].distanceToPlayer <<
				", speed: " << zombies[i].speed <<
				", damage: " << zombies[i].damage << std::endl;
			if (zombies[i].isAlive())
			{
				player.attack(zombies[i]);
				zombies[i].attack(player);
				zombiesAreAlive = true;
			}
		}
		std::cout << "-----------------------------------" << std::endl;
	} while (player.isAlive() && zombiesAreAlive);
	if (zombiesAreAlive)
		std::cout << "GAME OVER: Zombies ate the player's brain!" << std::endl;
	else
		std::cout << "GAME OVER: Player killed all the zombies!" << std::endl;
	return 0;
}