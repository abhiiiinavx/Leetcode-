class Solution {
public:
    int ans = 0;

    pair<int,int> dfs(TreeNode* root) {
        if (!root) return {0, 0};

        auto l = dfs(root->left);
        auto r = dfs(root->right);

        int sum = root->val + l.first + r.first;
        int cnt = 1 + l.second + r.second;

        if (root->val == sum / cnt)
            ans++;

        return {sum, cnt};
    }

    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};