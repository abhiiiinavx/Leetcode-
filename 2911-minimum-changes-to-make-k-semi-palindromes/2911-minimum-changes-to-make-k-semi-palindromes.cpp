
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        int inf = INT_MAX / 2;

        auto peel = [&](int i, int j, int d) {
            int changes = 0;

            for (; j - i > d; i += d, j -= d) {
                for (int t = 0; t < d; ++t) {
                    changes += (s[i + t] != s[j - d + t]);
                }
            }

            return changes;
        };

        vector<vector<int>> cost(n + 1, vector<int>(n + 1, inf));

        for (int d = 1; 2 * d <= n; ++d) {
            for (int len = 2 * d; len <= n; len += d) {
                for (int i = 0, j = len; j <= n; ++i, ++j) {
                    cost[i][j] = min(cost[i][j], peel(i, j, d));
                }
            }
        }

        vector<int> best(n + 1, inf);
        best[0] = 0;

        auto extend = [&](int j) {
            int ans = inf;

            for (int i = 0; i < j - 1; ++i) {
                ans = min(ans, best[i] + cost[i][j]);
            }

            return ans;
        };

        for (int pieces = 1; pieces < k; ++pieces) {
            vector<int> next(n + 1, inf);

            for (int j = 2 * pieces; j <= n - 2 * (k - pieces); ++j) {
                next[j] = extend(j);
            }

            swap(best, next);
        }

        return extend(n);
    }
};
