#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    int countPalindromes(string s) {
        long long N = 1e9 + 7;
        int n = s.size();
        long long c[n][10], f[n][10][10];
        memset(c, 0, sizeof(c));
        memset(f, 0, sizeof(f));
        for (int i = 0; i < n; i++) {
            int cur = s[i] - '0';
            if (i == 0) {
                c[i][cur]++;
            }
            else {
                for (int k = 0; k < 10; k++) {
                    c[i][k] += c[i - 1][k] % N;
                    c[i][k] %= N;
                }
                c[i][cur]++;
                for (int j = 0; j < 10; j++) {
                    for (int k = 0; k < 10; k++) {
                        f[i][j][k] += f[i - 1][j][k] % N;
                        f[i][j][k] %= N;
                    }
                }
                for (int j = 0; j < 10; j++) {
                    f[i][j][cur] += c[i - 1][j] % N;
                    f[i][j][cur] %= N;
                }
            }
        }
        
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < 10; j++) {
//                cout << c[i][j] << " ";
//            }
//            cout << "\n";
//        }
//
//        cout << "f value" << "\n";
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < 10; j++) {
//                for (int k = 0; k < 10; k++) {
//                    cout << f[i][j][k] << " ";
//                }
//                cout << "\n";
//            }
//            cout << "\n";
//        }
        
        long long d[n][10], g[n][10][10];
        memset(d, 0, sizeof(d));
        memset(g, 0, sizeof(f));
        
        for (int i = n - 1; i >= 0; i--) {
            int cur = s[i] - '0';
            if (i == n - 1) {
                d[i][cur]++;
            }
            else {
                for (int k = 0; k < 10; k++) {
                    d[i][k] += d[i + 1][k] % N;
                    d[i][k] %= N;
                }
                d[i][cur]++;
                for (int j = 0; j < 10; j++) {
                    for (int k = 0; k < 10; k++) {
                        g[i][j][k] += g[i + 1][j][k] % N;
                        g[i][j][k] %= N;
                    }
                }
                for (int j = 0; j < 10; j++) {
                    g[i][cur][j] += d[i + 1][j] % N;
                    g[i][cur][j] %= N;
                }
            }
        }
        
//        cout << "d value" << "\n";
//        for (int i = n - 1; i >= 0; i--) {
//            for (int j = 0; j < 10; j++) {
//                cout << d[i][j] << " ";
//            }
//            cout << "\n";
//        }
//
//        cout << "g value" << "\n";
//        for (int i = n - 1; i >= 0; i--) {
//            for (int j = 0; j < 10; j++) {
//                for (int k = 0; k < 10; k++) {
//                    cout << g[i][j][k] << " ";
//                }
//                cout << "\n";
//            }
//            cout << "\n";
//        }
        
        long long res = 0;
        for (int i = 2; i <= n - 3; i++) {
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 10; k++) {
                    res += (f[i - 1][j][k] * g[i + 1][k][j]) % N;
                }
            }
        }
        return res % N;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution a;
    string s = "9999900000";
    int res = a.countPalindromes(s);
    std::cout << res << "\n";
    return 0;
}

// From solution. AC. 48 ms, beats 64%; 25 MB, beats 27%.
