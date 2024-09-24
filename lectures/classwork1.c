

#include <stdio.h>

int main(int argc, char* argv[])
{
    int count = 0;
    double input, total = 0, average = 0;
    while(scanf("%lf", &input)==1){
        total += input;
        count++;
        average = total / count;
        printf("total = %lf, average = %lf", average, count);
    }

    return 0;
}

#include <stdio.h>

int main(int argc, char* argv[])
{
    int grade;
    printf("Enter your score:");
    scanf("%d", &grade);
    if (grade>=90){
        printf("Grade : A\n");
    }else if (grade>=80){
        printf("Grade : B\n");
    }else if (grade>=70){
        printf("Grade : C\n");
    
    }else if (grade>=60){
        printf("Grade : D\n");
    
    }else{
        printf("Grade : F\n");
    }
    return 0;
}






/*
i didnt get to do question 3 because i had to move my car and thats why i left early, will attempt it for my sake later
*/

#include <stdio.h>

int main(int argc, char* argv[])
{
    double input1;
    double input2;
    scanf("%lf", &input1);
    

    return 0;
}




