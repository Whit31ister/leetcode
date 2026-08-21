class SolutionBrute {
    public int maxProfit(int[] prices) {
        int bestProfit = 0;

        for (int buy = 0; buy < prices.length; buy++) {
            for (int sell = buy + 1; sell < prices.length; sell++) {
                bestProfit = Math.max(bestProfit, prices[sell] - prices[buy]);
            }
        }
        return bestProfit;
    }
}

class Solution {
    public int maxProfit(int[] prices) {
        int lowestPrice = prices[0];
        int bestProfit = 0;

        for (int price : prices) {
            lowestPrice = Math.min(lowestPrice, price);
            bestProfit = Math.max(bestProfit, price - lowestPrice);
        }
        return bestProfit;
    }
}
