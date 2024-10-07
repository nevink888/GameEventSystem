
#include <iostream>
#include <string>
#include <unordered_set>
#include <memory>
#include <vector>

using namespace std;

// Declaration of GameEngine (Subject) class
class GameEngine;

// Abstract Observer (Player) Class
class Player {
public:
    virtual ~Player() = default;
    virtual void play() = 0;
    virtual void update(const string& event) = 0;
};

//  Player Class: Warrior
class Warrior : public Player {
public:
    void play() override {
        cout << "[Warrior] Engages in battle with the enemy!" << endl;
    }

    void update(const string& event) override {
        cout << "[Warrior] Received event: " << event << endl;
    }
};

//  Player Class: Mage
class Mage : public Player {
public:
    void play() override {
        cout << "[Mage] Casts a fireball at the enemy!" << endl;
    }

    void update(const string& event) override {
        cout << "[Mage] Received event: " << event << endl;
    }
};

//  Factory to create Player objects
class PlayerFactory {
public:
    unique_ptr<Player> createPlayer(const string& type) {
        if (type == "Warrior") {
            return make_unique<Warrior>();
        }
        else if (type == "Mage") {
            return make_unique<Mage>();
        }
        return nullptr;
    }
};

// (GameEngine) that generates events
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

int main() {
    PlayerFactory factory;
    GameEngine gameEngine;

    // Create players using the factory
    unique_ptr<Player> warrior = factory.createPlayer("Warrior");
    unique_ptr<Player> mage = factory.createPlayer("Mage");

    // Add players to the game engine to receive events
    gameEngine.addPlayer(warrior.get());
    gameEngine.addPlayer(mage.get());

    // Simulate actions for the players
    if (warrior) {
        warrior->play();
    }

    if (mage) {
        mage->play();
    }

    gameEngine.generateEvent("Enemy appears!");
    gameEngine.generateEvent("Power-up available!");

    // Create another player and perform an action
    unique_ptr<Player> anotherWarrior = factory.createPlayer("Warrior");
    if (anotherWarrior) {
        anotherWarrior->play();
        gameEngine.addPlayer(anotherWarrior.get());
    }

    // Generate another event after adding a new player
    gameEngine.generateEvent("Boss fight starts!");

    return 0;
}

