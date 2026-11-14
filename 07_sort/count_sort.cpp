
/*
 * 计数排序（Counting Sort）
 *
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 * 排序方式：非比较排序
 *
 * n：元素个数
 * k：关键字取值范围的大小
 *
 * 适用范围：非负整数，且关键字取值范围不宜过大
 */

#include <bits/stdc++.h>
using namespace std;

void count_sort(int a[], int len){
    if(len<=1) return;

    // 1. 找到最大值
    int max_num = a[0];
    for(int i=0;i<len;i++){
        if(max_num<a[i]) max_num = a[i];
    }

    // 2. 初始化计数数组
    int b[max_num+1];
    for(int i=0;i<=max_num;i++) b[i]=0;

    // 3. 统计每个元素出现的次数
    for(int i=0;i<len;i++){
        b[a[i]]++;
    }

    // 4. 计算前缀和
    // b[i] 表示小于等于 i 的元素个数
    for(int i=1;i<=max_num;i++){
        b[i] += b[i-1];
    }

    // 5. 从右向左遍历，保证排序稳定性
    int res[len];
    for(int i=len-1;i>=0;i--){
        res[--b[a[i]]] = a[i];
    }

    // 6. 将排序结果复制回原数组
    for(int i=0;i<len;i++){
        a[i] = res[i];
    }
}

int main(){
    int a[] = {4,2,2,8,3,3,1};
    int len = sizeof(a)/sizeof(a[0]);

    count_sort(a,len);

    for(int i=0;i<len;i++){
        cout << a[i] << " ";
    }

    return 0;
}
