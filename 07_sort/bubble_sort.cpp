
/*
冒泡排序（优化版）
最好时间复杂度：O(n)
平均时间复杂度：O(n^2)
最坏时间复杂度：O(n^2)
空间复杂度：O(1)
稳定排序
*/

#include <bits/stdc++.h>
using namespace std;

// 冒泡排序
void bubble_sort(int a[], int len){
    for(int i=1;i<len;i++){
        bool flag = false; // 记录本趟是否发生交换

        for(int j=0;j<len-i;j++){
            if(a[j]>a[j+1]){
                swap(a[j],a[j+1]);
                flag = true;
            }
        }

        // 没有交换，说明数组已经有序
        if(!flag) return;
    }
}

// 输出数组
void print_array(int a[],int len){
    for(int i=0;i<len;i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

int main(){
    int a[] = {8,3,5,1,9,2,5,7};
    int len = sizeof(a)/sizeof(a[0]);

    cout << "排序前：";
    print_array(a,len);

    bubble_sort(a,len);

    cout << "排序后：";
    print_array(a,len);

    return 0;
}
