#include <cstdio>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <tuple>
#include <iostream>
#include <queue>
#include <cmath>
#include <cassert>
#include <utility>
using namespace std;

struct Cubie {
    int edges[7];
};

struct col_block {
    char colors[6][4];
};

Cubie TranslateToCubie(const col_block& colorBlock) {
    Cubie result;
    string s;
    string possibleColors[21] = {
        "rgw", "wrg", "gwr", "rwb", "brw", "wbr",
        "ryg", "gry", "ygr", "rby", "yrb", "byr",
        "owg", "gow", "wgo", "obw", "wob", "bwo",
        "oyb", "boy", "ybo"
    };
    s.push_back(colorBlock.colors[0][0]);
    s.push_back(colorBlock.colors[3][1]);
    s.push_back(colorBlock.colors[4][2]);
    
    for (int i = 0; i < 21; i++) {
        if (s == possibleColors[i]) {
            result.edges[i / 3] = (0) * 3 + (i % 3);
        }
    }
    
    s.clear();
    s.push_back(colorBlock.colors[0][1]);
    s.push_back(colorBlock.colors[4][3]);
    s.push_back(colorBlock.colors[1][0]);
    
    for (int i = 0; i < 21; i++) {
        if (s == possibleColors[i]) {
            result.edges[i / 3] = (1) * 3 + (i % 3);
        }
    }
    
    s.clear();
    s.push_back(colorBlock.colors[0][2]);
    s.push_back(colorBlock.colors[5][0]);
    s.push_back(colorBlock.colors[3][3]);
    
    for (int i = 0; i < 21; i++) {
        if (s == possibleColors[i]) {
            result.edges[i / 3] = (2) * 3 + (i % 3);
        }
    }
    
    s.clear();
    s.push_back(colorBlock.colors[0][3]);
    s.push_back(colorBlock.colors[1][2]);
    s.push_back(colorBlock.colors[5][1]);
    
    for (int i = 0; i < 21; i++) {
        if (s == possibleColors[i]) {
            result.edges[i / 3] = (3) * 3 + (i % 3);
        }
    }
    
    s.clear();
    s.push_back(colorBlock.colors[2][0]);
    s.push_back(colorBlock.colors[4][0]);
    s.push_back(colorBlock.colors[3][0]);
    
    for (int i = 0; i < 21; i++) {
        if (s == possibleColors[i]) {
            result.edges[i / 3] = (4) * 3 + (i % 3);
        }
    }
    
    s.clear();
    s.push_back(colorBlock.colors[2][1]);
    s.push_back(colorBlock.colors[1][1]);
    s.push_back(colorBlock.colors[4][1]);
    
    for (int i = 0; i < 21; i++) {
        if (s == possibleColors[i]) {
            result.edges[i / 3] = (5) * 3 + (i % 3);
        }
    }
    
    s.clear();
    s.push_back(colorBlock.colors[2][3]);
    s.push_back(colorBlock.colors[5][3]);
    s.push_back(colorBlock.colors[1][3]);
    
    for (int i = 0; i < 21; i++) {
        if (s == possibleColors[i]) {
            result.edges[i / 3] = (6) * 3 + (i % 3);
        }
    }
    
    return result;
}

void print_cubie(const Cubie& cublet) {
    for (int r = 0; r < 7; ++r) {
        printf("%3d", cublet.edges[r]);
    }
    printf("\n");
}

void Readcol_block(col_block& colorBlock) {
    for (int r = 0; r < 6; ++r) {
        for (int cl = 0; cl < 4; ++cl) {
            scanf("%s", &colorBlock.colors[r][cl]);
        }
    }
}

Cubie RotateFront(const Cubie& cublet) {
    Cubie rotatedCubie = cublet;
    int rotationOrder[21] = {3, 4, 5, 9, 10, 11, 0, 1, 2, 6, 7, 8, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    
    for (int i = 0; i < 7; i++) {
        rotatedCubie.edges[i] = rotationOrder[rotatedCubie.edges[i]];
    }
    
    return rotatedCubie;
}

Cubie RotateRight(const Cubie& cublet) {
    Cubie rotatedCubie = cublet;
    int rotationOrder[21] = {0, 1, 2, 17, 15, 16, 6, 7, 8, 4, 5, 3, 12, 13, 14, 19, 20, 18, 11, 9, 10};
    
    for (int i = 0; i < 7; i++) {
        rotatedCubie.edges[i] = rotationOrder[rotatedCubie.edges[i]];
    }
    
    return rotatedCubie;
}

Cubie RotateUp(const Cubie& cublet) {
    Cubie rotatedCubie = cublet;
    int rotationOrder[21] = {14, 12, 13, 1, 2, 0, 6, 7, 8, 9, 10, 11, 16, 17, 15, 5, 3, 4, 18, 19, 20};
    
    for (int i = 0; i < 7; i++) {
        rotatedCubie.edges[i] = rotationOrder[rotatedCubie.edges[i]];
    }
    
    return rotatedCubie;
}

enum MoveType { ROTATE_RIGHT = 1, ROTATE_UP = 2, ROTATE_FRONT = 3, ROTATE_RIGHT_2 = 4, ROTATE_UP_2 = 5, ROTATE_FRONT_2 = 6, ROTATE_RIGHT_1 = 7, ROTATE_UP_1 = 8, ROTATE_FRONT_1 = 9 };

int Order(const Cubie& cublet) {
    int value = 0;
    int k = 6;
    
    for (int r = 0; r < 7; ++r) {
        int v = cublet.edges[r];
        value += v * pow(21, k);
        k -= 1;
    }
    
    return value;
}

Cubie Decode(int order) {
    Cubie node;
    int temp = order;
    
    for (int r = 6; r >= 0; r--) {
        node.edges[r] = temp % 21;
        temp = temp / 21;
    }
    
    return node;
}

#define MAX_MOVES (1800000000) 
std::vector<int> Solve(const Cubie& srcCubie, const Cubie& destCubie) {
    queue<int> moveQueue;
    int visited[MAX_MOVES];
    int parent[MAX_MOVES];
    int initialOrder = Order(srcCubie);
    int finalOrder = Order(destCubie);
    moveQueue.push(Order(srcCubie));
    visited[Order(srcCubie)] = ROTATE_UP;
    int temp = 0;
    
    while (!moveQueue.empty()) {
        int childOrder = moveQueue.front();
        moveQueue.pop();
        Cubie currentCubie = Decode(childOrder);
        
        if (childOrder == finalOrder) {
            std::vector<int> moves;
            
            while (childOrder != initialOrder) {
                moves.push_back(visited[childOrder]);
                childOrder = parent[childOrder];
            }
            
            std::reverse(moves.begin(), moves.end());
            std::vector<int> resultMoves;
            int previousMove = 0;
            
            for (auto currentMove : moves) {
                auto tempMove = currentMove;
                
                if (currentMove == previousMove) {
                    int flag = resultMoves.back();
                    resultMoves.pop_back();
                    
                    if (flag == currentMove) {
                        tempMove += 3;
                    }
                    else {
                        tempMove += 6;
                    }
                }
                
                previousMove = currentMove;
                resultMoves.push_back(tempMove);
            }
            
            return resultMoves;
        }
        
        Cubie rotatedFront = RotateFront(currentCubie);
        Cubie rotatedRight = RotateRight(currentCubie);
        Cubie rotatedUp = RotateUp(currentCubie);
        
        int frontOrder = Order(rotatedFront);
        int rightOrder = Order(rotatedRight);
        int upOrder = Order(rotatedUp);
        
        if (!visited[frontOrder]) {
            visited[frontOrder] = ROTATE_FRONT;
            parent[frontOrder] = childOrder;
            moveQueue.push(frontOrder);
        }
        
        if (!visited[rightOrder]) {
            visited[rightOrder] = ROTATE_RIGHT;
            parent[rightOrder] = childOrder;
            moveQueue.push(rightOrder);
        }
        
        if (!visited[upOrder]) {
            visited[upOrder] = ROTATE_UP;
            parent[upOrder] = childOrder;
            moveQueue.push(upOrder);
        }
        
        temp += 1;
    }
    
    return std::vector<int>();
    assert(0);
}

void print_moves(const std::vector<int>& moves) {
    for (auto move : moves) {
        switch (move) {
            case ROTATE_UP: printf("U "); break;
            case ROTATE_FRONT: printf("F "); break;
            case ROTATE_RIGHT: printf("R "); break;
            case ROTATE_UP_1: printf("U' "); break;
            case ROTATE_FRONT_1: printf("F' "); break;
            case ROTATE_RIGHT_1: printf("R' "); break;
            case ROTATE_UP_2: printf("U2 "); break;
            case ROTATE_FRONT_2: printf("F2 "); break;
            case ROTATE_RIGHT_2: printf("R2 "); break;
        }
    }
    
    printf("\n");
}

int main() {
    Cubie destinationCubie;
    col_block sourcecol_block;
    
    Readcol_block(sourcecol_block);
    Cubie sourceCubie = TranslateToCubie(sourcecol_block);
    
    for (int i = 0; i < 7; i++) {
        destinationCubie.edges[i] = i * 3;
    }
    
    printf("\n");
    printf("Start cublet configuration is:");
    print_cubie(sourceCubie);
    printf("\n");
    printf("End cublet configuration is:");
    print_cubie(destinationCubie);
    printf("\n");
    
    auto moves = Solve(sourceCubie, destinationCubie);
    print_moves(moves);
    
    return 0;
}
