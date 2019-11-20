string longestPalindrome(string&s) {
        string news="$#";
        for(LL i=0;i<s.size();++i)
            news=news+s[i]+"#";
        vector<LL>p(news.size(),1);
        LL x=0,xr=0;
        for(LL i=1;i<news.size();++i){
            if(i<xr)
                p[i]=min(xr-i,p[2*x-i]);
            while(i+p[i]<news.size()&&news[i-p[i]]==news[i+p[i]])
                ++p[i];
            if(xr<i+p[i]){
                x=i;
                xr=i+p[i];
            }
        }
        LL k=max_element(p.begin()+1,p.end())-p.begin();
        return s.substr((k-p[k])/2,p[k]-1);//返回最长回文子串
    }
