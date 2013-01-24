#include <stdio.h>
#include <stdlib.h>
#define MIN(a,b) (((a)<(b))?(a):(b))

int main(){
    int ** table ;
    int *coins , cities;
    int i ,j,k,p,temp,m;
    scanf("%d\n",&cities);
    table = (int **)malloc(cities*sizeof(int*));
    coins = (int*)malloc((cities+1)*sizeof(int));
    coins[0] = 0 ; 
    for (i = 0 ; i < cities ; i++){
        table[i] = (int*)malloc(cities*sizeof(int));
        for (j = 0 ; j < cities ; j++){
                table[i][j] = 0 ;
        }
        scanf("%d",&coins[i+1]);
        coins[i+1] += coins[i];
    }
  
    for (p = 2 ; p <=cities ; p++){
        for (i = 0; i < cities  - p +1; i++) {
            j = i + p - 1;
            m = 0;
            for(k = i ; k < j  ; k++){
                temp = MIN((coins[k+1]-coins[i]+table[i][k]),(coins[j+1]-coins[k+1]+table[k+1][j]));
                if (temp > m)
                    m = temp;
            }
            table[i][j] = m ;
        }
    }
  
    printf("%d\n",table[0][cities-1]);
	 for (i = 0 ; i < cities ; i++)
        free(table[i]);
	free(coins);
	free(table);
    return 0 ;

}

