#include <iostream>
#include <string>
using namespace std;
struct Record {
    string type;
    string status;
    int hours = 0;
};
int type_count[4],type_num[4],final=-1;
string Type[4] = { "printer","scanner","router","server" };
bool judge(Record s) {
    for (int i = 0;i < 4;++i) {
        if (Type[i] == s.type) {
            type_num[i] += s.hours;
            type_count[i]++;
            if (final == -1 || type_num[i] > type_num[final]||(type_num[i]==type_num[final]&&final>i))final = i;
            return 1;
        }
    }
    return 0;
}//即判断合法，又完成num累加,还完成count计数
int main() {
    int count = 0;
    if (!(cin >> count)) return 0;
    for (int i = 1;i <= count;++i) {
        Record s;
        if (!(cin >> s.type >> s.status >> s.hours)) return 1;
        if (s.status != "ok" && s.status != "repair")return 1;
        if (!judge(s))return 1;
        //三次合法，其实都是输入是否合法
    }
    for (int i = 0;i < 4;++i) {
        cout << Type[i] << " " << type_count[i] << " "<<type_num[i]<<"\n";
    }
    cout<<"busiest "<<Type[final]<<"\n";
    return 0;
}
// TODO: 读取 count 条记录，按题面统计四类设备。
// 输出顺序固定为 printer、scanner、router、server。
// 即使某类数量为 0 也要输出；总时长并列时选择固定顺序中更靠前的类型。