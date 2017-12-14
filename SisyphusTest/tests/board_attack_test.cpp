#include "../../Sisyphus/board.h"
#include "gtest/gtest.h"


TEST(BoardTest, BoardFindsAttackingSquaresOfPawns) {
	// Test that the attacked square function works with multiple pieces
	// https://lichess.org/editor/rnbqkbnr/ppp1pppp/6P1/8/8/B6p/PPPPPPPP/RNBQK1NR_w_KQkq_-
	Piece init_piece_test[64] = {
		wRook, wKnight, Empty, wKing, wQueen, wBishop, wKnight, wRook,
		wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn,
		bPawn, Empty, Empty, Empty, Empty, Empty, Empty, wBishop,
		Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
		Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
		Empty, wPawn, Empty, Empty, Empty, Empty, Empty, Empty,
		bPawn, bPawn, bPawn, bPawn, bPawn, Empty, bPawn, bPawn,
		bRook, bKnight, bBishop, bKing, bQueen, bBishop, bKnight, bRook,
	};
	for (int i = 0; i < 64; i++)
	{
		piece[i] = init_piece_test[i];
	}
	EXPECT_EQ(true, is_attacked(9, Black));
	EXPECT_EQ(true, is_attacked(12, Black));
	EXPECT_EQ(true, is_attacked(48, White));
	EXPECT_EQ(true, is_attacked(50, White));
	EXPECT_EQ(true, is_attacked(51, White));
	// Not attacked 
	EXPECT_EQ(false, is_attacked(49, White));
	EXPECT_EQ(false, is_attacked(56, White));
	EXPECT_EQ(false, is_attacked(63, White));
	EXPECT_EQ(false, is_attacked(62, White));
}


int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
