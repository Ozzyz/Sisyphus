#pragma once
#define EXPORT_TEST_FUNCTIONS
#define DllExport   __declspec(dllexport)
#define DllImport __declspec(dllimport)

// With this setup, we can go color ^= 1 (XOR)
typedef enum  { White = 0, Black = 1, None = 2 }Color;
inline Color operator^(Color a, int b)
{
	return static_cast<Color>(static_cast<int>(a) ^ b);
}

typedef enum {
	wPawn = 0, bPawn = 1,
	wKnight = 2, bKnight = 3,
	wBishop = 4, bBishop = 5,
	wRook = 6, bRook = 7,
	wQueen = 8, bQueen = 9,
	wKing = 10, bKing = 11,
	Empty = 12
}Piece;

extern Piece piece[64];
extern Piece init_piece[64];
extern int board[120];
DllExport bool in_check(Color color);
DllExport void init_board(Piece piece[]);
DllExport bool is_attacked(int square, Color color);

//DllExport void generate_move(int from, int to, bool capture);

DllExport bool is_color(Piece piece, Color color);