arr = {21,32,3424,123,12,432,2,332,132,423,123}

for(int i=arr.length;i>0;--i){
    for(int j=1;j<i;++j){
        if(arr[j-1]>arr[j]) swap(arr[j-1],arr[j]);
    }
}

for(int i=0;i<arr.length;++i){
    cout<<arr[i]<<"\t";
}