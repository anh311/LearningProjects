char repeatedCharacter(char* s) {
    char hash[] = {
    'q','w','e','r','t','z','u','i','o','p',
    'a','s','d','f','g','h','j','k','l',
    'y','x','c','v','b','n','m'
};
    int* hashnum  = calloc(26,sizeof(int));
    int len = strlen(s);
    for (int i = 0;i<len;i++){
        	for (int j=0;j<26;j++){
                if (hash[j]==(s[i])){
                    hashnum[j]++;
                }
                if (hashnum[j]==2) return hash[j];
            }

    }
    free(hashnum);
    return '\0';
}