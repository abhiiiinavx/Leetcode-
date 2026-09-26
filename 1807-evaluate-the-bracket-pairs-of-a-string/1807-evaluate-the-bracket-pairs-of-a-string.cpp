class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        for (auto &x : knowledge)
            mp[x[0]] = x[1];

        string ans;

        for (int i = 0; i < s.size(); ) {
            if (s[i] == '(') {
                int j = s.find(')', i);
                string key = s.substr(i + 1, j - i - 1);

                if (mp.count(key))
                    ans += mp[key];
                else
                    ans += '?';

                i = j + 1;
            } 
            else {
                ans += s[i];
                i++;
            }
        }

        return ans;
    }
};