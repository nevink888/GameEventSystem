#include <iostream>
#include <string>
#include <memory>
#include <unordered_set>

using namespace std;

// Abstract Player class (Observer)
class Player {
public:
    virtual ~Player() = default;
    virtual void play() = 0;
    virtual void update(const string& event) = 0;
};

// Concrete Player Class: Warrior
class Warrior : public Player {
public:
    void play() override {
        cout << "[Warrior] Engages in battle with the enemy!" << endl;
    }

    void update(const string& event) override {
        cout << "[Warrior] Received event: " << event << endl;
    }
};

// Concrete Player Class: Mage
class Mage : public Player {
public:
    void play() override {
        cout << "[Mage] Casts a fireball at the enemy!" << endl;
    }

    void update(const string& event) override {
        cout << "[Mage] Received event: " << event << endl;
    }
};

// PlayerFactory to create different types of Player objects
class PlayerFactory {
public:
    Player* createPlayer(const string& type) {
        if (type == "Warrior") {
            return new Warrior();
        } else if (type == "Mage") {
            return new Mage();
        }
        return nullptr;
    }
};

// Subject class (GameEngine) to generate events and notify players
class GameEngine {
private:
    unordered_set<Player*> players;

public:
    void addPlayer(Player* player) {
        players.insert(player);
    }

    void removePlayer(Player* player) {
        players.erase(player);
    }

    void generateEvent(const string& event) {
        cout << "Game Event: " << event << endl;
        for (Player* player : players) {
            player->update(event);
        }
    }
};

// Main function demonstrating the factory and observer pattern
int main() {
    PlayerFactory factory;
    GameEngine gameEngine;

    // Create players using the factory
    Player* warrior = factory.createPlayer("Warrior");
    Player* mage = factory.createPlayer("Mage");

    // Add players to the game engine
    gameEngine.addPlayer(warrior);
    gameEngine.addPlayer(mage);

    // Simulate actions for the players
    if (warrior) {
        warrior->play();
    }
    
    if (mage) {
        mage->play();
    }

    // Generate some game events
    gameEngine.generateEvent("Enemy appeared");
    gameEngine.generateEvent("Power-up available");

    // Create another player and perform an action
    Player* anotherWarrior = factory.createPlayer("Warrior");
    if (anotherWarrior) {
        anotherWarrior->play();
        gameEngine.addPlayer(anotherWarrior);
    }

    // Generate another game event
    gameEngine.generateEvent("Boss fight starts");

    // Clean up
    delete warrior;
    delete mage;
    delete anotherWarrior;

    return 0;
