int Scan(&x){
    int num = 0;
    for(int i=0;i<x.length;++i){
        switch (x[i])
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            ++num;
            cout<<"Pos is:"<<i+1<<endl;
        }
    }
    return num;

}