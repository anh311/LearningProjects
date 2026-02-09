/*int largestCombination(int* candidates, int candidatesSize) {
    int max=0;
    for (int i =0;i<24;i++){
        int count=0;
        for (int j =0;j<candidatesSize;j++){
            if((candidates[j]&1)==1){
                count++;
            }
            candidates[j]>>=1;
        }
        if (count>max){
            max=count;
        }
    }
    return max;
}
*/
int largestCombination(int* candidates, int candidatesSize) {
    int max=0;
    for (int i =0;i<24;i++){
        int count=0;
        for (int j =0;j<candidatesSize;j++){
            if(candidates[j]&(1<<i)){
                count++;
            }
            if (count + (candidatesSize - j) <= max) break;
        }
        if (count>max){
            max=count;
        }
    }
    return max;
}