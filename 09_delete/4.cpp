
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    const double distance = 1000;  // 沙漠总长度
    const int capacity = 500;      // 油箱容量

    int n = 1;
    double maxDistance = 500;

    // 计算至少需要多少个满油箱
    while (maxDistance < distance) {
        n++;
        maxDistance += (double)capacity / (2 * n - 1);
    }

    // 初始需要的汽油总量
    cout << "初始汽油量：" << n * capacity << " L" << endl;

    double position = 0;  // 当前距离沙漠起点的位置

    cout << fixed << setprecision(2);
    cout << "贮油点编号\t距离(km)\t存油量(L)" << endl;

    // 逐阶段建立贮油点
    for (int i = n; i >= 2; i--) {

        // 当前阶段能够推进的距离
        double d = (double)capacity / (2 * i - 1);

        position += d;

        // 当前贮油点剩余的汽油
        int oil = (i - 1) * capacity;

        cout << n - i + 1 << "\t\t"
             << position << "\t\t"
             << oil << endl;
    }

    cout << "最后剩余路程："
         << distance - position << " km" << endl;

    return 0;
}
