#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;


class Solution {
public:
    vector<int> secondGreaterElement(vector<int>& nums) {
        int n = nums.size();
        stack<int> s;
        // minimum priority_queue
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> t;
        vector<int> res(n, -1);
        for (int i = 0; i < n; i++) {
            while (true) {
                if (t.size() == 0) {
                    break;
                }
                pair<int, int> temp = t.top();
                if (temp.first < nums[i]) {
                    res[temp.second] = nums[i];
                    t.pop();
                }
                else {
                    break;
                }
            }
            while ((s.size() > 0) && (nums[s.top()] < nums[i])) {
                int aux = s.top();
                s.pop();
                t.push({nums[aux], aux});
            }
            s.push(i);
        }
        return res;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution a;
    vector<int> nums = {2,4,0,9,6};
    vector<int> res = a.secondGreaterElement(nums);
    for (auto c: res) {
        cout << c << " ";
    }
    cout << "\n";
    std::cout << "\n";
    return 0;
}

// AC. 232 ms, beats 53%; 89 MB, beats 55%.
// Use both monotonous stack and priority_queue. 
