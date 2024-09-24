#include <stdio.h>
#include <stdlib.h>
double power(double exponent, double j);

int main()
{
	int n, i;

	printf("n = ");
	scanf("%d", &n);

	double pi = 0.;
	//TODO
	//add code below 
	
	for (i=0;i<=n;i++){
		double x = power(i,16); 
		pi += ((4.0/((8*i)+1))-(2.0/((8*i)+4))-(1.0/((8*i)+5))-(1.0/((8*i)+6)))*(1/x);

	}

	printf("PI = %.10f\n", pi);
	return 0;
}

double power(double exponent, double j){
	double result = 1;
	for (int i=0; i<exponent; i++){
		result  *= j;

	}
	return result; 
}