//
// Created by ozzy on 14/12/2017.
//

#include "search.h"
#include "board.h"
#include "evaluation.h"
#include <climits>
// this is a very stupid implementation, succumbing to the horizon effect
Move search(Board &board){
    // In : The current board state
    // Out: The chosen move
    // Searches through the search tree, and returns the best found move
    // TODO: Adapt search dept based on time

    int depth = 3;
    // for move in board moves, if negamax(board > max, max = move

}


int negamax(Board& board, int depth, Color color){
    if(depth == 0){ // TODO: Check if it is a terminal node
        return (int)color * eval_board_pos(board);
    }
    int best = INT_MIN;

    vector<Move> moves = generate_all_moves(color, board);
    for (auto mv : moves) {
        board.make_move(mv);
        int val = - negamax(board, depth - 1, color^1);
        board.undo_move(mv);
        if(val > best){
            best = val;
        };
    }
}