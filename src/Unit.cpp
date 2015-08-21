#include "Unit.hpp"

Unit::Unit(double max_health) : max_health(max_health), health(max_health) {

}

void Unit::takeDamage(double damage_amount) {
    if (isKillingBlow(damage_amount)) {
        die();
    } else {
        changeHealthBy(-damage_amount);
    }
}

void Unit::healFor(double heal_amount) {
    if (wouldBeOverFullHealth(heal_amount)) {
        setHealth(getMaxHealth());
    } else {
        changeHealthBy(heal_amount);
    }
}

bool Unit::isKillingBlow(double damage_amount) {
    return ((getHealth() - damage_amount) < 0);
}

bool Unit::wouldBeOverFullHealth(double heal_amount) {
    return ((getHealth() + heal_amount) > max_health);
}

void Unit::changeHealthBy(double amount) {
    setHealth(getHealth() + amount);

}

void Unit::attack(Unit& target, double damage_amount) {
    if (canAttack()) {
        target.takeDamage(damage_amount);
    }
}

void Unit::heal(Unit& target, double heal_amount) {
    if (canHeal()) {
        target.healFor(heal_amount);
    }
}

bool Unit::canAttack() {
    return true;
}

bool Unit::canHeal() {
    return true;
}

void Unit::die() {
    setHealth(0);
}

bool Unit::isDead() {
    return health <= 0;
}

double Unit::getHealth() {
    return health;
}

double Unit::getMaxHealth() {
    return max_health;
}

void Unit::setHealth(double health) {
    this->health = health;
}

void Unit::setMaxHealth(double max_health) {
    this->max_health = max_health;
}
