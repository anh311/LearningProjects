#include <stdio.h>
#include <stdlib.h>
int compare(const void *a, const void*b){
    return (*(int*)a - *(int*)b);
}

int maximizeSquareHoleArea(int n, int m, int* hBars, int hBarsSize, int* vBars, int vBarsSize) {
    qsort(hBars,hBarsSize,sizeof(int),compare);
    qsort(vBars,vBarsSize,sizeof(int),compare);
    int countmax=0;
    int countmax1=0;
    
    for (int i=0; i<hBarsSize;i++){
        int count=0;
        for (int j =i;j<hBarsSize-1;j++){
            if (hBars[j]+1!=hBars[j+1]){
                break;
            }
            count++;
        }
        if(count>countmax){
            countmax=count;
        }
    }
     for (int i=0; i<vBarsSize;i++){
        int count1=0;
        for (int j =i;j<vBarsSize-1;j++){
            if (vBars[j]+1!=vBars[j+1]){
                break;
            }
            count1++;
        }
        if(count1>countmax1){
            countmax1=count1;
        }
    }
    if(countmax>countmax1){
        return (2+countmax1)*(2+countmax1);
    }
    return (countmax+2)*(countmax+2);
}