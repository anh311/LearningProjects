/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* diStringMatch(char* s, int* returnSize) {
    int l = strlen(s);
    int a = 0;
    int b = l;
    int * arr=calloc(l+1,sizeof(int));
    *returnSize=l+1;
    for (int k=0;k<l+1;k++){
        if(s[k]=='I'){
            arr[k]=a;
            a++;
        }
        else{
            arr[k]=b;
            b--;
        }
    }
    arr[l]=a;
    return arr;
}