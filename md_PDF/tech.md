# <center><font face="仿宋">超算队考核技术报告</font></center>
---
**作者：haber-f**  
**无AI修饰**
## 一.基本情况概论
### 1.Linux基础入门
- 完成前三关，学习了第四关shell和第六关Linux账号部分知识，
- 通过LabEx平台学习Linux，共计完成15个实验

  ![LabEx 实验图](photo/LabEx.1.png)
  ![LabEx](photo/LabEx.2.png)
### 2.C/C++
- 完成前三关
- 参加雏鸟杯
  ![雏鸟杯](photo/smallbird.png)
## 二.环境的选择
### 1.NCUSCC的容器
~~不用开虚拟机了~~
- 非常方便快捷
### 2.DevC++
- 老软件依旧实用,负责修改进阶路线代码
### 3.VMware虚拟机
- 安装中文语言包
- 选择系统映像
>ubuntu-24.04.4-desktop-amd64
- 硬件配置（3GB内存，40GB盘，1处理器，2核）
![ubuntu](photo/ubuntu.png)
### 4.VScode
- C/C++配置(MinGW-x64做编译器)
![组件C/C++](photo/vscode.1.png)
- Markdown配置(本篇md文档来源)
![组件Md](photo/vscode.2.png)
- git管理
![vs-git](photo/vscode.3.png)
## 三.考核过程
### 1.Linux第一题
>零基础小白与Linux的第一战——耗时2天半


- 学习方面
  1.课程学习  b站：只学够用的 Linux：长度正好的零基础入门教程——稍微对Linux命令有所了解
    b站：其他杂项，如虚拟机，Linux基础方面的。
  总结广而杂，无法付诸实践
  2.练习方面  通过千问推荐，综合比对，发现[labex](https://labex.io/zh/learn/linux)网站和[webminal](https://webminal.org/terminal/)适合用于Linux指令的练习，其中labex配备实时AI,利于即使提问(由于有clear机制，具体过程无法提供)
- 厘清脉络
由于对Linux任务不熟悉，由千问AI帮我厘清脉络
1.在 /workspace/目录下找到所有输入文件（如数据文件、密钥文本等）。
2.通过帮助信息明确 /workspace/exam 的用法、参数顺序及输入输出方式。
3.正确组合命令，将输入和密钥传递给程序。
4.确保生成的 /workspace/flag 与预期结果相同
- 代码实现1--找文件
```
bash-5.2$ ls -lah /workspace/
total 21K
...(大量文件)
```
- 代码实现2--看帮助
```
bash-5.2$ /workspace/exam -h
用法：exam [-h] -e 密钥

使用密钥处理 /workspace/input，将结果写入 /workspace/output。

选项:
  -h, --help  显示帮助并退出
  -e 密钥       指定非空 ASCII 密钥

诊断日志：/var/log/ncuscc/exam.log。退出码：0 表示成功，1
表示处理失败，2 表示参数错误或无法写入日志。
```
- 代码实现3--读取密钥并开始处理
```
bash-5.2$ mv ./input.bin ./input
bash-5.2$ /workspace/exam -e $(cat /workspace/cabinet/key.txt)
bash-5.2$ mv ./output ./flag
```
- 提交通过
### 2.Linux第二题
>有些懵懵懂懂的萌新第二战——3天(辩论赛挤占大量时间)
- 尝试不太借助AI，试着自己厘清脉络
首先要找到两份输入，再看密钥和程序，最后要保持A，B有序拼接
根据提示用find（刚好在LabEx学了没多久练个手）{find + 路径 + 筛选 +怎么做}
- 代码实现1（找到输入路径）
```
bash-5.2$ find /workspace -name '*signal-A*' -print
/workspace/archive/2026/signal-A.bin
bash-5.2$ find /workspace -name '*signal-B*' -print
```
- 代码实现2（查找密钥）
```
bash-5.2$ grep -r "ACCESS_KEY=" /workspace/
/workspace/catalog/words.txt:ACCESS_KEY=STAR
```
- 代码实现3（运行并处理最后的检查文件）
```
bash-5.2$cat /workspace/archive/2026/signal-A.bin /workspace/inbox/signal-B.bin | tee /workspace/input
bash-5.2$ /workspace/exam -e "STAR"
bash-5.2$ mv /workspace/output /workspace/flag
```
### 3.Linux第三题
>能熟练运用一些指令的新手第三战——1天
- 厘清思路
先找到原始文本和密钥，尝试处理后，根据日志等信息判断原文本缺少的，在进行相关补齐操作。
- 代码实现一（find密钥和原文件）
```
bash-5.2$ find .
.
./exam
./input.txt
./key.txt
./logs
bash-5.2$ cat ./key.txt
NOVA
```
- 代码实现二（查看帮助并处理运行）
```
bash-5.2$ ./exam -h
用法：exam [-h] -e 密钥

使用密钥处理 /workspace/input，将结果写入 /workspace/output。

选项:
  -h, --help  显示帮助并退出
  -e 密钥       指定非空 ASCII 密钥

诊断日志：/var/log/ncuscc/exam.log。退出码：0 表示成功，1 表示处理失败，2 表示参数错误或无法写入日志。

bash-5.2$ cp ./input.txt ./input
./exam -e $(cat ./key.txt)
exam: 输入字节数必须是密钥字节数的整数倍（输入 19 字节，密钥 4 字节）
```
- 代码实现三(最后处理)
```
bash-5.2$ sed -i '$ s/$/ /'  ./input
bash-5.2$ mv ./input ./flag
``` 
### 4.C/C++第一题
>这是有点基础的蒟蒻的一战
- 理清思路
  根据题目搞懂应该完善的点,已选定C++方向
- 本地代码实现
```cpp
#include <iostream>
using namespace std;
int main() {
    int n = 0;
    if (!(cin >> n)) {
        return 1;  // 没读到 n：保留非零退出码，便于发现输入问题
    }
    int sum=0,mn=10000,mx=-10000;
    for(int i=1;i<=n;++i){
	   int a=0;
	   if(!(cin>>a))return 1;//退出码 
	   sum+=a;mn=min(mn,a);mx=max(mx,a);
	}
    cout << "count=" << n << "\n";
    cout << "sum=" << sum << "\n";
    cout << "min=" << mn << "\n";
    cout << "max=" << mx << "\n";
    return 0;
}
```
- 容器内部步骤
```
bash_5.2$ rm -r ./c
bash_5.2$ rm main.cpp
bash_5.2$ touch main.cpp
bash_5.2$ nano main.cpp
在其中粘贴本地写好的代码ctrl+x 然后 y
bash_5.2$ g++ -std=c++17 -Wall -Wextra -o main main.cpp
```
- diff 容器内部检验
```
bash_5.2$ diff <(./main < samples/01-mixed.in) samples/01-mixed.out
```
- 提交成功
### 5.C/C++第二题
>生死时速1
- 代码呈现
```cpp
#include <iostream>
#include <string>
using namespace std;
struct Record {
    string type;
    string status;
    int hours = 0;
};
int type_count[4],type_num[4],final=-1;//个数，总数，最大的
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
        //三次合法，其实都是判断输入是否合法
    }
    for (int i = 0;i < 4;++i) {
        cout << Type[i] << " " << type_count[i] << " "<<type_num[i]<<"\n";
    }
    cout<<"busiest "<<Type[final]<<"\n";
    return 0;
}
// TODO: 读取 count 条记录，按题面统计四类设备。
// 输出顺序固定为 printer、scanner、router、server。
// 即使某类数量为 0 也要输出；总时长并列时选择固定顺序中更靠
```
- 同上C++第一题套法
### 6.C/C++ 第三题
>生死时速2
- 代码呈现
```cpp
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
		//回绕,将kept看作指针,不作存储数量了
    }
    long long sum = 0;
    for (int i = 0; i < 8; ++i) sum += window[i];
    cout << "kept=" << min(8,count)<< "\n";
    if(count>=8)cout << "oldest=" << window[kept] << "\n";
    else cout << "oldest=" << window[0] << "\n";
    //首先kept指的是下一个数要存的位置，那么当count>8,全都填满，那么最后kept指的就是下一个要删除的元素，也就是最早的保留值
    //count<=8,那么最早的保留值还是在0位置
    cout << "last=" << window[(kept+8-1)%8] << "\n";
    //既然如此那么last就是指针指的上一个了
    cout << "sum=" << sum << "\n";
    (void)CAPACITY;
    return 0;
}
// 固定容量读数窗口（含已知缺陷的 C++ 起步代码）
// 目标：只保留最后 8 个读数。当前写入没有按容量回绕。
// 缺陷：i 可能达到或超过 CAPACITY。
// 缺陷：保留数量没有上限。
```
- 同上C++第一题套法
## 四.遇到的问题以及解决方案
### 1.Linux第一题
#### A.不知道怎么查看帮助
a.尝试先运行下程序
```
bash-5.2$ ./exam
用法：exam [-h] -e 密钥
exam: 参数无效，请使用 --help 查看用法。
```
b.使用cat查看文件内容(可以找但累死)
c.根据AI说法大部分都支持 --help和-h，直接走起
#### B.没有./input
a. mv一下，将./input.bin变为./input
### 2.Linux 第二题
#### A如何合并两个文件
a.根据提示，借助管道,通过tee实现
```
bash-5.2$cat /workspace/archive/2026/signal-A.bin /workspace/inbox/signal-B.bin | tee /workspace/input
```
b.按次序向./input输入文件内容
1.先复制一份，再追加一份
```
cp  /workspace/archive/2026/signal-A.bin /workspace/input 
cat /workspace/inbox/signal-B.bin >> /workspace/input
```
2.直接重定向，> 
```
cat /workspace/archive/2026/signal-A.bin /workspace/inbox/signal-B.bin > /workspace/input
```
### 3.Linux 第三题
#### A.如何在结尾\n前加入空格
a.sed指令
```
sed -i '$ s/$/ /' file.txt
```
解释：-i  原地编辑（in-place）。直接修改 `file.txt文件，而不是将结果输出到屏幕-i ;'$ s/$/ /'第一个$是"地址‌"，意思是‌只改最后一行;第二个$是"‌正则匹配‌"，意思是‌一行的末尾那个位置；/ /中间是换的新东西 
### 4.C/C++ 第一题
#### A.如何快速编写C++程序
a. 抛弃容器，在本地先编写好在交
#### B.为什么直接上传main.cpp不可以
a.一般来说这种文件天然缺少对于其他人员可运行，同时容器中没有sudo，缺少权限修改，同时容器中也有main.cpp不可重名
**以下是自己上传的main.cpp**
```
bash-5.2$ ls -lah ./main.cpp
ls: ./main.cpp
-rw-rw---- 1 997 1015 487 Oct 19 19:50 ./main.cpp
bash-5.2$ g++ -std=c++17 -Wall -Wextra -o main main.cpp
cc1plus: fatal error: main.cpp: Permission denied
compilation terminated.
```
### 5.C/C++ 第二题
#### A.为什么时长最多的那个总是找错
a.因为总小时数相同时，不是选输入中先出现的类型，而是选 printer、scanner、router、server 中更靠前的类型。
也就是下面的条件句
```cpp
if (final == -1 || type_num[i] > type_num[final]||(type_num[i]==type_num[final]&&final>i))final = i;
```
### 6.C/C++ 第三题
#### A.代码改完发现输入的8个值还是原来的
a.是把kept当指针了，但是忘记了读入存储的源代码是window[i]
#### count<8时oldest出错
a.忘记分情况讨论
也就是
```cpp
if(count>=8)cout << "oldest=" << window[kept] << "\n";
    else cout << "oldest=" << window[0] << "\n";
    //首先kept指的是下一个数要存的位置，那么当count>8,全都填满，那么最后kept指的就是下一个要删除的元素，也就是最早的保留值
    //count<=8,那么最早的保留值还是在0位置
```
## 五. 一些探究(small and not big)
### 1.Linux第一题
#### A.所谓保持二进制内容不变
|命令|说明|示例|
|:---|:---|:---|
|cp|最常用。默认情况下，cp 会逐字节复制数据。使用 cp -a 还可以保留权限和时间戳。 | cp source.bin dest.bin |
|dd|底层数据复制工具，专门用于处理原始二进制数据，常用于磁盘镜像或精确复制。 | dd if=source.bin of=dest.bin bs=1M |
|mv|移动或重命名。在同一文件系统内，它只是修改 inode 指向，数据本身完全不动；跨文件系统时等效于复制后删除源文件。 | mv source.bin dest.bin |
|cat+重定向| 虽然 cat 常用来查看文本，但 cat file1 > file2 也能精确复制二进制内容。 | cat source.bin > dest.bin |
### 2.Linux第二题
#### A.对于查询合并的思考
```
bash-5.2$ find /workspace -name '*signal-A*' -o -name "*signal-B*" -print
/workspace/inbox/signal-B.bin

/*发现都要加print，我怎么记得默认print*/

bash-5.2$ find /workspace -name '*signal-A*'
/workspace/archive/2026/signal-A.bin

但是
bash-5.2$ find /workspace -name '*signal-A*' -o -name "*signal-B*" 
/workspace/inbox/signal-B.bin
/workspace/archive/2026/signal-A.bin
而
bash-5.2$ find /workspace -name '*signal-A*' -o -name "*signal-B*" -print
/workspace/inbox/signal-B.bin
```
最后发现：
你写的所有东西（-name、-size、-print、-delete）都是布尔表达式按优先级从左到右做短逻辑求值，动作只有在它所在的表达式分支被执行到时才会触发.
### 3.Linux第三题
#### A.对于ASCLL的小思考
原始文本为 ASCII，那么应该思考空格是否为ASCLL的“ ”，然后发现是默认的。
### 6.C/C++第三题
#### A.对于也可以换用其他正确的数据结构的小思考
这个问题可以想到deque双端队列，维护队列长度为8，有人来了，前面的就走了，oldest取前面的，last就取后面的，计算num的时候全弹出
