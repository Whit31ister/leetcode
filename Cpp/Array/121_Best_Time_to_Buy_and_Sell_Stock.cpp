#include <algorithm>
#include <vector>

using namespace std;

class Solution_Brute {
public:
    int maxProfit(vector<int>& prices) {
        int bestProfit = 0;

        for (size_t buy = 0; buy < prices.size(); buy++) {
            for (size_t sell = buy + 1; sell < prices.size(); sell++) {
                bestProfit = max(bestProfit, prices[sell] - prices[buy]);
            }
        }

        return bestProfit;
    }
};

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int lowestPrice = prices[0];
        int bestProfit = 0;

        for (int price : prices) {
            lowestPrice = min(lowestPrice, price);
            bestProfit = max(bestProfit, price - lowestPrice);
        }

        return bestProfit;
    }
};

int main() {
    Solution sol;
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    int result = sol.maxProfit(prices);
    (void)result;
    return 0;
}
