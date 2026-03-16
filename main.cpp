#include <bits/stdc++.h>

using namespace std;

int main() {
    int bx, by, mx, my;
    cin >> bx >> by >> mx >> my;
    vector<int> mlx = {0, -1, 1,2, -2, -2, -1, 2, 1};
    vector<int> mly = {0, 2, 2, 1, 1, -1, -2, -1, -2};
    vector<vector<long long>> dp(30, vector<long long>(30, 0));
    vector<vector<bool>> checker(30, vector<bool>(30, false));
    
    bx += 2; by += 2; mx += 2; my += 2;

    for (int i = 1; i <= 8; i ++)
        checker[mx + mlx[i]][my + mly[i]] = true;
    checker[mx][my] = true;
    
    dp[2][1] = 1;
    
    for (int i = 2; i <= bx; i ++) {
        for (int j = 2; j <= by; j ++) {
            if (checker[i][j]) continue;

            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }

    cout << dp[bx][by] << endl;
}