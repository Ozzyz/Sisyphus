
#include "stdafx.h"
#include "utils.h"
#include <iostream>
#include <string>
#include "windows.h"
#include "fcntl.h"
#include "io.h"
void print_piece(Piece);
using namespace std;

void print_board(int board[64]) {
	for (int i = 0; i < 64; i++)
	{
		if (i % 8 == 0) {
			
			std::cout << '\n'<< std::string(40, '_') << '\n';
		}
		Piece pc = (Piece)board[i];
		if (pc == Empty) {
			std::wcout << "  ";
		}else{
		print_piece(pc);
		}
		std::cout << "|  ";
	}
}
const wchar_t* unicode_pieces[12] = { L"\u265F" ,L"\u2659" ,
L"\u265E" ,L"\u2658" , L"\u265D" ,L"\u2657" ,L"\u265C" , L"\u2656" ,
L"\u265B" ,L"\u2655" , L"\u265A" ,L"\u2654" };

const char* char_pieces[13] = { "wP", "bP",
"wKn", "bKn",
"wB", "bB",
"wR", "bR",
"wQ", "bQ",
"wK", "bK","  "};

void print_piece(Piece pc) {
	//_setmode(_fileno(stdout), _O_U16TEXT);
	//SetConsoleOutputCP(65001);
	//HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//DWORD written = 0;
	// explicitly call the wide version (which always accepts UTF-16)
	wcout << char_pieces[pc];
}

int square_to_board_index(string square) {
	if (square.length() != 2) {
		throw std::invalid_argument("Cant convert - Illegal square!");
	}
	string files = "hgfedcba";
	string ranks = "1234567";
	char file = square[0];
	char rank = square[1];
	return (int)files.find_first_of(file) + ranks.find_first_of(rank) * 8;
}
