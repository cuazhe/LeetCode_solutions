#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        int N = 1e9 + 7;
        int n = nums.size();
        long long sm = 0;
        for (auto c: nums) {
            sm += c;
        }
        
        long long dp[n][k];
        memset(dp, 0, sizeof(dp));
        
        /*
        for (int i = 1; i < k; i++) {
            cout << dp[n - 1][i] << " ";
        }
        cout << "\n";
        */
        
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                if (nums[i] < k) {
                    dp[i][nums[i]] = 1;
                }
                continue;
            }
            if (nums[i] < k) {
                dp[i][nums[i]] = (dp[i][nums[i]] + 1) % N;
            }
            for (int j = 1; j < k; j++) {
                if (j >= sm) {
                    break;
                }
                dp[i][j] += dp[i - 1][j];
                dp[i][j] %= N;
                if (nums[i] < j) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - nums[i]]) % N;
                }
            }
        }
        
        /*
        for (int i = 1; i < k; i++) {
            cout << dp[n - 1][i] << " ";
        }
        cout << "\n";
        */
        
        long long tot = 1;
        for (int i = 0; i < n; i++) {
            tot = (tot * 2) % N;
        }
        //cout << "tot = " << tot << "\n";
        
        long long temp = 0;
        for (int i = 1; i < k; i++) {
            if (sm - i < k) {
                temp = (temp + dp[n - 1][i]) % N;
            }
            else {
                temp = (temp + dp[n - 1][i] * 2) % N;
            }
            //cout << "i = " << i << "; dp[n-1][i] = " << dp[n-1][i] << " ; temp = " << temp << "\n";
        }
        
        long long res = 0;
        res = (tot - 2 - temp + N) % N;
        return res;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution a;
    vector<int> nums = {1, 2, 4};
    int k = 857;
    int res = a.countPartitions(nums, k);
    std::cout << res << "\n";
    return 0;
}

//AC. From solution. 48 ms, beats 30%; 16.3 MB, beats 28%.
