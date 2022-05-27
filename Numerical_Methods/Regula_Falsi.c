// This project is to help ease the process of finding a root of a polynomial equation.

#include <stdio.h>
#include <math.h>

float interval(int coefficient[], int degree, float *start, float *end);
float regula_falsi(int coefficient[],int degree, float*start, float *end);
float function(int coefficient[],int degree,int num);

int main()
{
    int i, j, k;

    // Input of the highest power of the polynomial eq and the coefficients of the elements.
    int degree;
    printf("Enter the degree of the polyomial eq:");
    scanf("%d", &degree);
    int coefficient[degree + 1];

    for (i = (degree); i >= 0; i--)
    {
        if (i == 0)
        {
            printf("Enter the constant:");
            scanf("%d", &coefficient[0]);
        }
        else if (i > 0)
        {
            printf("Enter the coefficient of x^[%d]:", i);
            scanf("%d", &coefficient[i]);
        }
    }

    // Printing the entered coefficient.
    printf("\nEntered polynomial:\n");
    for (int i = (degree); i >= 0; i--)
    {
        printf("%dx^[%d]\t", coefficient[i], i);
    }
    printf("\n");

    // Find the interval in which the root lies
    float start, end;

    // This is to keep track of which side is +ve and -ve
    // +ve - start is +ve
    // -ve - start is -ve
    float switcher;
    switcher = interval(coefficient, degree, &start, &end);
    printf("The root of the equation lies in the interval: (%f,%f)\n\n", start, end);

    //Application of Regula Falsi
    float regula_falsi();

    return 0;
}

float interval(int coefficient[], int degree, float *start, float *end)
{
    int solution[21], sum,index;

    // Calculation of the solutions of polynomials between -index and index
    for (int i = (-10); i <= 10; i++)
    {
        sum = function(coefficient,degree,i);
        solution[i+10]=sum;
    }

    for (int i = 0; i < 21; i++)
    {
        if (solution[i] * solution[i + 1] < 0)
        {
            *start = (i - 10);
            *end = (i - 9);

            // Returns a value for switcher
            if (solution[i] < 0)
            {
                return -1.00;
            }
            else if (solution[i] > 0)
            {
                return 1.00;
            }
        }
    }
    return 0;
}

float regula_falsi(int coefficient[],int degree, float*start, float *end)
{
    
}

float function(int coefficient[],int degree,int num)
{
    float sum = 0;
    for (int j = degree; j >= 0; j--)
    {
        sum += (coefficient[j] * (pow(num, j)));
    }
    return sum;
}