
/*
简单选择排序
最好时间复杂度：O(n^2)
平均时间复杂度：O(n^2)
最坏时间复杂度：O(n^2)
空间复杂度：O(1)
不稳定排序
*/

#include <bits/stdc++.h>
using namespace std;

void select_sort(int a[],int len){
    for(int i=1;i<len;i++){
        int minIndex = i-1;

        // 在未排序区间中寻找最小值
        for(int j=i;j<len;j++){
            if(a[minIndex]>a[j]){
                minIndex = j;
            }
        }

        // 将最小值交换到未排序区间的开头
        swap(a[i-1],a[minIndex]);
    }
}

int main(){
    int a[] = {8,3,5,1,9,2,5,7};
    int len = sizeof(a)/sizeof(a[0]);

    cout << "排序前：";
    for(int x:a) cout << x << " ";
    cout << endl;

    select_sort(a,len);

    cout << "排序后：";
    for(int x:a) cout << x << " ";
    cout << endl;

    return 0;
}
