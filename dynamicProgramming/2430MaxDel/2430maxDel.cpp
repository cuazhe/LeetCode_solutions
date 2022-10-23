#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    int deleteString(string s) {
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= i; j--) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j + 1] + 1;
                }
            }
        }
        //int res = 1;
        vector<int> dp2(n, 1);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (dp[i][j] >= (j - i)) {
                    dp2[i] = max(dp2[i], 1 + dp2[j]);
                }
            }
        }
        return dp2[0];
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution a;
    string s = "aaabaab";
    int res = a.deleteString(s);
    std::cout << res << "\n";
    return 0;
}

// AC. 1260 ms, beats 6%; 371 MB, beats 9%.
