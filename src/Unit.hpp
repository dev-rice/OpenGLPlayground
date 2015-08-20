#ifndef Unit_h
#define Unit_h

class Unit {
public:
    Unit(float max_health);

    void takeDamage(float damage_amount);
    void healFor(float heal_amount);

    void die();
    bool isDead();

    void attack(Unit& target, float damage_amount);
    void heal(Unit& target, float heal_amount);

    float getHealth();
    float getMaxHealth();

    void setHealth(float health);
    void setMaxHealth(float max_health);

private:

    void changeHealthBy(float amount);
    bool isKillingBlow(float damage_amount);
    bool wouldBeOverFullHealth(float heal_amount);

    float max_health;
    float health;
};

#endif
