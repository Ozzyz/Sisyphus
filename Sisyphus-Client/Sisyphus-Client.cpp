// Sisyphus-Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Sisyphus/board.h"
#include "../Sisyphus/fen.h"
#include "../Sisyphus/utils.h"
#include <iostream>
int main()
{
	string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	Board board = Board(starting_fen);
	print_board(board.board);
	std::vector<Move> moves = generate_all_moves(White, board);
	std::cin.get();
}

