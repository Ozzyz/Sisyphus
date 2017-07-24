

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Sisyphus/board.h"
#include "../Sisyphus/fen.h"


namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template <> static std::wstring ToString<Color>(const Color& c) { return (c == Black ? L"Black" : L"White"); }
		}
	}
}
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;
namespace SisyphusTest
{
	TEST_CLASS(FenTest)
	{
	private:
		Board boardc;

	public:
		TEST_METHOD_INITIALIZE(Setup_Board)
		{
			// Setup default start board
			boardc = Board();
		}

		TEST_METHOD(Parse_En_Passant_Fen_With_Castling)
		{
			string ep_fen = "rnbqkbnr/ppp1pppp/8/8/3pP3/2N3P1/PPPP1P1P/R1BQKBNR b KQkq e3 0 3";
			parse_fen(ep_fen, boardc);
			// Correct player to move next
			Color to_move = Black;
			Assert::AreEqual(to_move, boardc.get_to_move(), L"Next player to move");
			// Check that the en passant square is set to e3
			Assert::AreEqual(square_to_board_index("e3"), boardc.get_ep_square(), L"Could not find ep-square e3");
			// Check that all castling permissions are intact
			int castling = wCastleKing | wCastleQueen | bCastleKing | bCastleQueen;
			Assert::AreEqual(castling, boardc.get_castling_rights(), L"Castle rights are not equal");
			// Turns 
			int turns = 0;
			Assert::AreEqual(turns, boardc.get_turn());
		}
		TEST_METHOD(Parse_Starting_Board)
		{
			string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
			parse_fen(starting_fen, boardc);
			for (int square = 0; square < 64; square++)
			{
				Assert::AreEqual((int)init_piece[square], boardc.board[square], std::to_wstring(square).c_str());
			}
			// 
		}
		
	};
}