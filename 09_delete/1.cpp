#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int a[1005] = {0};

    a[0] = 1;
    a[1] = 1;

    for (int i = 2; i <= n; i++) {
        a[i] = (a[i - 1] + 2 * a[i - 2]) % 12345;
    }

    cout << a[n] << endl;

    return 0;
}
