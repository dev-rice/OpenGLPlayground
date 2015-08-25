#ifndef Unit_h
#define Unit_h

#include <iostream>

#include "Transform3D.hpp"

using namespace std;

class Unit {
public:
    Unit(Transform3D& transform_3D, double max_health, double attack_range);

    void takeDamage(double damage_amount);
    void healFor(double heal_amount);

    void die();
    bool isDead();

    void attack(Unit& target, double damage_amount);
    void heal(Unit& target, double heal_amount);

    bool isInAttackRange(Unit& target);

    double getHealth();
    double getMaxHealth();
    double getAttackRange();

    bool canAttack();
    bool canHeal();

    void setHealth(double health);
    void setMaxHealth(double max_health);

    Transform3D& getTransform3D();

private:

    void changeHealthBy(double amount);
    bool isKillingBlow(double damage_amount);
    bool wouldBeOverFullHealth(double heal_amount);

    Transform3D* transform_3D;
    double max_health;
    double health;
    double attack_range;
};

#endif
