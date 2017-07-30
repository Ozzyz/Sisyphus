#pragma once
#ifndef UTILS_H
#define UTILS_H
#endif // !UTILS_H


#include "board.h"
#include <iostream>
using std::string;
extern const wchar_t* char_pieces[13];
extern void print_board(Piece board[64]);
extern int square_to_board_index(string square);


