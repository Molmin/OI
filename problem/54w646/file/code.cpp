// 2023.09.02

#include<bits/stdc++.h>
using namespace std;

int n,choice[100001];
int a[100001][2],b[100001][2],c[100001][2];
set<pair<int,int> > A,B,C;

int main(){
    int T; scanf("%d",&T);
    while(T--){
        A.clear(),B.clear(),C.clear();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&a[i][0],&b[i][0],&c[i][0]);
            scanf("%d%d%d",&a[i][1],&b[i][1],&c[i][1]);
            choice[i]=0;
            A.insert({a[i][0],i});
            B.insert({b[i][0],i});
            C.insert({c[i][0],i});
        }
        int answer=0x7fffffff;
        while(true){
            int aval=A.rbegin()->first-A.begin()->first,
                bval=B.rbegin()->first-B.begin()->first,
                cval=C.rbegin()->first-C.begin()->first;
            answer=min(answer,max({aval,bval,cval}));
            int x;
            if(aval>=bval&&aval>=cval)x=A.begin()->second;
            else if(bval>=cval)x=B.begin()->second;
            else x=C.begin()->second;
            if(choice[x]==1)break;
            choice[x]=1;
            A.erase({a[x][0],x}),A.insert({a[x][1],x});
            B.erase({b[x][0],x}),B.insert({b[x][1],x});
            C.erase({c[x][0],x}),C.insert({c[x][1],x});
        }
        printf("%d\n",answer);
    }
    return 0;
}