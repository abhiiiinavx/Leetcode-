class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<long long, 4>> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }

        sort(a.begin(), a.end(), [](auto& x, auto& y) {
            if (x[0] != y[0]) return x[0] < y[0];
            return x[1] < y[1];
        });

        vector<long long> starts(n);
        for (int i = 0; i < n; i++) {
            starts[i] = a[i][0];
        }

        vector<int> nxt(n);

        for (int i = 0; i < n; i++) {
            nxt[i] = upper_bound(
                starts.begin(),
                starts.end(),
                a[i][1]
            ) - starts.begin();
        }

        struct Node {
            long long score;
            vector<int> v;
        };

        vector<vector<Node>> dp(n + 1, vector<Node>(5));

        for (int k = 0; k <= 4; k++) {
            dp[n][k] = {0, {}};
        }

        auto better = [](const Node& a, const Node& b) {
            if (a.score != b.score)
                return a.score > b.score;
            return a.v < b.v;
        };

        for (int i = n - 1; i >= 0; i--) {
            for (int k = 0; k <= 4; k++) {
                Node best = dp[i + 1][k];

                if (k > 0) {
                    Node take = dp[nxt[i]][k - 1];
                    take.score += a[i][2];
                    take.v.push_back(a[i][3]);

                    sort(take.v.begin(), take.v.end());

                    if (better(take, best))
                        best = take;
                }

                dp[i][k] = best;
            }
        }

        return dp[0][4].v;
    }
};