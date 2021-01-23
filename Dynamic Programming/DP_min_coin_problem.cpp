// Dynamic Programming- Coin Change 1
// You are given coins of different denominations and a total amount of money amount. 
// Write a program to compute the minimum number of coins that you need to make up that 
// amount. If that amount of money cannot be made up by any combination of the coins, return -1.

#include<iostream>
#include<limits.h>
#include<vector>
using namespace std;

int coinChange(vector<int>& coins, int remainder, vector<int>& dp) {
      
    if (remainder < 0) {
        return -1;
    }
    
    if (remainder == 0) {
        return 0;
    }
  
    if (dp[remainder] != 0) {
        return dp[remainder];
    }
  
    int minimum = INT_MAX;
    for (int coin: coins) {
        int changeResult = coinChange(coins, remainder - coin, dp);
  
        if (changeResult >= 0 && changeResult < minimum) {
            minimum = 1 + changeResult;
        }
    }
  
    dp[remainder] = (minimum == INT_MAX) ? -1 : minimum;
  
    return dp[remainder];
}

// Top Down Approach
int leastCoins(vector<int>& coins, int amount) {
    if (amount < 1) {
        return 0;
    }
      
    vector<int> dp(amount + 1);
    return coinChange(coins, amount, dp);
}

// Bottom-up Approach
int leastCoins2(vector<int>& coins, int amount){
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;

    for(int i=1; i<=amount; i++){
        for(int j=0; j<coins.size(); j++){
            if(coins[j]<=i){
                dp[i] = min(dp[i], 1+dp[i-coins[j]]);

            }
        }
    }

    return dp[amount] > amount ? -1 : dp[amount];
}

int main(){
    
    int amount = 12;
    vector<int> coins{1, 2, 4, 9};
    
    cout<<"Minimum no. of coins required (using Top-Down) for the amount "<<amount<<" are: "<<leastCoins(coins, amount);
    cout<<"\nMinimum no. of coins required (using Bottom-Up) for the amount "<<amount<<" are: "<<leastCoins2(coins, amount);

}