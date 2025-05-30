#include <iostream>
#include <vector>
#include <set>
#include <utility>

using namespace std;

class ChessBoard {
private:
    int m, n;
    vector<vector<bool>> board;

public:
    ChessBoard(int m, int n) : m(m), n(n) {
        board.resize(m, vector<bool>(n, true));
    }

    //проверка доски на соответствие условию (ладьи не бьют друг друга)
    bool isValidPlacement(const vector<pair<int, int>>& rooks) {
        set<int> rows, cols;
        for (const pair<int, int>& rook : rooks) {
            int i = rook.first;
            int j = rook.second;
            if (!board[i][j] || rows.count(i) || cols.count(j))
                return false;
            rows.insert(i);
            cols.insert(j);
        }
        return true;
    }

    //счёт ладейного числа
    int countRookPlacements(int k) {
        if (k > min(m, n)) return 0;

        vector<pair<int, int>> validSquares;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j])
                    validSquares.push_back({ i, j });

        int count = 0;

        vector<pair<int, int>> current;
        countRookCombinations(validSquares, k, 0, current, count);
        return count;
    }

    //генерация всех вариантов расстановок ладей
    void countRookCombinations(const vector<pair<int, int>>& validSquares, int k, int start,
        vector<pair<int, int>>& current, int& count) {
        if (current.size() == k) {
            if (isValidPlacement(current)) {
                count++;
            }
            return;
        }
        for (int i = start; i < validSquares.size(); i++) {
            current.push_back(validSquares[i]);
            countRookCombinations(validSquares, k, i + 1, current, count);
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
    int m, n;
    cout << "Введите размеры доски (m n): ";
    cin >> m >> n;

    ChessBoard chessBoard(m, n);

    int maxRooks;
    cout << "Введите максимальное количество ладей: ";
    cin >> maxRooks;

    vector<int> polynomial = chessBoard.rookPolynomial(maxRooks);

    cout << "Ладейный многочлен: ";
    for (int i = 0; i <= maxRooks; i++) {
        cout << polynomial[i] << "*x^" << i;
        if (i < maxRooks) {
            cout << " + ";
        }
    }
    cout << endl;

    return 1;
}
