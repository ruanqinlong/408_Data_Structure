
#include <bits/stdc++.h>
using namespace std;

/*
希尔排序
最好时间复杂度：O(nlogn)
最坏时间复杂度：O(n^2)
空间复杂度：O(1)
不稳定排序
*/

// 希尔排序
void shell_sort(int a[], int len){
    int temp,d,i,j;

    for(d=len/2;d>=1;d/=2){
        for(i=d;i<len;i++){
            if(a[i]<a[i-d]){
                temp = a[i];

                for(j=i-d;j>=0 && a[j]>temp;j-=d){
                    a[j+d] = a[j];
                }

                a[j+d] = temp;
            }
        }
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
    int a[] = {49,38,65,97,76,13,27,49,55,4};
    int len = sizeof(a)/sizeof(a[0]);

    cout << "排序前：";
    print_array(a,len);

    shell_sort(a,len);

    cout << "排序后：";
    print_array(a,len);

    return 0;
}
