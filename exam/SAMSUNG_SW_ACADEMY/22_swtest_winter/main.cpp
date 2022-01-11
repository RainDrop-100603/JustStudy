#include <iostream>
#include <vector>

using namespace std;

vector<int> shipsRemain;

int main() {
    shipsRemain.push_back(15);
    shipsRemain.push_back(15);
    shipsRemain.push_back(15);
    shipsRemain = vector<int>{5, 4, 3, 2, 1};
    for (auto& ele : shipsRemain) {
        cout << ele << endl;
    }
    return 0;
}