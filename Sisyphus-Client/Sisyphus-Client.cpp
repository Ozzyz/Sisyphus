// Sisyphus-Client.cpp : Defines the entry point for the console application.
//

#include "../Sisyphus/board.h"
#include "../Sisyphus/fen.h"
#include "../Sisyphus/utils.h"
#include <iostream>
#include <sstream>
#include <string>
#include "Sisyphus-Client.h"
using std::cout;
using std::endl;


void make_uci_move(Move &move) {
	cout << "bestmove " << move.uci() << endl;
}

void parse_move(string move_string, Board &board) {
	cout << "info parsing move string " << move_string << endl;
	Move move = Move(move_string);
	cout << "info created move " << move.toString() << endl;
	board.make_move(move);
}


void parse_uci_position(string line, Board &board) {
	// The UCI command position is on the form
	// position [fen]
	// position startposition 
	// and both can optionally end with a set of moves, for example e2e3 f7f5 b7b8q
	//TODO: Implement move info 

	int end_pos = line.find("moves");
	if (line.find("startposition")){
		board.set_position(starting_fen);
	}
	else {
		board.set_position(line.substr(9, end_pos));
	}
	// If we have moves, apply each move
	if (end_pos != string::npos) {
		string substring = line.substr(end_pos + 6, line.length());
		cout << "info substring " << substring << endl;
		std::istringstream iss(substring);
		
		string s;
		// Each move is separated by a space
		while (getline(iss, s, ' ')) {
			cout << "info parsing move " << s << "Lenght of move: " << s.length() << endl;
			parse_move(s, board);
		}
	}
}

void parse_uci_go(string line, Board &board) {
	// Format: go wtime 289536 btime 300000 winc 0 binc 0
	// Find all moves
	//print_board(board.board);
	vector<Move> moves = generate_all_moves((Color)board.get_to_move(), board);
	cout << "info choosing best move out of " << moves.size() << "available moves" << endl;
	// Make move (for now, just select the first)
	Move chosen_move = moves[0];
	// Make the move on the board
	board.make_move(chosen_move);
	// Return move to UCI engine
	make_uci_move(chosen_move);
}

void uci_loop(Board &board) {
	cout << "info entering uci pasrse loop!" << endl;
	string line;
	// Parse input from GUI
	while (true) {
		std::getline(std::cin, line);
		cout << "info this is testinfo" << endl;
		if (line.compare(0, 3, "uci") == 0) {
			// Send ready signal and info to the UCI-GUI
			cout << "id name Sisyphus" << endl;
			cout << "id author Ozzyz" << endl;
			cout << "uciok" << endl;
		}
		if(line.compare(0,7,"isready") == 0){
			cout << "readyok" << endl;
		}
		if (line.compare(0, 8, "position") == 0) {
			parse_uci_position(line, board);
		}
		if (line.compare(0, 2, "go") == 0) {
			parse_uci_go(line, board);
		}
		if (line.compare(0, 5, "quit") == 0) {
			break;
		}
	}


}

vector<Move> generate_all_moves(Color, Board &);

int main() {
	Board board = Board();
	uci_loop(board);
	std::cin.get();
}