//
//  kiosk.c
//
//  Created by Dimitris Tzannetos on 11/18/12.
//
//  Version : 1.0.2 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

double *coordinates,distance;
int *applications,N;

double solver (double,double);
int main(){
    
    double offset,position,max,result;
    int i;
    
    scanf("%d %lf",&N,&distance);
    coordinates = (double *)malloc(N*sizeof(double));
    applications = (int *)malloc(N*sizeof(int));
    scanf("%lf %d",&coordinates[0],&applications[0]);
    position = coordinates[0];
    position = position + (applications[0]-1)*distance;
    offset = position - coordinates[0];
    max = offset;
	
    for (i=1 ; i < N ; i++){
        scanf("%lf %d",&coordinates[i],&applications[i]);
        position += distance;
        if (position < coordinates[i]) position = coordinates[i] ;
		position = position + (applications[i]-1)*distance;
        offset = position - coordinates [i];
       	
        if (offset > max )
            max = offset;
    }
    result = solver(0,max);
    printf("%.2lf\n",result);
    free(coordinates);
    free(applications);
    return 0 ;
}


double solver (double start , double finish){
    
    int i,found;
    double dist,position,next,result,fix;
    result = finish ;
    if (fabs(start - finish) > 0.001){
         
        dist = (start + finish)/2;
        i = 0;
        found = 0 ;
        fix = coordinates[0]-dist;
        while ((i < N) && (found == 0)){
          
            position = coordinates[i] - dist;
            next = (applications[i]-1)*distance;
            position = MAX(position,fix);
            if ((fabs(position - coordinates[i]) <= dist) && (fabs( position + next - coordinates[i]) <= dist)){
                
                fix = position + next + distance ;
                i++;
            }
            else 
                found = -1 ;
        }
        
        if (found == 0)  
            result = solver(start,dist);
        else
            result = solver(dist,finish);
    }
    return result;
}
