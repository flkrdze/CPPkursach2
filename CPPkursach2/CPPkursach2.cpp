#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <sstream>
#include <string>

using namespace std;

class ChessBoard {
private:
    vector<pair<int, int>> validSquares;
    int maxRow, maxCol; 

public:
    //конструктор принимает вектор валидных клеток
    ChessBoard(const vector<pair<int, int>>& squares) {
        validSquares = squares;
        maxRow = 0;
        maxCol = 0;
        for (const auto& square : validSquares) {
            maxRow = max(maxRow, square.first);
            maxCol = max(maxCol, square.second);
        }
    }

    //проверка доски на соответствие условию (ладьи не бьют друг друга)
    bool isValidPlacement(const vector<pair<int, int>>& rooks) {
        set<int> rows, cols;
        for (const pair<int, int>& rook : rooks) {
            int i = rook.first;
            int j = rook.second;
            if (rows.count(i) || cols.count(j))
                return false;
            rows.insert(i);
            cols.insert(j);
        }
        return true;
    }

    //счёт ладейного числа
    int countRookPlacements(int k) {
        if (k > validSquares.size()) return 0;

        int count = 0;
        vector<pair<int, int>> current;
        countRookCombinations(k, 0, current, count);
        return count;
    }

    //генерация всех вариантов расстановок ладей
    void countRookCombinations(int k, int start, vector<pair<int, int>>& current, int& count) {
        if (current.size() == k) {
            if (isValidPlacement(current)) {
                count++;
            }
            return;
        }
        for (int i = start; i < validSquares.size(); i++) {
            current.push_back(validSquares[i]);
            countRookCombinations(k, i + 1, current, count);
            current.pop_back();
        }
    }

    //в векторе возвращаем коэффициенты ладейного многочлена 
    vector<int> rookPolynomial(int maxRooks) {
        vector<int> polynomial(maxRooks + 1, 0);
        for (int k = 0; k <= maxRooks; k++) {
            polynomial[k] = countRookPlacements(k);
        }
        return polynomial;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    vector<pair<int, int>> squares;
    string input;
    cout << "Введите координаты клеток (например, 0 0, 0 1, 1 1): ";
    getline(cin, input);
    stringstream ss(input);
    int x, y;

    //чтение координат
    while (ss >> x >> y) {
        squares.push_back({ x, y });
        if (ss.peek() == ',') {
            ss.ignore();
        }
    }

    ChessBoard chessBoard(squares);

    int maxRooks;
    cout << "Введите максимальное количество ладей: ";
    while (!(cin >> maxRooks) || maxRooks < 0) {
        cout << "Пожалуйста, введите корректное число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }

    vector<int> polynomial = chessBoard.rookPolynomial(maxRooks);

    cout << "Ладейный многочлен: ";
    for (int i = 0; i <= maxRooks; i++) {
        cout << polynomial[i] << "*x^" << i;
        if (i < maxRooks) {
            cout << " + ";
        }
    }
    cout << endl;

    return 0;
}
