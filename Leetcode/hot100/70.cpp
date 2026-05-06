//爬楼梯问题
//错误的遍历，超时了，因为有重复计算的部分
// class Solution {
// public:
//     int climbStairs(int n) {
//         if (n == 0) {
//             return 1;
//         }

//         if (n == 1) {
//             return 1;
//         }
//         return climbStairs(n - 1) + climbStairs(n - 2);
//     }
// };
//使用动态规划，保存已经计算过的结果，避免重复计算
class Solution {
public:
    int climbStairs(int n) {
        if (n == 0||n==1) {
            return 1;
        }
        int a = 1, b = 1;
        for (int i = 2; i <= n; i++) {
            int temp = a + b;
            a = b;
            b = temp;
        }
        return b;
    }
}
