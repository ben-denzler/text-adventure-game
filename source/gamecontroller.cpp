#ifndef GAME_CONTROLLER_CPP
#define GAME_CONTROLLER_CPP

#include "../header/game_controller.hpp"
#include "../header/factory.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <ios>
#include <limits>

using namespace std;

void GameController::createCharacter(istream& input) {
    string name;
    char type;

    // Ask for user input
    cout << "Please type the name of your character. Press Enter to continue." << endl;
    getline(input, name);

    // Display description of classes
    cout << endl;
    cout << "Choose the corresponding number of your class." << endl;
    cout << "1) Rougemouse - a fast mouse who specializes in small weaponary." << endl;
    cout << "2) Swordmouse - a gallant mouse who specializes in sword combat." << endl;
    cout << "3) Monkmouse - a wise mouse who specializes in using words and staffs." << endl;

    // Handle invalid input for type
    input >> type;
    while (!isdigit(type) || ((type != '1') && (type != '2') && (type != '3'))) {
        cout << "Invalid input, try again." << endl;
        input >> type;
    }
    cout << endl;

    // Create character from factory
    AbstractFactory* my_factory = new EntityFactory();
    currCharacter = my_factory->createCharacter(name, atoi(&type));

    // Confirms that the name and type is correct
    cout << endl;
    cout << currCharacter->getName() + " is a " + currCharacter->getType() << "!" << endl;

    // Delete anything created down here :)
    input.ignore(numeric_limits<streamsize>::max(), '\n');
    delete my_factory;
}

void GameController::createEnemies() {
    AbstractFactory* my_factory = new EntityFactory();
    
    // 3,2,1
    enemiesInGame.push_back(my_factory->createEnemy(3));
    enemiesInGame.push_back(my_factory->createEnemy(2));
    enemiesInGame.push_back(my_factory->createEnemy(1));

    // Delete anything created down here :)
    delete my_factory;
}

std::string GameController::getNarrative(std::string fileName) {
    
   // get next line
   //if line is CHOICE
   //getnext two times 
    
}

// Returns 0 if enemy is dead
// Returns 1 if character is dead
// Returns 2 if enemy does not exist
// Returns 3 if character wants to flee.
int GameController::battle(istream& inFS) {
    
    //get enemy from narrative
    currEnemy = enemiesInGame.back();
    enemiesInGame.pop_back();

    if (currEnemy != nullptr) {
        cout << "BATTLE HAS STARTED! " << currEnemy->getName() << " is attacking you." << endl;
        while (!currCharacter->isDead() && !currEnemy->isDead()) {
            
            // Display stats and options
            cout << "Character stats: "; currCharacter->display(); cout << endl;
            cout << "Enemy stats: "; currEnemy->display(); cout << endl;

            int battleChoice = displayBattleOptions(inFS);
            if (battleChoice == 3) {
                cout << "You were able to safely get away." << endl;
                return 3;
            }
            else { evalBattleChoice(battleChoice, inFS); }
        }
        
        return finishBattle();
    }
    else {
        cout << "ERROR: NO ENEMY TO FIGHT" << endl;
        return 2;
    }
}

int GameController::displayBattleOptions(istream& input){
    char num;
    
    cout << "Choose one of the options below:" << endl;
    cout << "1) ATTACK" << endl;
    cout << "2) DEFEND" << endl;
    cout << "3) FLEE" << endl;
    cout << "4) Access Inventory" << endl;
    
    input >> num;
    while (!isdigit(num) || ((num != '1') && (num != '2') && (num != '3') && (num != '4'))) {
        cout << "Invalid input, try again." << endl;
        input >> num;
    }
    cout << endl;

    input.ignore(numeric_limits<streamsize>::max(), '\n');
    return atoi(&num);
}

void GameController::evalBattleChoice(int battleChoice, istream& inFS) {
    // Attack
    if (battleChoice == 1) {
        currEnemy->takeDamage(currCharacter->getAttack());
        cout << "You dealt " << currCharacter->getAttack() << "damage!" << endl;
    }

    // Defend
    else if (battleChoice == 2) {
        cout << "You chose to defend." << endl;
        cout << currEnemy->getName() << " attacks!" << endl;
        currCharacter->takeDamage(currEnemy->getAttack() - currCharacter->getDefense());
        cout << "Player loses "  << (currEnemy->getAttack() - currCharacter->getDefense()) << " HP." << endl;
    }

    // Access Inventory and change weapon, armor, or use consumable
    else if (battleChoice == 4) {
        cout << "----------------------------------------------------" << endl;
        cout << "INVENTORY: Armor, Weapons & Consumables" << endl;
        currCharacter->getInventory()->display();
        cout << "----------------------------------------------------" << endl;
        cout << "Choose your item by typing its name (Case Matters). Press Enter to continue." << endl;
        
        string item;
        getline(inFS, item);
        baseItem* foundItem = currCharacter->getInventory()->find(item);
        while (foundItem == nullptr) {
            cout << "ERROR: ITEM NOT FOUND. Please type the item's name again." << endl;
            getline(inFS, item);
            foundItem = currCharacter->getInventory()->find(item);
        }
            foundItem->use(currCharacter);
            if (dynamic_cast<Consumable*>(foundItem) != nullptr) { delete foundItem; }
        cout << "You have chosen: " << item << endl;
    }

    if (battleChoice != 2) {
        // Enemy's turn
        cout << currEnemy->getName() << " attacks!" << endl;
        currCharacter->takeDamage(currEnemy->getAttack());
        cout << "Player loses "  << currEnemy->getAttack() << " HP" << endl;
    }
}

int GameController::finishBattle() {
    if (currEnemy->isDead()) {
        cout << "Congratulations! " << currEnemy->getName() << " has fainted." << endl;
        delete currEnemy;
        return 0;
    }
    else if (currCharacter->isDead()) {
        cout << "You have passed out. Can you find the strength to save the world again?" << endl;
        return 1;
    }
}

#endif