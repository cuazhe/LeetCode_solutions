#include <iostream>
#include <vector>
#include <bitset>
#include <cstring>
using namespace std;

class Solution {
public:
    int maxStudents(vector<vector<char>>& seats) {
        size_t m = seats.size(), n = seats[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(1<<n, 0));
        vector<int> look_up(m, 0);
        for (int i = 0; i < m; i++) {
            look_up[i] = transform(seats[i]);
        }
        for (int i = m - 1; i >= 0; i--) {
            // cout << i << "\n";
            for (int j = 0; j < (1 << n); j++) {
                bitset<8> bs(j);
                if (((j & look_up[i]) == 0) && ((j & (j << 1)) == 0) && ((j & (j >> 1)) == 0)) {
                    // cout << j << "\t";
                    for (int k = 0; k < (1 << n); k++) {
                        if (((j & (k << 1)) == 0) && ((j & (k >> 1)) == 0)) {
                            dp[i][j] = max(dp[i][j], dp[i + 1][k] + (int)bs.count());
                        }
                    }
                }
            }
           // cout << "\n";
        }
        int res = 0;
        for (int j = 0; j < (1<<n); j++) {
            res = max(res, dp[0][j]);
        }
        return res;
    }
    
    int transform(vector<char> c) {
        // bitset<8> res;
        string res = "";
        size_t n = c.size();
        for (int i = 0; i < n; i++) {
            if (c[i] == '#') {
                // res[n - 1 - i] = '1';
                res += "1";
            }
            else {
                // res[n - 1 - i] = '0';
                res += "0";
            }
        }
        // return (int)(res.to_ulong());
        return stoi(res, nullptr, 2);
    }
};
