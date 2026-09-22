class Solution {
    int k, n;
    vector<array<int, 5>> cnt;
    vector<int> prod;

    void pull(int p) {
        prod[p] = (long long)prod[p << 1] * prod[p << 1 | 1] % k;

        for (int i = 0; i < k; i++)
            cnt[p][i] = cnt[p << 1][i];

        for (int i = 0; i < k; i++) {
            int r = (long long)prod[p << 1] * i % k;
            cnt[p][r] += cnt[p << 1 | 1][i];
        }
    }

    void build(int p, int l, int r, vector<int>& nums) {
        if (l == r) {
            prod[p] = nums[l] % k;
            cnt[p][prod[p]] = 1;
            return;
        }

        int m = (l + r) >> 1;

        build(p << 1, l, m, nums);
        build(p << 1 | 1, m + 1, r, nums);

        pull(p);
    }

    void update(int p, int l, int r, int idx, int val) {
        if (l == r) {
            fill(cnt[p].begin(), cnt[p].end(), 0);

            prod[p] = val % k;
            cnt[p][prod[p]] = 1;

            return;
        }

        int m = (l + r) >> 1;

        if (idx <= m)
            update(p << 1, l, m, idx, val);
        else
            update(p << 1 | 1, m + 1, r, idx, val);

        pull(p);
    }

    pair<array<int, 5>, int> query(int p, int l, int r, int ql) {
        if (l >= ql)
            return {cnt[p], prod[p]};

        int m = (l + r) >> 1;

        if (ql <= m) {
            auto left = query(p << 1, l, m, ql);

            if (m + 1 > r)
                return left;

            auto right = query(p << 1 | 1, m + 1, r, ql);

            array<int, 5> res{};

            for (int i = 0; i < k; i++)
                res[i] = left.first[i];

            for (int i = 0; i < k; i++) {
                int rem = (long long)left.second * i % k;
                res[rem] += right.first[i];
            }

            int pdt = (long long)left.second * right.second % k;

            return {res, pdt};
        }

        return query(p << 1 | 1, m + 1, r, ql);
    }

public:
    vector<int> resultArray(vector<int>& nums, int K, vector<vector<int>>& queries) {
        k = K;
        n = nums.size();

        cnt.resize(4 * n + 5);
        prod.resize(4 * n + 5);

        build(1, 0, n - 1, nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            update(1, 0, n - 1, index, value);

            auto res = query(1, 0, n - 1, start);

            ans.push_back(res.first[x]);
        }

        return ans;
    }
};