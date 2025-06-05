#include "pch.h"
#include "CppUnitTest.h"
#include "../CPPkursach2/CPPkursach2.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestRookPolynomials
{
	TEST_CLASS(UnitTestRookPolynomials)
	{
	public:
		
		TEST_METHOD(TestIsValidPlacement)
		{
			vector<pair<int, int>> squares = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
			ChessBoard board(squares);

			//валидная расстановка (ладьи друг друга не бьют)
			vector<pair<int, int>> validRooks = { {0, 0}, {1, 1} };
			Assert::IsTrue(board.isValidPlacement(validRooks));

			//невалидная расстановка
			vector<pair<int, int>> invalidRooks = { {0, 0}, {1, 0} };
			Assert::IsFalse(board.isValidPlacement(invalidRooks));
		}

		TEST_METHOD(TestCountRookPlacements)
		{
			vector<pair<int, int>> squares = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
			ChessBoard board(squares);

			//0 ладей (должен быть 1 вариант расставить 0 ладей)
			Assert::AreEqual(1, board.countRookPlacements(0));

			//1 ладья (4 варианта - по одной в клетке)
			Assert::AreEqual(4, board.countRookPlacements(1));

			//2 ладьи (2 варианта, 2 диагонали)
			Assert::AreEqual(2, board.countRookPlacements(2));

			//3 ладьи (0 вариантов)
			Assert::AreEqual(0, board.countRookPlacements(3));
		}

		TEST_METHOD(TestRookPolynomial)
		{
			vector<pair<int, int>> squares = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
			ChessBoard board(squares);

			vector<int> expected = { 1, 4, 2, 0, 0 }; 
			vector<int> actual = board.rookPolynomial(4);

			Assert::AreEqual(expected.size(), actual.size());
			for (size_t i = 0; i < expected.size(); i++)
			{
				Assert::AreEqual(expected[i], actual[i]);
			}
		}

		TEST_METHOD(TestInvalidInputRecovery)
		{
			//производим сначала некорректный ввод, потом корректный
			stringstream fakeInput("a b\n1 2, 3 4");
			streambuf* oldCin = cin.rdbuf(fakeInput.rdbuf());

			vector<pair<int, int>> squares;
			string input;
			bool validInput = false;

			do {
				getline(cin, input);
				stringstream ss(input);
				int x, y;
				validInput = true;

				while (ss >> x >> y) {
					squares.push_back({ x, y });
					if (ss.peek() == ',') ss.ignore();
				}

				if (ss.fail() && !ss.eof()) {
					validInput = false;
					squares.clear();
					cout << "Некорректный ввод. Пожалуйста, введите координаты заново: ";
				}
			} while (!validInput);

			Assert::AreEqual(2, (int)squares.size());
			Assert::AreEqual(1, squares[0].first);
			Assert::AreEqual(2, squares[0].second);
			Assert::AreEqual(3, squares[1].first);
			Assert::AreEqual(4, squares[1].second);

			cin.rdbuf(oldCin);
		}
	};
}
