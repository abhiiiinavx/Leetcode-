class Solution {
public:
    vector<string> ans;

    void solve(string s, int start, int last, char open, char close) {
        int bal = 0;

        for (int i = start; i < s.size(); i++) {
            if (s[i] == open) bal++;
            else if (s[i] == close) bal--;

            if (bal >= 0) continue;

            for (int j = last; j <= i; j++) {
                if (s[j] == close && (j == last || s[j - 1] != close))
                    solve(s.substr(0, j) + s.substr(j + 1), i, j, open, close);
            }
            return;
        }

        reverse(s.begin(), s.end());

        if (open == '(')
            solve(s, 0, 0, ')', '(');
        else
            ans.push_back(s);
    }

    vector<string> removeInvalidParentheses(string s) {
        solve(s, 0, 0, '(', ')');
        return ans;
    }
};
