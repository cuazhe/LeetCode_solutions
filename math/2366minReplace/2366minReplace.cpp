#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        int n = nums.size();
        long long res = 0;
        long long cur = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] <= cur) {
                cur = nums[i];
                continue;
            }
            if (nums[i] % cur == 0) {
                res += (nums[i] / cur - 1);
            }
            else {
                res += (nums[i] / cur);
                long long k = nums[i] / cur;
                cur = nums[i] / (k + 1);
            }
        }
        return res;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution a;
    vector<int> nums = {19,7,2,24,11,16,1,11,23};
    long long res = a.minimumReplacement(nums);
    std::cout << res << "\n";
    return 0;
}

// AC. From solution. 88 ms, beats 95%; 53 MB, beats 67%.
