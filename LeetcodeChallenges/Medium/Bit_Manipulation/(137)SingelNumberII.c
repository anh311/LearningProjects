int singleNumber(int* nums, int numsSize) {
    int arr[32]={0};
    for (int i=0;i<numsSize;i++){
        for (int j=0;j<32;j++){
            if((nums[i]>>j)&1){
                arr[j]+=1;
            }
            
        }
    }
    int result=0;
    for (int j=0;j<32;j++){
        if(arr[j]%3!=0){
            result|=(1U<<j);
        }
            
    }
    return result;
}