int bitwiseComplement(int n) {
    if (n==0) return 1;
    int k=__builtin_clz(n);
    printf("%d\n",k);
    for (int i = 0; i < 32-k ;i++){
        n=n^(1<<i);
    }
    return n;
}