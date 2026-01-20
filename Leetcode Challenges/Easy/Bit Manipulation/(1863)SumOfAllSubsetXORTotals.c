int subsetXORSum(int* nums, int numsSize) {
    int totalsubsets= pow(2,numsSize);
    int** subsets = malloc(totalsubsets*sizeof(int*));
    int* subsetsize = malloc(totalsubsets*sizeof(int));

    for(int i=0;i<totalsubsets;i++){
        int count = 0;
        for (int j = 0; j<numsSize;j++){
            if(i & (1 << j)) {
                count++;
            }
        }

        subsetsize[i]=count;
        subsets[i]=malloc(count*sizeof(int));

        int k=0;
        for (int j = 0; j<numsSize;j++){
            if(i & (1 << j)) {
                subsets[i][k]=nums[j];
                k++;
            }
        }
    }
    int sum= 0 ;
    for(int i=0; i<totalsubsets;i++){
        int subsum=0;
        for (int j=0;j<subsetsize[i];j++){
            subsum ^= subsets[i][j];
        }
        sum+=subsum;
    }


    for(int i = 0; i < totalsubsets; i++) {
    free(subsets[i]);
    }
    free(subsets);
    free(subsetsize);
    return sum;
