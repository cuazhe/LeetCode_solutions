#include <iostream>
#include <vector>
#include <queue>
using namespace std;


class Solution {
public:
    long long kSum(vector<int>& nums, int k) {
        long long pos_sum = 0;
        int n = nums.size();
        vector<long long> arr;
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) {
                pos_sum += nums[i];
            }
            arr.push_back(abs(nums[i]));
        }
        sort(arr.begin(), arr.end());
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
        q.push({0, 0});
        for (int i = 0; i < k - 1; i++) {
            pair<long long, int> cur = q.top();
            q.pop();
            //cout << cur.first << " ; " << cur.second << "\n";
            int cur_pos = cur.second;
            int nxt_pos = cur.second + 1;
            long long cur_val = cur.first;
            if (cur_pos >= 0 && cur_pos < n) {
                pair<long long, int> temp = {cur_val + arr[cur_pos], nxt_pos};
                q.emplace(temp);
                if (cur_pos - 1 >= 0) {
                    pair<long long, int> temp = {cur_val - arr[cur_pos - 1] + arr[cur_pos], nxt_pos};
                    q.emplace(temp);
                }
            }
        }
        return pos_sum - q.top().first;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution a;
    vector<int> nums = {1,-2,3,4,-10,12};
    int k = 16;
    long long res = a.kSum(nums, k);
    std::cout << res << "\n";
    return 0;
}

// AC. 176 ms, beats 67%; 74 MB, beats 9%.
