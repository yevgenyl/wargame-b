#include "doctest.h"
#include "Board.hpp"
#include "FootSoldier.hpp"
#include "FootCommander.hpp"
#include "Paramedic.hpp"
#include "ParamedicCommander.hpp"
#include "Sniper.hpp"
#include "SniperCommander.hpp"

using namespace WarGame;

TEST_CASE("Small Board 3x3 "){
    WarGame::Board board(3,3);
    CHECK(!(board.has_soldiers(2)));
    CHECK(!(board.has_soldiers(1)));
    board[{0,0}] = new FootCommander(1);
    board[{0,1}] = new FootCommander(1);
    CHECK(board.has_soldiers(1));
    CHECK(!(board.has_soldiers(1)));
    board[{2,0}] = new FootCommander(2);
    board[{2,1}] = new FootCommander(2);    
    board.move(1,{0,0},WarGame::Board::MoveDIR::Up);
    board.move(2,{2,0},WarGame::Board::MoveDIR::Down);
    board.move(1,{0,1},WarGame::Board::MoveDIR::Up);
    board.move(2,{2,1},WarGame::Board::MoveDIR::Down);
    CHECK(!(board.has_soldiers(2)));
    CHECK(!(board.has_soldiers(1)));
}

TEST_CASE("Not finished tests..") {
    WarGame::Board board(5,5);
    board[{0,0}] = new FootSoldier(1);
    for (int i = 0; i < 100; i++) {
                CHECK(!board.has_soldiers(2));
    }
}
