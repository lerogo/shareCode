char c = 'A'
for(int i=123;i>0;--i){
    if(c>'z') c = 'A';
    arr[123-i] = c++;
}

search(arr,101);

search(arr,char x){
    for(int i=0;i<123;++i){
        if(arr[i]==x) return i;
    }
    return -1;
}