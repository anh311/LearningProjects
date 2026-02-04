int removeDuplicates(int* nums, int numsSize) {
    if (numsSize == 0){
        return 0;
    }
    int* hash = calloc(201,sizeof(int));
    for (int i = 0; i < numsSize; i++){
        hash[nums[i]+100]+=1;
    }
    int k=0;
    for (int i = 0; i <  201; i++){
        if (hash[i]!=0){
            nums[k]=i-100;
            k++;
        }
    }
    
return k;
    
}