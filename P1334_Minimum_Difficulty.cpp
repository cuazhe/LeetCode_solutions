class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        size_t n = jobDifficulty.size();
        vector<vector<int>> look_up(n, vector<int>(n, -1));
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (j == i) {
                    look_up[i][j] = jobDifficulty[i];
                }
                else {
                    look_up[i][j] = max(look_up[i][j - 1], jobDifficulty[j]);
                }
            }
        }
        vector<vector<int>> dp(n, vector<int>(d + 1, 300 * 1000));
        for (int i = 0; i < n; i++) {
            dp[i][1] = look_up[0][i];
            for (int j = 2; j < min(i + 2, d + 1); j++) {
                for (int k = j - 2; k < i; k++) {
                    dp[i][j] = min(dp[i][j], dp[k][j - 1] + look_up[k + 1][i]);
                }
            }
        }
        if (dp[n - 1][d] == 300 * 1000) {
            return -1;
        }
        return dp[n - 1][d];
    }
    
    int getMax(vector<int> arr) {
        int cur = arr[0];
        for (auto c: arr) {
            cur = max(cur, c);
        }
        return cur;
    }
};
