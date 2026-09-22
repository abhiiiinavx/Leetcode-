class Solution {
    struct Node {
        int l, r, prod;
        int cnt[5];

        Node() {
            l = r = 0;
            prod = 1;
            memset(cnt, 0, sizeof(cnt));
        }
    };

    int k;
    vector<Node> tree;

    Node merge(const Node& a, const Node& b) {
        Node res;

        res.prod = (long long)a.prod * b.prod % k;

        for (int i = 0; i < k; i++) {
            res.cnt[i] = a.cnt[i];
        }

        for (int i = 0; i < k; i++) {
            int rem = (long long)a.prod * i % k;
            res.cnt[rem] += b.cnt[i];
        }

        return res;
    }

    void build(int p, int l, int r, vector<int>& nums) {
        tree[p].l = l;
        tree[p].r = r;

        if (l == r) {
            int v = nums[l] % k;

            tree[p].prod = v;
            tree[p].cnt[v] = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(p * 2, l, mid, nums);
        build(p * 2 + 1, mid + 1, r, nums);

        tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
        tree[p].l = l;
        tree[p].r = r;
    }

    void update(int p, int idx, int value) {
        if (tree[p].l == tree[p].r) {
            value %= k;

            tree[p].prod = value;

            memset(tree[p].cnt, 0, sizeof(tree[p].cnt));
            tree[p].cnt[value] = 1;

            return;
        }

        int mid = (tree[p].l + tree[p].r) / 2;

        if (idx <= mid)
            update(p * 2, idx, value);
        else
            update(p * 2 + 1, idx, value);

        Node res = merge(tree[p * 2], tree[p * 2 + 1]);

        tree[p].prod = res.prod;

        for (int i = 0; i < k; i++) {
            tree[p].cnt[i] = res.cnt[i];
        }
    }

    Node query(int p, int l, int r) {
        if (l <= tree[p].l && tree[p].r <= r) {
            return tree[p];
        }

        int mid = (tree[p].l + tree[p].r) / 2;

        if (r <= mid) {
            return query(p * 2, l, r);
        }

        if (l > mid) {
            return query(p * 2 + 1, l, r);
        }

        Node left = query(p * 2, l, r);
        Node right = query(p * 2 + 1, l, r);

        return merge(left, right);
    }

public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        this->k = k;

        int n = nums.size();

        tree.resize(4 * n + 5);

        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            update(1, index, value);

            Node res = query(1, start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};