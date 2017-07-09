#include "stdafx.h"
#include <iostream>
#include "board.h"
/*
This is the main core of the chess engine - the board
This board is using a 10x12 layout (see https://chessprogramming.wikispaces.com/10x12+Board)
White pieces start at index 12 (top)
This program is heavily inspired by 
*/


#define PAWN(piece) ((piece & 14) == 0)
#define ROW(x)			(x >> 3)
#define COL(x)			(x & 7)
int NUM_BOARD_SQUARES = 10 * 12;
int turn = 12;
Color to_move = White; // Which side to move next
// Arrays for keeping track of what piece is at a square

/* Used to keep track over castling rights
The two leftmost bits is whether white can castle
First is Queenside, then Kingside
The same for black (two rightmost bits)
*/
int castling = 0b1111;

Piece piece[64] = {};

int board[120] = {
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1,  0,  1,  2,  3,  4,  5,  6,  7, -1,
	-1,  8,  9, 10, 11, 12, 13, 14, 15, -1,
	-1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
	-1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
	-1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
	-1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
	-1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
	-1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};
// Mapping of real squares to indexes of 10x12 board
int board_map[64] = {
	21, 22, 23, 24, 25, 26, 27, 28,
	31, 32, 33, 34, 35, 36, 37, 38,
	41, 42, 43, 44, 45, 46, 47, 48,
	51, 52, 53, 54, 55, 56, 57, 58,
	61, 62, 63, 64, 65, 66, 67, 68,
	71, 72, 73, 74, 75, 76, 77, 78,
	81, 82, 83, 84, 85, 86, 87, 88,
	91, 92, 93, 94, 95, 96, 97, 98
};


// Initial piece placement 
Piece init_piece[64] = {
	wRook, wKnight, wBishop, wKing, wQueen, wBishop, wKnight, wRook,
	wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn,
	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
	bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn,
	bRook, bKnight, bBishop, bKing, bQueen, bBishop, bKnight, bRook,
};


bool slide[6] = { false, false, true, true, true, false };
/* number of knight or ray directions the piece can move
0 is pawn, 1 knight, 2 bishop ...*/
int num_directions[6] = { 0, 8, 4, 4, 8, 8 }; 

/* The distance to every square the piece can reach. This is specified relative to
the full board (120)*/
int offset[6][8] = {
	{ 0,   0,  0,  0, 0,  0,  0,  0 },
	{ -21, -19,-12, -8, 8, 12, 19, 21 }, /* KNIGHT */
	{ -11,  -9,  9, 11, 0,  0,  0,  0 }, /* BISHOP */
	{ -10,  -1,  1, 10, 0,  0,  0,  0 }, /* ROOK */
	{ -11, -10, -9, -1, 1,  9, 10, 11 }, /* QUEEN */
	{ -11, -10, -9, -1, 1,  9, 10, 11 }  /* KING */
};



bool in_check(Color color) {
	// Returns true if the king of given color is in check

	Piece king = color == White ? wKing : bKing;
	for (int square = 12; square < 64; square++)
	{
		if (piece[square] == king) {
			return is_attacked(square, color ^ 1);
		}
	}
	return true;
}

bool is_attacked(int square, Color atk_color) {
	// Returns true if the square is attacked by pieces with the given color
	int mod = atk_color == Black ? -1 : 1;
	for (int i = 0; i < 64; i++)
	{
		if (is_color(piece[i], atk_color)) {
			Piece pc = piece[i];
			if (PAWN(pc)) {
				// Reverse attacking direction if black
				if (COL(i) != 7  && (i + 7*mod) == square){
					std::cout << "Attaking Piece: " << pc << "Square: " << i;
					return true;
				}
				if (COL(i) != 0 && (i + 9*mod) == square){
					std::cout << "Attaking Piece: " << pc << "Square: " << i;
					return true;
				}
			}
			else {
				// Look at available moves for each piece. Check if it is within bounds
				int piece_type = pc >> 1;
				for (int j = 0; j < num_directions[piece_type]; ++j) { /* for all knight or ray directions */
					for (int n = i;;) { /* starting with from square */
						n = board[board_map[n] + offset[piece_type][j]]; /* next square along the ray j */
						if (n == square) {
							return true;
						}
						if (n == -1) break; /* outside board */
						if (piece[n] != Empty) { break; } // Piece is blocking path
						if (!slide[piece_type]) { break; } 
						
					}
				}
			}
			
			
		}
	}
	return false;
}

bool is_color(Piece piece, Color color) {
	// Since all white pieces are even numbered, and the color white is 0, the following is correct
	return (piece % 2) == color && piece != Empty;
}

void init_board(Piece pieces[]) {
	for (int i = 0; i < 64; i++) {
		piece[i] = pieces[i];
	}
}

void init_board() {
	for (int i = 0; i < 64; i++)
	{
		piece[i] = init_piece[i];
	}
}


int main(int argc, char* argv[]){
	std::cin.get();
}