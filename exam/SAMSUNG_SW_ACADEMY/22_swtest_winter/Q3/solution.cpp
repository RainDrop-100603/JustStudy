#define MISS 0
#define CARRIER 1
#define BATTLESHIP 2
#define CRUISER 3
#define SUBMARINE 4
#define DESTROYER 5

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

vector<vector<int>> boards;  // -1: none, 0: MISS, 1~5: ships
vector<int> shipsRemain;
vector<int> shipsSize = {0, 5, 4, 3, 3, 2};

int DIR_UP = 0;
int DIR_LEFT = 1;
int DIR_DOWN = 2;
int DIR_RIGHT = 3;

extern int fire(int r, int c);

int spaceRemain(int row, int col, int direction, int value = -1) {
    int count = 0;
    if (direction == DIR_UP) {
        row--;
        while (row >= 0 && (boards[row][col] == -1 || boards[row][col] == value)) {
            count++;
            row--;
        }
    } else if (direction == DIR_LEFT) {
        col--;
        while (col >= 0 && (boards[row][col] == -1 || boards[row][col] == value)) {
            count++;
            col--;
        }
    } else if (direction == DIR_DOWN) {
        row++;
        while (row < 10 && (boards[row][col] == -1 || boards[row][col] == value)) {
            count++;
            row++;
        }
    } else if (direction == DIR_RIGHT) {
        col++;
        while (col < 10 && (boards[row][col] == -1 || boards[row][col] == value)) {
            count++;
            col++;
        }
    }
    return count;
}
bool fireHeuristic(int row, int col, int smallestShipSize) {
    if (spaceRemain(row, col, DIR_UP) + 1 >= smallestShipSize) return true;
    if (spaceRemain(row, col, DIR_LEFT) + 1 >= smallestShipSize) return true;
    return false;
}
void repeatFire(int row, int col, int& currentSize, int remain, int up, int down, int left, int right) {
    int ship = boards[row][col];
    int shipSize = shipsSize[ship];
    for (int i = 1; i <= remain; i++) {
        if (currentSize == shipSize) return;
        int tmpRow = row + i * down - i * up;
        int tmpCol = col + i * right - i * left;
        int ret = fire(tmpRow, tmpCol);
        boards[tmpRow][tmpCol] = ret;
        if (ret != ship) {
            return;
        } else {
            currentSize++;
        }
    }
}
void findShip(int row, int col) {
    int ship = boards[row][col];
    int shipSize = shipsSize[ship];
    shipsRemain[ship] = 0;
    // check remain space
    int spaceUp = spaceRemain(row, col, DIR_UP, ship);
    int spaceDown = spaceRemain(row, col, DIR_DOWN, ship);
    int spaceLeft = spaceRemain(row, col, DIR_LEFT, ship);
    int spaceRight = spaceRemain(row, col, DIR_RIGHT, ship);
    // find ship
    int currentSize = 1;
    if (1 + spaceDown + spaceUp >= shipSize) {
        // col check
        repeatFire(row, col, currentSize, spaceUp, 1, 0, 0, 0);
        repeatFire(row, col, currentSize, spaceDown, 0, 1, 0, 0);
    }
    if (currentSize == shipSize) return;
    // row check
    repeatFire(row, col, currentSize, spaceLeft, 0, 0, 1, 0);
    repeatFire(row, col, currentSize, spaceRight, 0, 0, 0, 1);
}

void init(int limit) {}

void play() {
    // init
    boards = vector<vector<int>>(10, vector<int>(10, -1));
    shipsRemain = vector<int>{0, 1, 1, 1, 1, 1};
    // fire
    int idx = 0;
    while (true) {
        int smallestShip = 0;
        for (int i = 5; i > 0; i--) {
            if (shipsRemain[i]) {
                smallestShip = i;
                break;
            }
        }
        if (smallestShip == 0) break;
        // shooting
        int row = idx / 10, col = idx % 10;
        int& nowPoint = boards[row][col];
        if (nowPoint == -1 && fireHeuristic(row, col, shipsSize[smallestShip])) nowPoint = fire(row, col);
        // point feedback
        if (nowPoint != 0 && shipsRemain[nowPoint]) findShip(row, col);
        idx++;
    }

    // cout << "---------------\n";
    // for (auto& ele : boards) {
    //     for (auto& ele2 : ele) {
    //         cout << ele2;
    //     }
    //     cout << endl;
    // }
}