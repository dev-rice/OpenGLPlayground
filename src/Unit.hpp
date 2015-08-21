#ifndef Unit_h
#define Unit_h

class Unit {
public:
    Unit(double max_health);

    void takeDamage(double damage_amount);
    void healFor(double heal_amount);

    void die();
    bool isDead();

    void attack(Unit& target, double damage_amount);
    void heal(Unit& target, double heal_amount);

    double getHealth();
    double getMaxHealth();

    bool canAttack();
    bool canHeal();

    void setHealth(double health);
    void setMaxHealth(double max_health);

private:

    void changeHealthBy(double amount);
    bool isKillingBlow(double damage_amount);
    bool wouldBeOverFullHealth(double heal_amount);

    double max_health;
    double health;
};

#endif
