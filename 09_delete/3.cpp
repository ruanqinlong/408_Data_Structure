#include <bits/stdc++.h>
using namespace std;

// 计算曼哈顿距离
int get_distance(int a, int b, int x[], int y[]) {
    return abs(x[a] - x[b]) + abs(y[a] - y[b]);
}

int main() {
    int n;
    cin >> n;

    int x[n+1], y[n+1];

    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    long long g[n+1] = {0};
    long long f[n+1] = {0};

    // 不跳过城市的情况
    for (int i = 2; i <= n; i++) {
        g[i] = g[i - 1] + get_distance(i - 1, i, x, y);
    }

    // 跳过一个城市的情况
    f[3] = get_distance(1, 3, x, y);

    for (int i = 4; i <= n; i++) {

        // 选择跳过 i-1，或者之前已经跳过一个城市
        f[i] = min(
            g[i - 2] + get_distance(i - 2, i, x, y),
            f[i - 1] + get_distance(i - 1, i, x, y)
        );
    }

    cout << f[n] << endl;

    return 0;
}
