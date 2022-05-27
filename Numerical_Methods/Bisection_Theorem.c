// This project is to help ease the process of finding a root of a polynomial equation.

#include <stdio.h>
#include <math.h>

float interval(int coefficient[], int degree, float *start, float *end);
int bisection(int coefficient[], int degree, float start, float end, float switcher);

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

    // Application of Bisection Theorem
    bisection(coefficient, degree, start, end, switcher);

    return 0;
}

float interval(int coefficient[], int degree, float *start, float *end)
{
    int solution[11], sum;

    // Calculation of the solutions of polynomials between -5 and 5
    for (int i = (-5); i <= 5; i++)
    {
        sum = 0;
        for (int j = degree; j >= 0; j--)
        {
            sum += (coefficient[j] * (pow(i, j)));
        }
        solution[i + 5] = sum;
    }

    for (int i = 0; i < 11; i++)
    {
        if (solution[i] * solution[i + 1] < 0)
        {
            *start = (i - 5);
            *end = (i - 4);

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

int bisection(int coefficient[], int degree, float start, float end, float switcher)
{
    //Counter to iterate through 15 iterations
    int counter = 1;
    while (counter <= 15)
    {
        float mid = (start + end) / 2;
        float function = 0.00;
        for (int j = degree; j >= 0; j--)
        {
            function += (coefficient[j] * (pow(mid, j)));
        }

        //Prints values to terminal rounded off to 4 decimal spaces
        printf("%d \t| %.4f \t| %.4f \t| (%.4f,%.4f)\t|\n",counter,mid,function,start,end);

        //Case if the value of f(mid)==0, ie the root of the eq is mid
        if (function == 0)
        {
            printf("The root of the given equation is: %d", mid);
        }

        //Case if the value of f(mid)>0, hence switch mid with start or end
        else if (function > 0)
        {
            if (switcher == 1)
            {
                start = mid;
            }
            else if (switcher == -1)
            {
                end = mid;
            }
        }   

        //Case if the value of f(mid)<0, hence switch mid with start or end
        else if (function < 0)
        {
            if (switcher == 1)
            {
                end = mid;
            }
            else if (switcher == -1)
            {
                start = mid;
            }
        }
        counter++;
    }
    return 0;
}
