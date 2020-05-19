/*
 * https://leetcode-cn.com/problems/counting-bits/
 * 偶数的位数 = 已知[该数/2]
 * 奇数的位数 = 已知[该数-1]+1
 * 0 0000 0
 * 1 0001 1
 * 2 0010 1
 * 3 0011 2
 * 4 0100 1
 * 5 0101 2
 * 6 0110 2
 * 7 0111 3
 * 8 1000 1
 */


class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> res = {0};
        for (int i=1; i<=num; ++i) {
            if (i&1)
                res.emplace_back(res[i-1]+1);
            else
                res.emplace_back(res[i/2]);
        }
        return res;
    }
};
