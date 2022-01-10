#include <queue>
#include <utility>
#include <vector>

using namespace std;

vector<priority_queue<pair<int, int>>> buyQueue, sellQueue;
vector<int> validTrade, quantities, minPrice, maxProfit;

int MAXPRICE = 1000000;

void init() {
    buyQueue = vector<priority_queue<pair<int, int>>>(6);   // pair (price , -1 * idx)
    sellQueue = vector<priority_queue<pair<int, int>>>(6);  // pair (-1 * price, -1 * idx)
    validTrade = vector<int>(1, 0);
    quantities = vector<int>(1, 0);
    minPrice = vector<int>(6, MAXPRICE + 100);
    maxProfit = vector<int>(6, 0);
}

int buy(int mNumber, int mStock, int mQuantity, int mPrice) {
    // set valid
    validTrade.push_back(1);
    // trading
    while (!sellQueue[mStock].empty()) {
        auto tmp = sellQueue[mStock].top();
        int price(tmp.first * -1), idx(tmp.second * -1), &quantity(quantities[idx]);
        if (price > mPrice) break;
        // trade
        if (quantity > mQuantity) {
            quantity -= mQuantity;
            mQuantity = 0;
            break;
        } else {
            mQuantity -= quantity;
            quantity = 0;
            sellQueue[mStock].pop();
        }
        maxProfit[mStock] = max(maxProfit[mStock], price - minPrice[mStock]);
        minPrice[mStock] = min(minPrice[mStock], price);
    }
    // set buyQueue and quantities
    if (mQuantity) buyQueue[mStock].push(make_pair(mPrice, -1 * mNumber));
    quantities.push_back(mQuantity);
    return mQuantity;
}

int sell(int mNumber, int mStock, int mQuantity, int mPrice) {
    // set valid
    validTrade.push_back(1);
    // trading
    while (!buyQueue[mStock].empty()) {
        auto tmp = buyQueue[mStock].top();
        int price(tmp.first), idx(tmp.second * -1), &quantity(quantities[idx]);
        if (price < mPrice) break;
        // trade
        if (quantity > mQuantity) {
            quantity -= mQuantity;
            mQuantity = 0;
            break;
        } else {
            mQuantity -= quantity;
            quantity = 0;
            buyQueue[mStock].pop();
        }
        maxProfit[mStock] = max(maxProfit[mStock], price - minPrice[mStock]);
        minPrice[mStock] = min(minPrice[mStock], price);
    }
    // set buyQueue and quantities
    if (mQuantity) sellQueue[mStock].push(make_pair(-1 * mPrice, -1 * mNumber));
    quantities.push_back(mQuantity);
    return mQuantity;
}

void cancel(int mNumber) { validTrade[mNumber] = 0; }

int bestProfit(int mStock) { return maxProfit[mStock]; }