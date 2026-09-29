class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Length of path must be even
        if ((m + n - 1) % 2 != 0)
            return false;

        // First character must be '('
        // Last character must be ')'
        if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(')
            return false;

        // dp[i][j][balance] = is it possible to reach (i,j)
        // with this balance?
        vector<vector<vector<bool>>> dp(
            m,
            vector<vector<bool>>(
                n,
                vector<bool>(m + n, false)
            )
        );

        dp[0][0][1] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                for (int balance = 0; balance <= m + n; balance++) {

                    int prevBalance;

                    if (grid[i][j] == '(')
                        prevBalance = balance - 1;
                    else
                        prevBalance = balance + 1;

                    if (prevBalance < 0 || prevBalance > m + n)
                        continue;

                    // Come from top
                    if (i > 0 && dp[i - 1][j][prevBalance])
                        dp[i][j][balance] = true;

                    // Come from left
                    if (j > 0 && dp[i][j - 1][prevBalance])
                        dp[i][j][balance] = true;
                }
            }
        }

        return dp[m - 1][n - 1][0];
    }
};