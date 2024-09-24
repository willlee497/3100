#include <stdio.h>
#include <math.h>

double halleys(double x, double epsilon){
    double ps = 0;
    double s = x;
    while(fabs(s-ps>=epsilon)){
        s = ps * (ps * ps +3 * x) / (3*ps*ps+x);
        return s;
    }


    return 0;


}

int main(){
    int x;
    scanf("%d", &);


}




int move(int n, char a, char b, char c){
    


}

int main(){




}



/* Write a program to compute the number of moves needed in the Tower of Hanoi problem with n disks.
 * In the Tower of Hanoi problem, n disks are placed on a rod, say A, in increasing order of their sizes.
   The goal is to move the disks to another rod, say C, without ever putting larger disks on top of the smaller ones.
   You can use an auxiliary rod, say B, to help in the process.
 * Your function should return the total number of moves used to achieve this goal.
 */

#include <stdio.h>

/* This function returns the total number of moves required to move n disks from rod A to C using rod B */
int move(int n, char a, char b, char c) {
	/* Try to break down the problem into simpler sub-problems and implement this function recursively.*/
}

int main() {
	/* The user must input the number of disks n. 
	 * Use the move function above to calculate the number of moves needed. 
	 * Print the result */
}

/* Write a program to compute the square root of x using the Halley's method */

#include <stdio.h>
#include <math.h>

/* This function should compute the Halley's sequence */
double halleys(double x, double epsilon) {
	/* s = prev_s * (prev_s * prev_s + 3 * x) / (3 * prev_s * prev_s + x)
	 * Compute s as long as the absolute difference |s - prev_s| exceeds the given threshold epsilon
	 * Return the value of s when the difference is less than epsilon. */
		
}

int main() {
	/* The user must input x for which the sqrt needs to be calculated and a threshold epsilon that marks the convergence of our calculation.
	 * Use the halleys function above to calculate the square root. 
	 * Print the result */

	return 0;
}



/* Write a program that takes two numbers (double) and a basic arithmetic operator (+, -, *, /) 
   from the user and returns the result. Remember that division by zero should result in an error. 
   Use switch case for your implementation.
 */


