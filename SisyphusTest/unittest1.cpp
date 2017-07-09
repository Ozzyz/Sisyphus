#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Sisyphus/board.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SisyphusTest
{
	TEST_CLASS(UnitTest1)
	{
	public:
		// TODO: Check rook, knight and king attacks
		TEST_METHOD_INITIALIZE(Setup_Board)
		{
			// Testboard: https://lichess.org/editor/r1bqkb1r/ppp1pppp/2n3P1/Q5Rn/8/B6p/PPPPPPPP/RN2KBN1_w_KQkq_-
			Piece testboard[64] = {
				Empty, wKnight, wBishop, wKing, Empty, Empty, wKnight, wRook,
				wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn,
				bPawn, Empty, Empty, Empty, Empty, Empty, Empty, wBishop,
				Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
				bKnight, wRook, Empty, Empty, Empty, Empty, Empty, wQueen,
				Empty, wPawn, Empty, Empty, Empty, bKnight, Empty , Empty,
				bPawn, bPawn, bPawn, bPawn, Empty, bPawn, bPawn, bPawn,
				bRook, bKnight, bBishop, bKing, bQueen, bBishop, Empty, bRook,
			};
			init_board(testboard);
		}


		TEST_METHOD(Verify_G6_Pawn_Attacks_Two_Squares)
		{
			Assert::AreEqual(true, is_attacked(48, White));
			Assert::AreEqual(true, is_attacked(50, White));
			
			
			//Assert::AreEqual(true, is_attacked(12, Black));
			//// Squares that should not be attacked
			//Assert::AreEqual(false, is_attacked(0, Black));
			//Assert::AreEqual(false, is_attacked(1, Black));
			//Assert::AreEqual(false, is_attacked(5, Black));
		}
		TEST_METHOD(Verify_H3_Pawn_Attacks_One_Square)
		{
			Assert::AreEqual(true, is_attacked(9, Black));
			Assert::AreEqual(false, is_attacked(11, Black));
		}
		TEST_METHOD(Verify_A3_Bishop_Attacks_One_Square_On_Diagonal)
		{
			Assert::AreEqual(true, is_attacked(51, White));
			Assert::AreEqual(false, is_attacked(58, White));

		}
		TEST_METHOD(Verify_C6_Knight_Attacks_Multiple_Squares)
		{
			Assert::AreEqual(true, is_attacked(62, Black), L"B8-square");
			Assert::AreEqual(true, is_attacked(55, Black), L"A7-square");
			Assert::AreEqual(true, is_attacked(39, Black), L"A5-square");
		}

	};
}