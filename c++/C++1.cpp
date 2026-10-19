#include <bits/stdc++.h>
using namespace std;
int main() {
    const int CAPACITY = 8;
    int window[8] = {};
    int kept = 0;
    int count = 0;
    if (!(cin >> count)) return 1;
    for (int i = 0; i < count; ++i) {
        int value = 0;
        if (!(cin >> value)) return 1;
        window[kept] = value;  kept=(kept+1)%8;
		//回绕,将kept看作指针
    }
    long long sum = 0;
    for (int i = 0; i < 8; ++i) sum += window[i];
    cout << "kept=" << min(8,count)<< "\n";
    if(count>=8)cout << "oldest=" << window[kept] << "\n";
    else cout << "oldest=" << window[0] << "\n";
    //首先kept指的是下一个数要存的位置，那么当count>8,全都填满，那么最后kept指的就是下一个要删除的元素，也就是最早的保留值
    //count<=8,那么最早的保留值还是在0位置
    cout << "last=" << window[(kept+8-1)%8] << "\n";
    cout << "sum=" << sum << "\n";
    (void)CAPACITY;
    return 0;
}// 固定容量读数窗口（含已知缺陷的 C++ 起步代码）
// 目标：只保留最后 8 个读数。当前写入没有按容量回绕。
// 缺陷：i 可能达到或超过 CAPACITY。
// 缺陷：保留数量没有上限。
