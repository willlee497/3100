#include <stdio.h>

int main(){
    int n, i, sum = 0;
    float average;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter %d elements:\n", n);
    /* todo create an array of size n to store the user input and compute the average*/
    int num[n];
    for(i=0;i<n;i++){
        scanf("%d",&num[i]);
        sum += num[i];
    }
    average = (float)sum / n;



    printf("Average =%.2f\n", average);
    return 0;
}

/* todo swap the values pointed by x and y*/

#include <stdio.h>
void swap(int *x, int *y){
    int z = *y; /* temp variable & address of pointer * deferencing the pointer*/
    *x = *y;
    *y = z;
    return;
}

int main(){
    int a = 10, b=20;
    swap(&a,&b); /* the call */
    printf("Before swapping: a = %d, b=%d\n", a, b);
    printf("After swapping: a = %d, b=%d\n", a, b);
    return 0;
}

/* todo call the swap function to swap the values just do call for swapping*/


#include <stdio.h>

void printMat(int n, int x[n][n]){
    /*todo print the matrix stored in x*/
    for (int i=0; i<n;i++){
        for (int j=0; j<n; j++){
            int v = x[i][j];
            printf("%d", v);
        }
        printf("\n");
    }
    return;
}

int main(){
    int imatrix[3][3] = {{1,0,0}, {0,1,0}, {0,0,1}}; /* array has to have size this is 2d add another [3] to make it a cubed size cant do [n] leave blank or set size*/
    int arr[n][n];
    printMat(3, imatrix); 
    return 0;
}


#include <stdio.h>
#include <stdlib.h>

void printMat(intn, int**x){
    /*print the matrix stored in x*/
    
    return;
}

int main (){
    int n=4; /* assume we are creating square matrix of size 4x4*/

    /*allocate memory and initialize a 2d matrix of n*n call the printmat func to print the matrix*/
}