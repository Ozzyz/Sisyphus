
#include "move.h"

/*
The move is represented by a 16-bit field
From lowest to highest:
6 bit - From square 
6 bit - To square
4 bit - Special moves (pawn promotion, where each bit is promote to {Knight, Bishop, Rook, Queen}
Table for the last 4 bits:

0000 : quiet moves (No captures or promotions)
0001 : double pawn push (Move two squares from initial pawn position)
0010 : King castle
0011 : Queen castle
0100 : Captures
0101 : En-passant capture
0110 : Unused
0111 : Unused
1000 : Knight promotion
1001 : Bishop promotion 
1010 : Rook promotion
1011 : Queen promotion
1100 :Knight promotion capture 
1101 : Bishop promotion capture
1110 :  Rook promotion capture
1111 : Queen promotion capture
*/



class Move {
protected:
	unsigned short move;

	Move(unsigned int from, unsigned int to, unsigned int flags) {
		move = (from & 0b111111) | ((to & 0b111111) << 6) | ((flags & 0b111111) << 12);
	}

	unsigned int from_square() {
		return move & 0b111111;
	}

	unsigned int to_square() {
		return (move >> 6) & 0b111111;
	}

	unsigned int get_flags() {
		return (move >> 12) & 0b111111;
	}

	bool operator==(Move a) const { return (move & 0xffff) == (a.move & 0xffff); }
	bool operator!=(Move a) const { return (move & 0xffff) != (a.move & 0xffff); }
};

