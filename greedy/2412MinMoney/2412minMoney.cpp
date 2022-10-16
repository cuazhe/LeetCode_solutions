#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    long long minimumMoney(vector<vector<int>>& transactions) {
        int n = transactions.size();
        long long neg_val = 0;
        for (auto& c: transactions) {
            if (c[0] - c[1] > 0) {
                neg_val += (c[0] - c[1]);
            }
        }
        long long res = 0;
        for (auto& c: transactions) {
            if (c[0] - c[1] > 0) {
                long long cur = neg_val - (c[0] - c[1]);
                res = max(res, cur + c[0]);
            }
            else {
                res = max(res, neg_val + c[0]);
            }
        }
        return res;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution a;
    vector<vector<int>> transactions = {{2,1}, {5,0}, {4,2}};
    long long res = a.minimumMoney(transactions);
    std::cout << res << "\n";
    return 0;
}

// AC. 260 ms, beats 99%; 108 MB, beats 64%.
