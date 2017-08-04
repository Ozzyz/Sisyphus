#pragma once
#ifndef UTILS_H
#define UTILS_H
#endif // !UTILS_H
#define DllExport   __declspec(dllexport)
#define DllImport __declspec(dllimport)
#include <iostream>
#include <string>
#include "windows.h"
#include "fcntl.h"
#include "io.h"


// With this setup, we can go color ^= 1 (XOR)
typedef enum { White = 0, Black = 1, None = 2 }Color;
inline Color operator^(Color a, int b)
{
	return static_cast<Color>(static_cast<int>(a) ^ b);
}
inline Color operator==(Color a, int other) {
	return static_cast<Color>(static_cast<int>(a) == other);
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

#define PAWN(piece) (piece == 1 || piece == 0)
#define ROW(x)			(x >> 3)
#define COL(x)			(x & 7)


using std::string;
extern const wchar_t* char_pieces[13];
DllExport void print_board(Piece[64]);
DllExport int square_to_board_index(string square);
DllExport string board_index_to_square(int index);



