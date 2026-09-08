class Solution {
public:
    int countCommas(int n) {
        int ans = 0;

        for (int i = 1000; i <= n; i++) {
            if (i >= 1000)
                ans++;
            if (i >= 1000000)
                ans++;
        }

        return ans;
    }
};