/*
归并排序
时间复杂度：O(nlogn)
空间复杂度：O(n)
稳定性：稳定
*/
#include<bits/stdc++.h>

using namespace std;

void merge(int a[],int len,int left,int mid,int right){
    int b[len];
    for(int i = left ;i<=right;i++) b[i] = a[i];
    int i,j,k;
    for(i=left,j=mid+1,k=left;i<=mid&&j<=right;k++){
        if(b[i]<=b[j]){
            a[k] = b[i++];
        }else{
            a[k] = b[j++];
        }
    }
    
    while(i<=mid) a[k++] = b[i++];
    while(j<=right) a[k++] = b[j++];
}

void merge_sort(int a[],int len,int left,int right){
    if(left<right){
        int mid = (left+right)/2;
        merge_sort(a,len,left,mid);
        merge_sort(a,len,mid+1,right);
        merge(a,len,left,mid,right);
    }
}

int main(){
    int a[] = {8,3,5,1,9,2,7,4};
    int len = sizeof(a)/sizeof(a[0]);

    merge_sort(a,len,0,len-1);

    for(int x:a)
        cout << x << " ";

    return 0;
}