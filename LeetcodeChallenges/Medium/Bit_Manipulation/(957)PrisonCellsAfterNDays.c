/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* prisonAfterNDays(int* cells, int cellsSize, int n, int* returnSize) {
    int arr[8]={0};
    int arry[8]={0};
    int m=(n-1)% 14 +1;
    *returnSize=cellsSize;
    for (int i=0;i<m;i++){
        for (int j=1;j<7;j++){
            if (cells[j-1]==1 && cells[j+1]==1) arr[j]=1;
            else if(cells[j-1]==0 && cells[j+1]==0) arr[j]=1;
            else arr[j]=0;
        }
        arr[0]=0;
        arr[7]=0;
        memcpy(cells, arr, sizeof(arr));
    }
    return cells;
}