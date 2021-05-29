#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "baseItem.hpp"
#include <vector>

using namespace std;

class GameController {
    private:
        vector<Entity*> enemiesInGame;
        Entity* currCharacter = nullptr;
        Entity* currEnemy = nullptr;

    public:
        void createCharacter(istream&);
        void createEnemies();
        int getNarrative(istream&, istream&);
        int battle(istream&);
        int displayBattleOptions(istream&);
        void evalBattleChoice(int, istream&);
        int finishBattle(istream&);

        // For testing
        Entity* getEnemy(int i) { return enemiesInGame.at(i); }
        Entity* getCurrCharacter() { return currCharacter; }
        Entity* getCurrEnemy() { return currEnemy; }
};

#endif