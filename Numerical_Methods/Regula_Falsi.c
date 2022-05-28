// This project is to help ease the process of finding a real root of a polynomial equation.

#include <stdio.h>
#include <math.h>

float interval(int coefficient[], int degree, float *start, float *end);
float regula_falsi(int coefficient[], int degree, float start, float end, float switcher);
float function(int coefficient[], int degree, float num);

int main()
{
    // Input of the highest power of the polynomial eq and the coefficients of the elements.
    int degree;
    printf("Enter the degree of the polyomial eq:");
    scanf("%d", &degree);
    int coefficient[degree + 1];

    for (int i = (degree); i >= 0; i--)
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
    printf("\n\n");

    // Find the interval in which the root lies
    float start, end;

    // This is to keep track of which side is +ve and -ve
    // +ve - start is +ve
    // -ve - start is -ve
    float switcher;
    switcher = interval(coefficient, degree, &start, &end);
    printf("The root of the equation lies in the interval: (%f,%f)\n\n", start, end);

    // Application of Regula Falsi
    regula_falsi(coefficient, degree, start, end, switcher);

    return 0;
}

float interval(int coefficient[], int degree, float *start, float *end)
{
    int sum, index;
    printf("Enter the value of extremes to check(Note that the first interval with the solution will be applied):");
    scanf("%d", &index);
    int solution[(2 * index) + 1];

    // Calculation of the solutions of polynomials between -index and index and the solutions are stored in solution[]
    for (int i = (-index); i <= index; i++)
    {
        solution[i + index] = function(coefficient, degree, i);
    }

    // Checking for condition of f(a).f(b)<0 to set intervals
    for (int i = 0; i < (2 * index) + 1; i++)
    {
        if (solution[i] * solution[i + 1] < 0)
        {
            *start = (i - index);
            *end = (i - (index - 1));

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

float regula_falsi(int coefficient[], int degree, float start, float end, float switcher)
{
    float function_start, function_end, function_mid, mid;
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("| Iteration \t|(Start,End) \t\t|f(Start) \t|f(End) \t|X \t|f(X) \t\t|(Start',End') \t |\n");
    printf("------------------------------------------------------------------------------------------------------------------\n");

    // Counter to iterate through 10 iterations
    int counter = 1, counter_root = 0;
    while (counter <= 10)
    {
        function_start = function(coefficient, degree, start);
        function_end = function(coefficient, degree, end);

        // Applying the Regula Falsi Theorem
        mid = ((start * function_end) - (end * function_start)) / (function_end - function_start);
        function_mid = function(coefficient, degree, mid);

        // Printing the values in the table
        printf("| %d \t\t|(%.4f,%.4f) \t|%.4f \t|%.4f \t|%.4f |%.4f \t|", counter, start, end, function_start, function_end, mid, function_mid);

        // Case if the value of f(mid)>0, hence switch mid with start or end
        if (function_mid > 0)
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

        // Case if the value of f(mid)<0, hence switch mid with start or end
        else if (function_mid < 0)
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

        // Printing the new interval
        printf("(%.4f,%.4f) |\n", start, end);

        // Case if the value of f(mid)==0, ie the root of the eq is mid
        if (function_mid == 0)
        {
            counter_root++;
            printf("------------------------------------------------------------------------------------------------------------------\n");
            printf("\nThe root of the given equation is: %.4f", mid);
            break;
        }
        counter++;
    }

    // counter_root is established to avoid overlapping of lines
    if (counter_root == 0)
    {
        printf("------------------------------------------------------------------------------------------------------------------\n");
    }

    return 0;
}

float function(int coefficient[], int degree, float num)
{
    // Returns value of the polynomial equation for a given number num
    float sum = 0;
    for (int j = degree; j >= 0; j--)
    {
        sum += (coefficient[j] * (pow(num, j)));
    }

    return sum;
}