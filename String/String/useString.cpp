#include<iostream>
#include "String.h"
int main() {
    std::cout << "--- KMP 查找子串功能测试 ---" << std::endl;

    // --- 测试案例 1: 基本匹配 ---
    String text1("ababcabcacbab");
    String pattern1("abcac");
    std::cout << "\n[测试 1]" << std::endl;
    std::cout << "主串: " << text1.GetStr() << std::endl;
    std::cout << "模式串: " << pattern1.GetStr() << std::endl;
    int pos1 = text1.KPM_Find(pattern1);
    std::cout << "查找结果 (预期: 5): " << pos1 << std::endl;

    // --- 测试案例 2: 开头匹配 ---
    String text2("ababaabab");
    String pattern2("ababa");
    std::cout << "\n[测试 2]" << std::endl;
    std::cout << "主串: " << text2.GetStr() << std::endl;
    std::cout << "模式串: " << pattern2.GetStr() << std::endl;
    int pos2 = text2.KPM_Find(pattern2);
    std::cout << "查找结果 (预期: 0): " << pos2 << std::endl;

    // --- 测试案例 3: 结尾匹配 ---
    String text3("hello world");
    String pattern3("world");
    std::cout << "\n[测试 3]" << std::endl;
    std::cout << "主串: " << text3.GetStr() << std::endl;
    std::cout << "模式串: " << pattern3.GetStr() << std::endl;
    int pos3 = text3.KPM_Find(pattern3);
    std::cout << "查找结果 (预期: 6): " << pos3 << std::endl;

    // --- 测试案例 4: 不存在匹配 ---
    String text4("hello world");
    String pattern4("goodbye");
    std::cout << "\n[测试 4]" << std::endl;
    std::cout << "主串: " << text4.GetStr() << std::endl;
    std::cout << "模式串: " << pattern4.GetStr() << std::endl;
    int pos4 = text4.KPM_Find(pattern4);
    std::cout << "查找结果 (预期: -1): " << pos4 << std::endl;

    // --- 测试案例 5: 模式串比主串长 ---
    String text5("short");
    String pattern5("verlongpattern");
    std::cout << "\n[测试 5]" << std::endl;
    std::cout << "主串: " << text5.GetStr() << std::endl;
    std::cout << "模式串: " << pattern5.GetStr() << std::endl;
    int pos5 = text5.KPM_Find(pattern5);
    std::cout << "查找结果 (预期: -1): " << pos5 << std::endl;

    // --- 测试案例 6: 空模式串 ---
    String text6("any text");
    String pattern6("");
    std::cout << "\n[测试 6]" << std::endl;
    std::cout << "主串: " << text6.GetStr() << std::endl;
    std::cout << "模式串: " << pattern6.GetStr() << std::endl;
    int pos6 = text6.KPM_Find(pattern6);
    std::cout << "查找结果 (预期: 0): " << pos6 << std::endl;

    // --- 测试案例 7: 连续的高度重复字符，考验next数组 ---
    String text7("aaaaabaaaaab");
    String pattern7("aaaaab");
    std::cout << "\n[测试 7]" << std::endl;
    std::cout << "主串: " << text7.GetStr() << std::endl;
    std::cout << "模式串: " << pattern7.GetStr() << std::endl;
    int pos7 = text7.KPM_Find(pattern7);
    std::cout << "查找结果 (预期: 6): " << pos7 << std::endl;

    return 0;
}