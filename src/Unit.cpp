#include "Unit.hpp"

Unit::Unit(float max_health) : max_health(max_health), health(max_health) {

}

void Unit::takeDamage(float damage_amount) {
    if (isKillingBlow(damage_amount)) {
        die();
    } else {
        changeHealthBy(-damage_amount);
    }
}

void Unit::healFor(float heal_amount) {
    if (wouldBeOverFullHealth(heal_amount)) {
        setHealth(getMaxHealth());
    } else {
        changeHealthBy(heal_amount);
    }
}

bool Unit::isKillingBlow(float damage_amount) {
    return ((getHealth() - damage_amount) < 0);
}

bool Unit::wouldBeOverFullHealth(float heal_amount) {
    return ((getHealth() + heal_amount) > max_health);
}

void Unit::changeHealthBy(float amount) {
    setHealth(getHealth() + amount);

}

void Unit::attack(Unit& target, float damage_amount) {
    target.takeDamage(damage_amount);
}

void Unit::die() {
    setHealth(0);
}

bool Unit::isDead() {
    return health <= 0;
}

float Unit::getHealth() {
    return health;
}

float Unit::getMaxHealth() {
    return max_health;
}

void Unit::setHealth(float health) {
    this->health = health;
}

void Unit::setMaxHealth(float max_health) {
    this->max_health = max_health;
}
