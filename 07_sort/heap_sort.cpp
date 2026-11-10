/*
堆排序（大根堆，下标从1开始）
最好时间复杂度：O(nlogn)
平均时间复杂度：O(nlogn)
最坏时间复杂度：O(nlogn)
空间复杂度：O(logn)（递归调整堆）
不稳定排序
*/

#include <bits/stdc++.h>
using namespace std;

// 向下调整大根堆
void check(int a[],int len,int i){
    int left = 2*i,right = left+1;
    int maxI = i;

    if(left<=len && a[left]>a[maxI])
        maxI = left;

    if(right<=len && a[right]>a[maxI])
        maxI = right;

    if(maxI!=i){
        swap(a[i],a[maxI]);
        check(a,len,maxI);
    }
}

// 建立大根堆
void build_heap(int a[],int len){
    int i = len/2;
    while(i>0){
        check(a,len,i);
        i--;
    }
}

// 依次取出堆顶最大值
void sort_a(int a[],int len){
    int i = len;
    while(i>1){
        swap(a[1],a[i]);
        check(a,i-1,1);
        i--;
    }
}

// 堆排序
void heap_sort(int a[],int len){
    build_heap(a,len);
    sort_a(a,len);
}

int main(){
    // a[0] 不参与排序
    int a[] = {0,8,3,5,1,9,2,5,7};
    int len = sizeof(a)/sizeof(a[0])-1;

    cout << "排序前：";
    for(int i=1;i<=len;i++)
        cout << a[i] << " ";
    cout << endl;

    heap_sort(a,len);

    cout << "排序后：";
    for(int i=1;i<=len;i++)
        cout << a[i] << " ";
    cout << endl;

    return 0;
}
