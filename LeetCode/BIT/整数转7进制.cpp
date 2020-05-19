/*
 * https://leetcode-cn.com/problems/base-7/
 * 递归（商）+ 余数
 */

class Solution {
public:
    string convertToBase7(int num) {
        if (num<0) return '-' + convertToBase7(-num);
        if (num<7) return to_string(num);
        return convertToBase7(num/7) + to_string(num%7);
    }
};
