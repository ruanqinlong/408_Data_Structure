
/*
快速排序（挖坑法）
最好时间复杂度：O(nlogn)
平均时间复杂度：O(nlogn)
最坏时间复杂度：O(n^2)
空间复杂度：平均 O(logn)，最坏 O(n)
不稳定排序
*/

#include <bits/stdc++.h>
using namespace std;

// 快速排序
void quick_sort(int a[],int start,int end){
    if(start>=end) return;

    int k = a[start]; // 基准值
    int left = start,right = end;

    while(left<right){
        // 从右向左寻找小于基准值的元素
        while(left<right && a[right]>=k) right--;
        if(left<right) a[left++] = a[right];

        // 从左向右寻找大于基准值的元素
        while(left<right && a[left]<=k) left++;
        if(left<right) a[right--] = a[left];
    }

    a[left] = k; // 基准值归位

    // 递归排序左右区间
    quick_sort(a,start,left-1);
    quick_sort(a,left+1,end);
}

int main(){
    int a[] = {8,3,5,1,9,2,5,7};
    int len = sizeof(a)/sizeof(a[0]);

    cout << "排序前：";
    for(int x:a) cout << x << " ";
    cout << endl;

    quick_sort(a,0,len-1);

    cout << "排序后：";
    for(int x:a) cout << x << " ";
    cout << endl;

    return 0;
}
