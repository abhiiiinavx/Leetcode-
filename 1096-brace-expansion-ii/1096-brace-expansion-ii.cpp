class Solution {
public:
    set<string> merge(set<string> a, set<string> b) {
        set<string> res;
        for (string x : a)
            for (string y : b)
                res.insert(x + y);
        return res;
    }

    set<string> parse(string &s, int &i) {
        set<string> res, cur = {""};

        while (i < s.size() && s[i] != '}') {
            if (s[i] == ',') {
                for (string x : cur) res.insert(x);
                cur = {""};
                i++;
            } 
            else {
                set<string> next;

                if (s[i] == '{') {
                    i++;
                    next = parse(s, i);
                    i++; // skip '}'
                } 
                else {
                    next.insert(string(1, s[i]));
                    i++;
                }

                cur = merge(cur, next);
            }
        }

        for (string x : cur) res.insert(x);
        return res;
    }

    vector<string> braceExpansionII(string expression) {
        int i = 0;
        set<string> ans = parse(expression, i);

        return vector<string>(ans.begin(), ans.end());
    }
};