#pragma once
#include <vector>
#include "Soldier.hpp"
typedef unsigned int uint;

namespace WarGame {

class Board {
  private:
    std::vector<std::vector<Soldier*>> board;
    uint rows, cols;
  public:
    enum MoveDIR { Up, Down, Right, Left };
    
    Board(uint numRows, uint numCols) : 
      board(numRows, std::vector<Soldier*>(numCols, nullptr)), rows(numRows), cols(numCols) {}

    // operator for putting soldiers on the game-board during initialization.
    Soldier*& operator[](std::pair<int,int> location);
    
    // operator for reading which soldiers are on the game-board.
    Soldier* operator[](std::pair<int,int> location) const;

    std::pair<int,int> getBoardDimensions() const;

    bool canMove(std::pair<int,int> location, MoveDIR move);

    std::pair<int,int> getDestinationIndex(std::pair<int,int> location, MoveDIR move);

    void applyAttack(uint player_number, std::pair<int,int> location);

    std::vector<std::pair<int,int>> getLocations(uint player_number);

    void drawBoard();

    void updateBoard();

    std::vector<Soldier*> getPlayersRadius(std::pair<int,int> soldierLocation, std::vector<std::pair<int,int>> locations);

    std::vector<std::pair<std::pair<int,int>,Soldier*>> getLocationsAndReferences(std::vector<std::pair<int,int>> locations);

    std::vector<std::pair<std::vector<Soldier*>,Soldier*>> getRadiusAndReferenceForEach(std::vector<std::pair<int,int>> locations);

    // The function "move" tries to move the soldier of player "player"
    //     from the "source" location to the "target" location,
    //     and activates the special ability of the soldier.
    // If the move is illegal, it throws "std::invalid_argument". 
    // Illegal moves include:
    //  * There is no soldier in the source location (i.e., the soldier pointer is null);
    //  * The soldier in the source location belongs to the other player.
    //  * There is already another soldier (of this or the other player) in the target location.
    // IMPLEMENTATION HINT: Do not write "if" conditions that depend on the type of soldier!
    // Your code should be generic. All handling of different types of soldiers 
    //      must be handled by polymorphism.
    void move(uint player_number, std::pair<int,int> source, MoveDIR direction);

    // returns true iff the board contains one or more soldiers of the given player.
    bool has_soldiers(uint player_number) const;
};

}
