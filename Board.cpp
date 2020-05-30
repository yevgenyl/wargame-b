#include "Board.hpp"
#include <iostream>
typedef unsigned int uint;
using namespace std;
/*
 * Exceptions:
 */
class IllegalMoveException: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Move not allowed!";
    }
} IllegalMoveException;

class IndexOutOfBoundsException: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Location doesn't exist!";
    }
} IndexOutOfBoundsException;

class MoveOnEmptyException: public std::exception
{
    virtual const char* what() const throw()
    {
        return "No soldier was found on moving location.";
    }
} MoveOnEmptyException;

bool WarGame::Board::has_soldiers(uint player_number) const{
    for(int i = 0; i < this->board.size(); i++){
        for(int j = 0; j < this->board[i].size(); j++){
            if(board[i][j] != nullptr && board[i][j]->getPlayer() == player_number) //If we found a player of team 'player_number'
                return true;
        }
    }
    return false;
}

Soldier*& WarGame::Board::operator[](std::pair<int,int> location){
    std::pair<int,int> boardDimension = getBoardDimensions();
    if((location.first < boardDimension.first) && (location.second < boardDimension.second)) // Check for legal location (in bounds).
        return this->board[location.first][location.second];
    else
        throw  IndexOutOfBoundsException;
}

Soldier* WarGame::Board::operator[](std::pair<int,int> location) const {
    std::pair<int, int> boardDimension = getBoardDimensions();
    if ((location.first < boardDimension.first) &&
        (location.second < boardDimension.second)) { // Check for legal location (in bounds).
        if (this->board[location.first][location.second] == nullptr) {
            throw IndexOutOfBoundsException;
        } else {
            return this->board[location.first][location.second];
        }
    }else {
        throw IndexOutOfBoundsException;
    }
}

void WarGame::Board::move(uint player_number, std::pair<int,int> source, MoveDIR direction){
    std::pair<int,int> boardDimension = getBoardDimensions();
    if((source.first < boardDimension.first) && (source.second < boardDimension.second)) { // Check for legal location (in bounds).
        if (this->board[source.first][source.second] != nullptr) { // Check if there os Soldier ehich can be moved.
            if (canMove(source, direction)) {
                std::pair<int, int> destination = getDestinationIndex(source, direction); // Get desired destination.
                this->board[destination.first][destination.second] = this->board[source.first][source.second]; // Move soldier to destination.
                this->board[source.first][source.second] = nullptr; // Remove soldier from old destination.
                applyAttack(player_number,destination); // Apply attack from new destination.
                updateBoard(); //Update dead players.
            } else {
                throw IllegalMoveException;
            }
        } else {
            throw MoveOnEmptyException;
        }
    }else{
        throw  IndexOutOfBoundsException;
    }
}

void WarGame::Board::applyAttack(uint player_number, std::pair<int,int> location){
    uint enemy = (player_number == 1 ? 2 : 1); // Which player is the enemy
    std::vector<std::pair<int,int>> enemyLocations = getLocations(enemy); // Get enemy's team locations.
    std::vector<std::pair<int,int>> playerLocations = getLocations(player_number); // Get player's team locations.
    Soldier *soldier = this->board[location.first][location.second]; // The soldier which making the attack.
    std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndRefrencesOfPlayer = getRadiusAndReferenceForEach(playerLocations);
    std::vector<std::pair<std::pair<int,int>,Soldier*>> enemyLocationsAndReferences = getLocationsAndReferences(enemyLocations);
    std::vector<std::pair<std::pair<int,int>,Soldier*>> teamLocationsAndReferences = getLocationsAndReferences(playerLocations);
    soldier->attack(location, teamLocationsAndReferences, enemyLocationsAndReferences, radiusAndRefrencesOfPlayer); // Finally attack
}

std::vector<std::pair<int,int>> WarGame::Board::getLocations(uint player_number){
    std::vector<std::pair<int,int>> enemyLocation;
    for(int i = 0; i < this->board.size(); i++){
        for(int j = 0; j < this->board[i].size(); j++){
            if(this->board[i][j] != nullptr){
                if (this->board[i][j]->getPlayer() == player_number) {
                    std::pair<int, int> index = make_pair(i, j);
                    enemyLocation.push_back(index);
                }
            }
        }
    }
    return enemyLocation;
}

std::vector<std::pair<std::pair<int,int>,Soldier*>> WarGame::Board::getLocationsAndReferences(std::vector<std::pair<int,int>> locations){
    std::vector<std::pair<std::pair<int,int>,Soldier*>> locationsAndReferences;
    for(int i = 0; i < locations.size(); i++){
        std::pair<int,int> location = locations[i];
        Soldier *soldier = this->board[location.first][location.second];
        std::pair<std::pair<int,int>,Soldier*> toPush = make_pair(location,soldier);
        locationsAndReferences.push_back(toPush);
    }
    return locationsAndReferences;
}

std::vector<Soldier*> WarGame::Board::getPlayersRadius(std::pair<int,int> soldierLocation, std::vector<std::pair<int,int>> locations){
    std::vector<Soldier*> enemyRadius;
    std::pair<int,int> leftUp = make_pair(soldierLocation.first-1, soldierLocation.second-1);
    std::pair<int,int> up = make_pair(soldierLocation.first-1, soldierLocation.second);
    std::pair<int,int> rightUp = make_pair(soldierLocation.first-1, soldierLocation.second+1);
    std::pair<int,int> right = make_pair(soldierLocation.first, soldierLocation.second+1);
    std::pair<int,int> rightDown = make_pair(soldierLocation.first+1, soldierLocation.second+1);
    std::pair<int,int> down = make_pair(soldierLocation.first+1, soldierLocation.second);
    std::pair<int,int> leftDown = make_pair(soldierLocation.first+1, soldierLocation.second-1);
    std::pair<int,int> left = make_pair(soldierLocation.first, soldierLocation.second-1);
    for(int i = 0; i < locations.size(); i++){
        std::pair<int,int> current = locations[i];
        if(current == leftUp || current == up || current == rightUp
        || current == right || current == rightDown || current == down
        || current == leftDown || current == left)
            enemyRadius.push_back(this->board[current.first][current.second]);
    }
    return enemyRadius;
}

std::vector<std::pair<std::vector<Soldier*>,Soldier*>> WarGame::Board::getRadiusAndReferenceForEach(std::vector<std::pair<int,int>> locations){
    std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReferences;
    for(int i = 0; i < locations.size(); i++){
        Soldier *soldier = this->board[locations[i].first][locations[i].second];
        std::vector<Soldier*> radius = getPlayersRadius({locations[i].first,locations[i].second},locations);
        std::pair<std::vector<Soldier*>,Soldier*> p = make_pair(radius,soldier);
        radiusAndReferences.push_back(p);
    }
    return radiusAndReferences;
}

std::pair<int, int> WarGame::Board::getBoardDimensions() const{
    std::pair<int, int> dimensions(WarGame::Board::rows,WarGame::Board::cols);
    return dimensions;
}

bool WarGame::Board::canMove(std::pair<int,int> location, MoveDIR move){
    std::pair<int,int> index = getDestinationIndex(location,move);
    std::pair<int,int> boardDimension = getBoardDimensions();
    bool inBounds = index.first >= 0 && index.second >= 0 &&
            index.first < boardDimension.first && index.second < boardDimension.second;
    if(inBounds) {
        bool destEmpty = board[index.first][index.second] == nullptr;
            if (destEmpty){
                return true;
            } else{
                return false;
            }
    } else{
        return false;
    }
}

std::pair<int,int> WarGame::Board::getDestinationIndex(std::pair<int,int> location, MoveDIR move){
    std::pair<int,int> destination;
    switch(move){
        case Up:
            destination = make_pair(location.first+1,location.second);
            break;
        case Right:
            destination = make_pair(location.first,location.second+1);
            break;
        case Left:
            destination = make_pair(location.first,location.second-1);
            break;
        case Down:
            destination = make_pair(location.first-1,location.second);
            break;
        default:
            break;
    }
    return destination;
}

void WarGame::Board::updateBoard(){
    for(int i = 0; i < this->board.size(); i++){
        for(int j = 0; j < this->board[i].size(); j++){
            if(this->board[i][j] != nullptr && this->board[i][j]->getHealth() <= 0)
                board[i][j] = nullptr;
        }
    }
}

void WarGame::Board::drawBoard(){
    for(int i = 0; i < this->board.size(); i++){
        for(int j = 0; j < this->board[i].size(); j++){
            if(this->board[i][j] != nullptr) {
                cout << " " + this->board[i][j]->toString() + " ";
            } else{
                cout << " __ ";
            }
        }
        cout << endl;
    }
    cout << '\n';
}
