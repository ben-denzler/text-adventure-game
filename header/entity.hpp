#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
using namespace std;

class Entity
{
    protected:
      string name = "" ;
      int health = 0;
      int attack = 0;
      int defense = 0;

    public:
    
        // Constructor
        Entity(string _name, int _health, int _attack, int _defense) 
            : name(_name), health(_health), attack(_attack), defense(_defense) {}

        virtual void display() = 0;
        void takeDamage(int damage) { health -= damage; }
        bool isDead() { return (health <= 0); }

        // Getters
        int getAttack() { return attack; }
        int getDefense() { return defense; }
        int getHealth() { return health; }
        string getName() { return name; }
        virtual string getType() {}
        virtual baseItem* getInventory() { /*THROW EXCEPTIONS (if this is not a character)*/ }

};


#endif // ENTITY_HPP