#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
typedef long long int ll;
typedef long long int  arr[100][100];
const ll mod=100000007;
arr a,b,c,aux;
ll k ;
int n,m,s,t;

void mult(arr a,arr b,arr c) {
    int i,j,x;
    memset(aux,0,sizeof(aux));
    for(x=0;x<n;x++)
        for(i=0;i<n;i++)
            if (a[i][x])
                for(j=0;j<n;j++)
                    aux[i][j]+=(ll)a[i][x]*b[x][j];
    
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if (aux[i][j]>=mod) c[i][j]=aux[i][j]%mod;
            else c[i][j]=aux[i][j]; 
             
}

int main(){
    int i,j,first,sec;
    if (scanf("%lld %d %d %d %d",&k,&n,&m,&s,&t)) ; 
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            b[i][j]=0;
            if (i == j)
                a[i][i]=1;
            else
                a[i][j]=0;
        }
    for(i=0;i<m;i++){
        if (scanf("%d %d\n",&first,&sec)) ; 
        b[first-1][sec-1]=1;
    }
    for(k--;k;k>>=1){
        if(k&1) mult(a,b,a);
        mult(b,b,b);
    }
    printf("%lld\n",a[s-1][t-1]);
    return 0; 
}
