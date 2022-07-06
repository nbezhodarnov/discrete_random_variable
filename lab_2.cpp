#include <iostream>
#include <vector>

static int y = 0;
static const unsigned long Y_VALUE_LIMIT = (unsigned long)1 << (sizeof(y) * 8 - 1);

// Генератор псевдослучайных чисел (равномерное распределение на отрезке [0, 1])
double rnd() {
    y *= 843314861;
    y += 453816693;
    if (y < 0) {
        y += Y_VALUE_LIMIT;
    }
    return double(y) / double(Y_VALUE_LIMIT - 1);
}

// Генератор псевдослучайных чисел (дискретная случайная величина с элементами A[i] и вероятностями p[i])
template<class T> T dsv(const std::vector<double> &p, const std::vector<T> &A) {
    double alpha = rnd();
    for (unsigned int i = 0; i < p.size(); i++) {
        alpha -= p[i];
        if (alpha < 0) {
            return A[i];
        }
    }
    return A[A.size() - 1];
}

// Игра камень-ножницы-бумага-колодец

enum GameThings {
    Stone,
    Scissors,
    Paper,
    Well
};

int PlayGame(const GameThings &first, const GameThings &second) {
    if (first == second) {
        return 0;
    }
    if ((first == Stone && second == Scissors) || (first == Paper && second != Scissors) || (first == Well && second != Paper)) {
        return 1;
    }
    return -1;
}

int main() {
    unsigned int N = 100;
    const std::vector<double> p(4, 0.25); // Вероятности выбора предмета
    const std::vector<GameThings> A = {Stone, Scissors, Paper, Well}; // 1 - камень, 2 - ножницы, 3 - бумага, 4 - колодец
    GameThings first_player, second_player;
    int sum_first = 0, sum_second = 0;
    for (unsigned int i = 0; i < N; i++) {
        first_player = dsv<GameThings>(p, A);
        second_player = dsv<GameThings>(p, A);
        int first_prize = PlayGame(first_player, second_player);
        sum_first += first_prize;
        sum_second -= first_prize;
    }
    std::cout << "There has been played " << N << " games.\n";
    std::cout << "First player score: " << sum_first << '\n';
    std::cout << "Second player score: " << sum_second << '\n';
    std::cout << "First player average win: " << sum_first / (double)N << '\n';
    std::cout << "Second player average win: " << sum_second / (double)N << '\n';
    return 0;
}
