#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // 用于格式化输出

using namespace std;

// 辅助函数：打印当前 next 数组的状态
void printArray(const vector<int>& next, int currentLen) {
    cout << "     当前 next 数组: [ ";
    for (int i = 0; i < next.size(); i++) {
        if (i <= currentLen) {
            // 打印已计算出的部分
            cout << next[i];
        } else {
            // 还没算出来的部分用 ? 表示
            cout << "?";
        }
        if (i < next.size() - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

void debugNext(string s) {
    int len = s.length();
    vector<int> next(len);
    
    cout << "==========================================" << endl;
    cout << "开始分析字符串: \"" << s << "\"" << endl;
    cout << "长度: " << len << endl;
    cout << "==========================================" << endl;

    next[0] = -1;
    int j = 0; 
    int k = -1; 
    
    int step = 1; // 用于记录步骤数

    // 注意：为了演示完整过程，我们打印初始状态
    printArray(next, 0);

    while (j < len - 1) {
        cout << "\n--- Step " << step++ << " ---" << endl;
        cout << "  状态: j = " << j << " ('" << s[j] << "'), k = " << k;
        
        if (k != -1) {
            cout << " ('" << s[k] << "')";
        } else {
            cout << " (无前缀)";
        }
        cout << endl;

        // 逻辑判断
        if (k == -1) {
            cout << "  判定: k 为 -1 (刚开始或已回溯到底)" << endl;
            cout << "  操作: j++, k++, 记录 next[" << j + 1 << "]" << endl;
            j++;
            k++;
            next[j] = k;
            cout << "  结果: next[" << j << "] = " << k << endl;
        } 
        else if (s[j] == s[k]) {
            cout << "  判定: s[" << j << "] == s[" << k << "] ('" << s[j] << "' == '" << s[k] << "') -> 匹配成功！" << endl;
            cout << "  操作: j++, k++, 记录 next[" << j + 1 << "]" << endl;
            j++;
            k++;
            next[j] = k;
            cout << "  结果: next[" << j << "] = " << k << endl;
        } 
        else {
            cout << "  判定: s[" << j << "] != s[" << k << "] ('" << s[j] << "' != '" << s[k] << "') -> 失配！" << endl;
            cout << "  操作: 回溯 k = next[k] (即 next[" << k << "] = " << next[k] << ")" << endl;
            k = next[k];
            cout << "  结果: k 变为 " << k << " (j 保持不变)" << endl;
        }

        // 打印本步结束后的数组状态
        printArray(next, j);
    }
    
    cout << "\n==========================================" << endl;
    cout << "最终结果: ";
    for(int x : next) cout << x << " ";
    cout << endl;
    cout << "==========================================" << endl;
}

int main() {
    // 你可以在这里修改想要测试的字符串
    // 建议使用我们刚才分析过的 "ababaa" 来观察回溯
    string input = "ababaa"; 
    
    cout << "请输入要测试的字符串 (直接回车默认使用 \"" << input << "\"): ";
    string temp;
    char c = cin.get(); // 读取第一个字符
    if (c != '\n') {
        cin.putback(c); // 如果不是回车，放回去重新读
        cin >> input;
    }

    debugNext(input);

    return 0;
}