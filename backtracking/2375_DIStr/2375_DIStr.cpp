class Solution {
public:
    bool visited[10] = {0};
    int n;
    string res;
    string pat;
    int found = 0;
    string smallestNumber(string pattern) {
        n = pattern.size();
        pat = pattern;
        //cout << pat << "\n";
        //cout << visited[3] << "\n";
        dfs(0);
        return res;
    }
    
    void dfs(int pos) {
        //cout << "pos = " << pos << "; res = " << res << "\n";
        if (pos == n + 1) {
            found = 1;
            return;
        }
        for (int i = 1; i <= 9; i++) {
            int flag = 0;
            if (!visited[i]) {
                if (pos == 0) {
                    visited[i] = true;
                    res += to_string(i);
                    //cout << "pos = " << pos << "; i = " << i << "; " << res << "\n";
                    flag = 1;
                }
                else {
                    if (pat[pos - 1] == 'I') {
                        //cout << "i = " << i << "; res[pos - 1] = " << res[pos - 1] << "\n";
                        //cout << res[pos - 1] - '0' << "\n";
                        if (i > (int)(res[pos - 1] - '0')) {
                            visited[i] = true;
                            res += to_string(i);
                            flag = 1;
                            //cout << "i = " << i << "; res = " << res << "\n";
                        }
                    }
                    else {
                        if (i < (int)(res[pos - 1] - '0')) {
                            visited[i] = true;
                            res += to_string(i);
                            flag = 1;
                        }
                    }
                    
                }
            }
            if (flag == 1) {
                dfs(pos + 1);
                if (found == 0) {
                    visited[i] = 0;
                    res.pop_back();
                    continue;
                }
                else {
                    return;
                }
            }
            else {
                continue;
            }
        }
        return;
    }
};
