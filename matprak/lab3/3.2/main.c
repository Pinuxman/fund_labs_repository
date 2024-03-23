#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <limits.h>

typedef enum status_code
{
    SUCCESS,
    INVALID_PARAMETER,
    BAD_ALOC

}status_code;

typedef struct
{
    double* cords;
    int dimension;

}Vector;

void print_vector(Vector vector, int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        printf("%lf", vector.cords[i]);

    }
    printf("\n");
}

status_code norm_of_Chebyshev(double* result, Vector vector, int dimension)
{
    if(dimension < 1)
    {
        return INVALID_PARAMETER;
    }
    double max = vector.cords[0];

    for (int i = 0; i < dimension; i++)
    {
        if (vector.cords[i] > max)
        {
            max = vector.cords[i];
        }
    }
    *result = max;
    return SUCCESS;


}

status_code p_norm(double* result, Vector vector, int dimension, int p)
{
    if (p < 1 || dimension <= 0)
    {
        return INVALID_PARAMETER;
    }
    double sum = 0.0;

    for (int i = 0; i < dimension; i++)
    {
        sum += pow(fabs(vector.cords[i]), p);
    }
    *result = pow(sum, 1.0/ p);

    return SUCCESS;
}

status_code a_norm(double* result, Vector vector, int dimension)
{
    if (dimension <= 0)
    {
        return INVALID_PARAMETER;
    }
    int unite_matrix[dimension][dimension];

    for (int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            if (i == j)
            {
                unite_matrix[i][j] = 1;
            }
            else
            {
                unite_matrix[i][j] = 0;
            }
        }
    }

    double res[dimension];
    double sum = 0.0;

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            sum += unite_matrix[i][j] * vector.cords[j];
        }
        res[i] = sum;
    }
    double pow_res = 0.0;
    for (int i = 0; i < dimension; i++)
    {
        pow_res += pow(res[i], 2);
    }
    *result = sqrt(pow_res);
    return SUCCESS;


}

status_code get_ans
(
    double* result, Vector* result_vector, int dimension, int p,
    status_code (*norm_of_chebyshev)(double*, Vector, int),
    status_code (*p_norm)(double*, Vector, int, int),
    status_code (*a_norm)(double*, Vector, int),
    int count, ...
)
{

    va_list(ptr);
    va_start(ptr, count);

    double max_res[3];
    max_res[0] = INT_MIN;
    max_res[1] = INT_MIN;
    max_res[2] = INT_MIN;

    for (int i = 0; i < count; i++)
    {
        Vector vector = va_arg(ptr, Vector);
        
        double result_[3];
        
        if (norm_of_chebyshev(&(result_[0]), vector, dimension) != SUCCESS)
        {
            return INVALID_PARAMETER;
        }

        if (p_norm(&(result_[1]), vector, dimension, p) != SUCCESS)
        {
            return INVALID_PARAMETER;
        }

        if (a_norm(&(result_[2]), vector, dimension) != SUCCESS)
        {
            return INVALID_PARAMETER;
        }
        for (int j = 0; j < 3; j++)
        {
            if(result_[j] > max_res[j])
            {
                max_res[j] = result_[j];
                result_vector[j] = vector;
                result[j] = max_res[j];

            }
        }
    }
    return SUCCESS;


}

int main()
{
    int p = 1;
    int dimension = 3;
    Vector vec1, vec2, vec3;

    vec1.cords = (double*)malloc(sizeof(double) * dimension);
    if (vec1.cords == NULL)
    {
        printf("failed to allocate memory\n");
        return BAD_ALOC;
    }
    vec1.cords[0] = 0.1;
    vec1.cords[1] = 0.5;
    vec1.cords[2] = 3.2;

    vec2.cords = (double*)malloc(sizeof(double) * dimension);
    if (vec2.cords == NULL)
    {
        printf("failed to allocate memory\n");
        return BAD_ALOC;
    }
    vec2.cords[0] = 0.1;
    vec2.cords[1] = 2.5;
    vec2.cords[2] = 3.2;

    vec3.cords = (double*)malloc(sizeof(double) * dimension);
    if (vec3.cords == NULL)
    {
        printf("failed to allocate memory\n");
        return BAD_ALOC;
    }
    vec3.cords[0] = 0.5;
    vec3.cords[1] = 2.5;
    vec3.cords[2] = 3.0;

    double result[3];
    Vector result_vector[3];
    int count = 3;

    get_ans(result, result_vector, dimension, p, norm_of_Chebyshev, p_norm, a_norm, count, vec1, vec2, vec3);

    for(int i = 0; i < count; i++)
    {
        printf("For norm number %d the longest vector is:\n", i + 1);
        print_vector(result_vector[i], dimension);
        printf("value of vector %lf\n", result[i]);
    }
    free(vec1.cords);
    free(vec2.cords);
    free(vec3.cords);
    return 0;
}