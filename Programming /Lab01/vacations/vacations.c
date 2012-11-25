//
//  vacations.c
//
//  Created by Dimitris Tzannetos on 11/17/12.
//
//

#include <stdio.h>
#include <stdlib.h>


int main() {
    
    //  temperature and aux arrays
    long long int *temp , *ascend , *descend ;
    //  input elements
    long long int N;
    int average;
    //  counters and aux variables
    long long i,j,peak,days,asCounter,deCounter;
    
    //  creating input array
    
    scanf("%lld %d",&N,&average);
    temp = (long long int *)malloc(N*sizeof(long long int));
    if (temp==0){
        printf("Error!: Out of memory!");
        return 1;
    }
    
    //  creating aux arrays
    ascend = (long long int *)malloc(N*sizeof(long long int));
    descend = (long long int *)malloc(N*sizeof(long long int));
    if (ascend== 0 ||descend==0){
        printf("Error!: Out of memory!");
        return 1;
    }
    
    // reading input
    
    scanf("%lld",&temp[0]);
    temp[0] = temp[0]-average;
    peak = temp[0];
    deCounter = 0 ;
    descend[deCounter] = 0 ;
    for (i=1 ; i < N ;i++){
        
        scanf("%lld",&temp[i]);
        temp[i]-=average;
        temp[i] = temp[i] + temp[i-1] ; // sigma sum of so far read temps
        
        //  create the descending sigma sum array while reading input
        if (temp[i] < peak){
            peak = temp[i];
            deCounter++;
            descend[deCounter] = i;
        }
    }
    
    //  input and descend array complete !
    //  create the ascending sigma sum array running through the temp array
    peak = temp[N-1]; //the entire sigma sum is made the new peak
    asCounter = 0 ;
    ascend[asCounter] = N-1;
    for (i= N-2 ; i >= 0 ; i--){
        if (temp[i] > peak){
            asCounter++;
            peak = temp[i];
            ascend[asCounter]=i;
        }
    }
    days = 0 ;
    j = deCounter;
    for (i=0; i <= asCounter; i++){
        if ((temp[ascend[i]] >=0)&&(ascend[i]>=days))
            days = ascend[i]+1;
        while ((j>=0)&&(temp[ascend[i]]-temp[descend[j]] >= 0)) {
            if (ascend[i] - descend[j] > days)
                days = ascend[i] - descend[j];
            j--;
        }
    }
    printf("%lld\n",days);
    free(temp);
    free(ascend);
    free(descend);
    return 0 ;
}
