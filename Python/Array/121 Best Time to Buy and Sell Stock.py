# Input: prices = [7,1,5,3,6,4]
# Output: 5

# Brute Force
class Solution_Brute:
    def maxProfit(self, prices: list[int]) -> int:
        best_profit = 0

        for buy in range(len(prices)):
            for sell in range(buy + 1, len(prices)):
                best_profit = max(best_profit, prices[sell] - prices[buy])

        return best_profit


# Optimal Solution - One Pass
class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        lowest_price = float("inf")
        best_profit = 0

        for price in prices:
            lowest_price = min(lowest_price, price)
            best_profit = max(best_profit, price - lowest_price)

        return best_profit


# Local Testing
prices = [7, 1, 5, 3, 6, 4]
sol = Solution()
print(sol.maxProfit(prices))
