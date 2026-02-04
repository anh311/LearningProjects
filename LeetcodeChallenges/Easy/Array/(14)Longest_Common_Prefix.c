char* longestCommonPrefix(char** strs, int strsSize) {
    char* pre=strs[0];
    if (strsSize==0){
        return "";
    }
    
    for (int i = 1; i<strsSize;i++){
        int j=0;
        while (pre[j] != '\0' && strs[i][j] != '\0' && strs[i][j] == pre[j]){
            j++;
        }
        pre[j]='\0';
    }
    
    return pre;
}