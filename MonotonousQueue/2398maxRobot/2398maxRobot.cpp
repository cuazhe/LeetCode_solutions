#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> pii;


class Solution {
public:
    int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget) {
        deque<pii> mono_dq;
        int n = chargeTimes.size();
        int left = 0, right = 0;
        long long s = 0;
        int res = 0;
        for (right = 0; right < n; right++) {
            while ((mono_dq.size() > 0) && (mono_dq.back().first < chargeTimes[right])) {
                mono_dq.pop_back();
            }
            mono_dq.push_back({chargeTimes[right], right});
            s += runningCosts[right];
            //right++;
            while ((mono_dq.size() > 0) && (mono_dq.front().first + (right - left + 1) * s) > budget) {
                if (left == mono_dq.front().second) {
                    mono_dq.pop_front();
                }
                s -= runningCosts[left];
                left++;
            }
            if (mono_dq.size() > 0) {
                res = max(res, right - left + 1);
            }
            //cout << "right = " << right << " ; res = " << res << "\n";
        }
        return res;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution a;
    //vector<int> chargeTimes = {3,6,1,3,4};
    //vector<int> chargeTimes = {11,12,19};
    vector<int> chargeTimes = {5, 46,56,45,54,30,92, 63, 31};
    //vector<int> runningCosts = {2,1,3,4,5};
    //vector<int> runningCosts = {10,8, 7};
    vector<int> runningCosts = {62, 81,33,99,28,99,86, 19, 5};
    long long budget = 85;
    int res = a.maximumRobots(chargeTimes, runningCosts, budget);
    //bool test = a.canFinish(chargeTimes, runningCosts, budget, 3, 1);
    //cout << test << "\n";
    std::cout << res << "\n";
    return 0;
}

// AC. 184 ms, beats 69%; 109 MB, beats 59%.
