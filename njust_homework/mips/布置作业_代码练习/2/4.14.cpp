for(int i=100;i>0;--i){
    arr[100-i] = i;
}
getNum(arr);



getNum(arr){
    int cnt;
    for(int i=100;i>0;--i){
        if(arr[100-i]%4==0) cnt++;
    }
    return cnt;
}