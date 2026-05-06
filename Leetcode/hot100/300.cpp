#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int LCS(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else if (dp[i - 1][j] > dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
        return dp[m][n];
    }

    int lengthOfLIS(vector<int>& nums) {
        vector<int> nums2(nums);
        sort(nums2.begin(), nums2.end());
        //排序后要去重
        nums2.erase(unique(nums2.begin(), nums2.end()), nums2.end());
        nums2.erase(unique(nums2.begin(), nums2.end()), nums2.end());
        return LCS(nums, nums2);
    }
};
