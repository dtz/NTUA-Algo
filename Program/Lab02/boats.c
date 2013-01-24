#include <stdio.h>
#include <stdlib.h>
int * A , * B ,* table;
int boats;
void Merge(int * , int *, int , int , int );
void MergeSort(int *,int *, int, int);
int binarySearch(int, int, int);
int calculate(void);
int main(){
    int i ;
    
    scanf("%d\n",&boats);
    A = (int *)malloc(sizeof(int)* boats);
    B = (int *)malloc(sizeof(int)* boats);
    for (i = 0 ; i < boats ; i++){
        scanf("%d %d",&A[i],&B[i]);
    }
    MergeSort(A,B,0,boats-1);
    table = (int *) malloc (sizeof(int)* boats);
    printf("%d\n",calculate());
	free(A);
	free(B);
	free(table);
    return 0 ;
}
void MergeSort(int *array,int *b, int left, int right)
{
    int mid = (left+right)/2;
    if(left<right)
    {
        /* Sort the left part */
        MergeSort(array,b,left,mid);
        /* Sort the right part */
        MergeSort(array,b,mid+1,right);
        /* Merge the two sorted parts */
        Merge(array,b,left,mid,right);
    }
}

void Merge(int *array, int *b , int left, int mid, int right)
{
    /*We need a Temporary array to store the new sorted part*/
    int tempArray[right-left+1];
    int aux[right-left+1];
    int pos=0,lpos = left,rpos = mid + 1,iter = 0;
    //printf("left is %d right is %d",lpos,rpos);
    while(lpos <= mid && rpos <= right)
    {
        
        if(array[lpos] < array[rpos])
        {
            tempArray[pos] = array[lpos];
            aux[pos] = b[lpos];
            pos++;lpos++;
        }
        else  if (array[lpos] == array[rpos]) {
            
            if (b[lpos] < b[rpos]){
                tempArray[pos] = array[lpos];
                aux[pos] = b[lpos];
                pos++;lpos++;
            }
            else {
                tempArray[pos] = array[rpos];
                aux[pos] = b[rpos];
                pos++;rpos++;
            }
        }
        else
        {
            
            tempArray[pos] = array[rpos];
            aux[pos] = b[rpos];
            pos++;rpos++;
        }
    }
    while(lpos <= mid) {
        tempArray[pos] = array[lpos];
        aux[pos] = b[lpos];
        pos++;lpos++;
    }
    while(rpos <= right){
        tempArray[pos] = array[rpos];
        aux[pos] = b[rpos];
        pos++;rpos++;
    }
    /* Copy back the sorted array to the original array */
    for(iter = 0;iter < pos; iter++)
    {
        array[iter+left] = tempArray[iter];
        b[iter+left] = aux[iter];
    }
    return;
}
int binarySearch(int left , int right , int key ){
    int m ;
    while (right- left > 1 ){
        m = left + (right-left)/2;
        if (table[m] > key)
            right = m ;
        else
            left = m ;
    }
    return right  ;
}
int calculate(){
    
    int len,i,temp;
    len  = 1;
    table[0] = B[0];
    for (i = 1 ; i < boats ; i++){
        if (B[i] < table[0])
        {
            table[0] = B[i];
             
        }
        else if (B[i] >= table[len-1]){
            table[len] = B[i];
            len++;
        }
        else {
            
            temp = binarySearch(-1,len-1,B[i]);
            table[temp] = B[i];
        }
    }
    return len ;
}
