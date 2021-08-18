#include "Entity.h"

Entity::Entity() {
	hp = 0, dmg = 0, def = 0;
}

Entity::~Entity() {

}

void Entity::move() {

}

int Entity::get_hp(void) {
	return hp;
}
void Entity::set_hp(int a) {
	hp = a;
}

int Entity::get_dmg(void) {
	return dmg;
}
void Entity::set_dmg(int a) {
	dmg = a;
}

int Entity::get_def(void) {
	return def;
}
void Entity::set_def(int a) {
	def = a;
}