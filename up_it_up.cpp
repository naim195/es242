#include <vector>
#include <array>
#include <algorithm>
#include <tuple>
#include <cstdio>

#include "queue.hpp"

struct Puzzle {
    int tiles[3][3];
};

long calc_order(const Puzzle& puzzle) {
    long order = 0;
    int power = 1;
    for (int row = 2; row >= 0; --row) {
        for (int col = 2; col >= 0; --col) {
            order += puzzle.tiles[row][col] * power;
            power *= 7;
        }
    }
    return order;
}

void read_puzzle(Puzzle& puzzle) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            scanf("%d", &puzzle.tiles[row][col]);
        }
    }
}

std::tuple<int, int> find_space(const Puzzle& puzzle) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (puzzle.tiles[row][col] == 0) {
                return {row, col};
            }
        }
    }
    assert(0);
    return {0, 0};
}

Puzzle move_up(const Puzzle& puzzle) {
    const std::tuple<int, int> space = find_space(puzzle);
    const int row = std::get<0>(space);
    const int col = std::get<1>(space);
    if (row == 2) {
        return puzzle;
    }
    Puzzle newPuzzle = puzzle;
    switch (newPuzzle.tiles[row + 1][col]) {
        case 1: newPuzzle.tiles[row][col] = 3; break;
        case 2: newPuzzle.tiles[row][col] = 2; break;
        case 3: newPuzzle.tiles[row][col] = 6; break;
        case 4: newPuzzle.tiles[row][col] = 4; break;
        case 5: newPuzzle.tiles[row][col] = 1; break;
        case 6: newPuzzle.tiles[row][col] = 5; break;
    }
    newPuzzle.tiles[row + 1][col] = 0;
    return newPuzzle;
}

Puzzle move_down(const Puzzle& puzzle) {
    const std::tuple<int, int> space = find_space(puzzle);
    const int row = std::get<0>(space);
    const int col = std::get<1>(space);
    if (row == 0) {
        return puzzle;
    }
    Puzzle newPuzzle = puzzle;
    switch (newPuzzle.tiles[row - 1][col]) {
        case 1: newPuzzle.tiles[row][col] = 5; break;
        case 2: newPuzzle.tiles[row][col] = 2; break;
        case 3: newPuzzle.tiles[row][col] = 1; break;
        case 4: newPuzzle.tiles[row][col] = 4; break;
        case 5: newPuzzle.tiles[row][col] = 6; break;
        case 6: newPuzzle.tiles[row][col] = 3; break;
    }
    newPuzzle.tiles[row - 1][col] = 0;
    return newPuzzle;
}

Puzzle move_left(const Puzzle& puzzle) {
    const std::tuple<int, int> space = find_space(puzzle);
    const int row = std::get<0>(space);
    const int col = std::get<1>(space);
    if (col == 2) {
        return puzzle;
    }
    Puzzle newPuzzle = puzzle;
    switch (newPuzzle.tiles[row][col + 1]) {
        case 1: newPuzzle.tiles[row][col] = 2; break;
        case 2: newPuzzle.tiles[row][col] = 6; break;
        case 3: newPuzzle.tiles[row][col] = 3; break;
        case 4: newPuzzle.tiles[row][col] = 1; break;
        case 5: newPuzzle.tiles[row][col] = 5; break;
        case 6: newPuzzle.tiles[row][col] = 4; break;
    }
    newPuzzle.tiles[row][col + 1] = 0;
    return newPuzzle;
}

Puzzle move_right(const Puzzle& puzzle) {
    const std::tuple<int, int> space = find_space(puzzle);
    const int row = std::get<0>(space);
    const int col = std::get<1>(space);
    if (col == 0) {
        return puzzle;
    }
    Puzzle newPuzzle = puzzle;
    switch (newPuzzle.tiles[row][col - 1]) {
        case 1: newPuzzle.tiles[row][col] = 4; break;
        case 2: newPuzzle.tiles[row][col] = 1; break;
        case 3: newPuzzle.tiles[row][col] = 3; break;
        case 4: newPuzzle.tiles[row][col] = 6; break;
        case 5: newPuzzle.tiles[row][col] = 5; break;
        case 6: newPuzzle.tiles[row][col] = 2; break;
    }
    newPuzzle.tiles[row][col - 1] = 0;
    return newPuzzle;
}

bool puzzle_equal_check(const Puzzle& a, const Puzzle& b) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (a.tiles[row][col] != b.tiles[row][col]) {
                return false;
            }
        }
    }
    return true;
}

enum Move { LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4 };

#define MAX_ORD (40353600)
std::vector<int> solve(const Puzzle& src, const Puzzle& dest) {
    queue<Puzzle, MAX_ORD> puzzleQueue;
    int visited[MAX_ORD];
    Puzzle parent[MAX_ORD];

    enqueue(puzzleQueue, src);
    visited[calc_order(src)] = LEFT;

    while (!is_empty(puzzleQueue)) {
        Puzzle currentPuzzle = dequeue(puzzleQueue);
        if (puzzle_equal_check(currentPuzzle, dest)) {
            std::vector<int> moves;
            Puzzle puzzle = currentPuzzle;
            int order = calc_order(puzzle);
            while (!puzzle_equal_check(puzzle, src)) {
                moves.push_back(visited[order]);
                puzzle = parent[order];
                order = calc_order(puzzle);
            }
            std::reverse(moves.begin(), moves.end());
            return moves;
        }

        Puzzle move_upResult = move_up(currentPuzzle);
        Puzzle move_downResult = move_down(currentPuzzle);
        Puzzle move_leftResult = move_left(currentPuzzle);
        Puzzle move_rightResult = move_right(currentPuzzle);

        int upOrder = calc_order(move_upResult);
        int downOrder = calc_order(move_downResult);
        int leftOrder = calc_order(move_leftResult);
        int rightOrder = calc_order(move_rightResult);

        if (!visited[upOrder]) {
            visited[upOrder] = UP;
            parent[upOrder] = currentPuzzle;
            enqueue(puzzleQueue, move_upResult);
        }
        if (!visited[downOrder]) {
            visited[downOrder] = DOWN;
            parent[downOrder] = currentPuzzle;
            enqueue(puzzleQueue, move_downResult);
        }
        if (!visited[leftOrder]) {
            visited[leftOrder] = LEFT;
            parent[leftOrder] = currentPuzzle;
            enqueue(puzzleQueue, move_leftResult);
        }
        if (!visited[rightOrder]) {
            visited[rightOrder] = RIGHT;
            parent[rightOrder] = currentPuzzle;
            enqueue(puzzleQueue, move_rightResult);
        }
    }

    printf("\nPuzzle is not solvable\n");
    return { 0 };
}

void printMoves(const std::vector<int>& moves) {
    for (auto move : moves) {
        switch (move) {
        case LEFT: printf("LEFT "); break;
        case RIGHT: printf("RIGHT "); break;
        case UP: printf("UP "); break;
        case DOWN: printf("DOWN "); break;
        }
    }
    printf("\n");
}

int main() {
    Puzzle sourcePuzzle, destinationPuzzle;

    read_puzzle(sourcePuzzle);
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            destinationPuzzle.tiles[row][col] = 1;
        }
    }
    destinationPuzzle.tiles[1][1] = 0;

    auto moves = solve(sourcePuzzle, destinationPuzzle);
    printMoves(moves);

    return 0;
}
