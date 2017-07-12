
#include "move.h"





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

