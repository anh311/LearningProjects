int compare(const void* a, const void* b){
    int an =*(const int*) a;
    int bn =*(const int*) b;
    return (an-bn);
}

int minOperations(int* nums, int numsSize) {
    int count=0;
    qsort(nums,numsSize,sizeof(int),compare);
    for (int i=0; i<numsSize;i++){
        if ((nums[i]&1)==1){
            nums[i]-=1;
            count++;
        }
    }
    int i=0;
    while(nums[numsSize-1]!=0 ){
    
        if((nums[i]&1)==1){
            count++;
            nums[i]--;
        }

        nums[i]>>=1;
        i++;
        if(i==numsSize && nums[numsSize-1]!=0){
            i=0;
            count++;    
        } 
        
    }
    return count;
}