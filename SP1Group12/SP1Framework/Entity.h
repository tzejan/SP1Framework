#pragma once
#include "Position.h"
class Entity{
public:
	Entity::Entity();
	Entity::~Entity();

	virtual void Entity::move();

	int Entity::get_hp(void);
	void set_hp(int);

	int get_dmg(void);
	void set_dmg(int);

	int get_def(void);
	void set_def(int);

private:
	Position EntityPos;
	int hp, dmg, def;

};

