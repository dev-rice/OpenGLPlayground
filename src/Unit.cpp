#include "Unit.hpp"

Unit::Unit(Transform3D& transform_3D, double max_health, double attack_range) : transform_3D(&transform_3D), max_health(max_health), health(max_health), attack_range(attack_range) {

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

bool Unit::isInAttackRange(Unit& target) {
    float distance_to_target = getTransform3D().distanceTo(target.getTransform3D());
    return (distance_to_target <= getAttackRange());
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

double Unit::getAttackRange() {
    return attack_range;
}

void Unit::setHealth(double health) {
    this->health = health;
}

void Unit::setMaxHealth(double max_health) {
    this->max_health = max_health;
}

Transform3D& Unit::getTransform3D() {
    return *transform_3D;
}
