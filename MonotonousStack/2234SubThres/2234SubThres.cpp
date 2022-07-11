#include <iostream>
#include <vector>
#include <stack>
using namespace std;


class Solution {
public:
    int validSubarraySize(vector<int>& nums, int threshold) {
        int n = nums.size();
        stack<int> stk = {};
        vector<int> left(n, -1);
        vector<int> right(n, n);
        for (int i = 0; i < n; i++) {
            if (stk.size() == 0) {
                stk.push(i);
                left[i] = -1;
            }
            else if (nums[stk.top()] < nums[i]) {
                left[i] = stk.top();
                stk.push(i);
            }
            else {
                while ((stk.size() > 0) && (nums[stk.top()] >= nums[i])) {
                    stk.pop();
                }
                if (stk.size() == 0) {
                    left[i] = -1;
                    stk.push(i);
                }
                else {
                    left[i] = stk.top();
                    stk.push(i);
                }
            }
        }
        stk = {};
        for (int i = n - 1; i >= 0; i--) {
            if (stk.size() == 0) {
                stk.push(i);
                right[i] = n;
            }
            else if (nums[stk.top()] < nums[i]) {
                right[i] = stk.top();
                stk.push(i);
            }
            else {
                while ((stk.size() > 0) && (nums[stk.top()] >= nums[i])) {
                    stk.pop();
                }
                if (stk.size() == 0) {
                    right[i] = n;
                    stk.push(i);
                }
                else {
                    right[i] = stk.top();
                    stk.push(i);
                }
            }
        }
        long long cur;
        for (int i = 0; i < n; i++) {
            cur = (right[i] - 1 - left[i]);
            if (nums[i] * cur > threshold) {
                return cur;
            }
        }
        return -1;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution a;
    vector<int> nums = {6,5,6,5,8};
    int threshold = 7;
    int res = a.validSubarraySize(nums, threshold);
    std::cout << res << "\n";
    return 0;
}

// AC. 220 ms, beats 42%; 87 MB, beats 65%.
// Monotonous stack.
