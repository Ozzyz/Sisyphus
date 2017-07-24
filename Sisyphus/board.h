#pragma once
#define EXPORT_TEST_FUNCTIONS
#define DllExport   __declspec(dllexport)
#define DllImport __declspec(dllimport)
#include "stdafx.h"
#include <iostream>
#include <vector>
//#include "fen.h"
#include "move.h"
using std::vector;
using std::string;
// Handy square definitions
static const int A1 = 7;
static const int H8 = 56;
static const int A8 = 0;
static const int H1 = 63;


// With this setup, we can go color ^= 1 (XOR)
typedef enum  { White = 0, Black = 1, None = 2 }Color;
inline Color operator^(Color a, int b)
{
	return static_cast<Color>(static_cast<int>(a) ^ b);
}
inline Color operator==(Color a, int other) {
	return static_cast<Color>(static_cast<int>(a) == other);
}


typedef enum {
	wCastleKing = 8,
	wCastleQueen = 4,
	bCastleKing = 2,
	bCastleQueen = 1
}CastlePermissions;

typedef enum {
	wPawn = 0, bPawn = 1,
	wKnight = 2, bKnight = 3,
	wBishop = 4, bBishop = 5,
	wRook = 6, bRook = 7,
	wQueen = 8, bQueen = 9,
	wKing = 10, bKing = 11,
	Empty = 12
}Piece;

class Board {
private:
	static const int NUM_BOARD_SQUARES = 10 * 12;
	static const int BOARD_SIZE = 64;
	// Square that can be attacked en passant, if viable, else 99
	int ep_square;
	int turn;
	/* Used to keep track over castling rights
	The two leftmost bits is whether white can castle
	First is Queenside, then Kingside
	The same for black (two rightmost bits)
	*/
	int castling;
	// Which side to move next
	Color to_move;
public:
	Board();
	Board(string fen);
	Piece board[BOARD_SIZE];
	int get_ep_square();
	int get_castling_rights();
	Color get_to_move();
	int get_turn();
	void set_turn(int turn);
	void set_to_move(Color to_move);
	void set_ep_square(int ep_square);
	void set_castling_rights(int castling);
	void set_board(Piece pieces[64]);
};



extern Piece piece[64];
extern Piece init_piece[64];
extern int mailbox_board[120];
extern int board_map[64];
DllExport bool in_check(Color color);
DllExport void init_board(Piece piece[]);
DllExport void init_board();
DllExport bool is_attacked(int square, Color color);
//DllExport void generate_move(int from, int to, bool capture);
DllExport bool is_color(Piece piece, Color color);

vector<Move> generate_all_moves(Color current_side, Board);
void generate_move(int from, int to, int flags, vector<Move>&);

