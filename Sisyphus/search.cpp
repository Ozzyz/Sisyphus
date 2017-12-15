//
// Created by ozzy on 14/12/2017.
//

#include "search.h"
#include "board.h"
#include "evaluation.h"
#include <climits>
#include <iostream>

int negamax(Board& board, int depth, Color to_move){
    if(depth == 0){ // TODO: Check if it is a terminal node
        if(to_move == Black){
            return - eval_board_pos(board);
        }return eval_board_pos(board);
        }
    int best = INT_MIN;
    vector<Move> moves = generate_all_moves(to_move, board);
    for (auto mv : moves) {
        board.make_move(mv);
        int val = - negamax(board, depth - 1, to_move^1);
        board.undo_move(mv);
        if(val > best){
            best = val;
        };
    }
    return best;
}

// this is a very stupid implementation, succumbing to the horizon effect
Move search(Board &board){
    // In : The current board state
    // Out: The chosen move
    // Searches through the search tree, and returns the best found move
    // TODO: Adapt search dept based on time
    int depth = 5;
    // for move in board moves, if negamax(board > max, max = move
    int best = INT_MIN;

    Move best_move = Move(1,1,1);
    Color to_move = board.get_to_move();
    vector<Move> moves = generate_all_moves(to_move, board);
    std::cout << "info Considering " << moves.size() << " moves " << std::endl;
    for (auto mv : moves) {
        board.make_move(mv);
        int val = - negamax(board, depth, to_move^1);
        board.undo_move(mv);
        std::cout << "Move: " << mv.uci() << ", Score: " << val << std::endl;
        //print_board(board.board);
        if(val > best){
            best = val;
            best_move = mv;
        };
    }
    return best_move;
}
