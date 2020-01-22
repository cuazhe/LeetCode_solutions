class Solution {
public:
    int minimumDistance(string word) {
        size_t n = word.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(26, vector<int>(26, INT_MAX)));
        int res = INT_MAX;
        if (n <= 1) {
            return 0;
        }
        for (size_t i = 0; i < n; i++) {
            int idx = word[i] - 'A';
            if (i == 0) {
                for (int j = 0; j < 26; j++) {
                    dp[i][idx][j] = 0;
                    dp[i][j][idx] = 0;
                }
            }
            else {
                for (int j = 0; j < 26; j++) {
                    for (int k = 0; k < 26; k++) {
                        if (dp[i - 1][j][k] != INT_MAX) {
                            dp[i][idx][k] = min(dp[i][idx][k], dp[i - 1][j][k] + get_dist(j, idx));
                            dp[i][j][idx] = min(dp[i][j][idx], dp[i - 1][j][k] + get_dist(k, idx));
                        }
                        if (i == n - 1) {
                            res = min(res, dp[i][idx][k]);
                            res = min(res, dp[i][j][idx]);
                        }
                    }
                }
            }
        }
        return res;
    }
    
    int get_dist(int a, int b) {
        pair<int, int> coord_a = get_coordi(a);
        pair<int, int> coord_b = get_coordi(b);
        return abs(coord_a.first - coord_b.first) + abs(coord_a.second - coord_b.second);
    }
    
    pair<int, int> get_coordi(int k) {
        int x = k / 6;
        int y = k % 6;
        return {x, y};
    }
};
