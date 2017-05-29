#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"


struct matrix
{
    int cols;
    int rows;
    int* content;
};


typedef struct matrix matrix;


int matrix_irandom(int a, int b)
{
    return rand()%(b+1-a)+a;
}


matrix* matrix_init(int cols, int rows)
{
    matrix* ptr = malloc(sizeof(matrix));
    ptr->cols = cols;
    ptr->rows = rows;
    ptr->content = (int*)malloc(cols * rows * sizeof(int));
    matrix_clear(ptr);
    return ptr;
};

matrix* matrix_init1(int input)
{
    matrix* ptr = matrix_init(input, input);
    int i;
    for(i = 0; i < input; ++i)
    {
        *(ptr->content + i + i * input) = 1;
    }
    return ptr;
}

matrix *matrix_copy(matrix *ptr)
{
    int x = matrix_get_width(ptr);
    int y = matrix_get_height(ptr);
    matrix *new_matrix = matrix_init(x, y);
    int i, j;
    for(j = 0; j < y; ++j)
    {
        for(i = 0; i < x; ++i)
        {
            matrix_set(matrix_get(ptr, i, j), new_matrix, i, j);
        }
    }
    return new_matrix;
}

void matrix_set(int x, matrix* ptr, int col, int row)
{
    *(ptr->content + col + row * matrix_get_width(ptr)) = x;
}

void matrix_randomize(matrix* ptr)
{
    int a = matrix_get_width(ptr) * matrix_get_height(ptr);
    int i;
    for(i = 0; i < a; ++i)
    {
        *(ptr->content + i) = matrix_irandom(0, 39);
    }
}

int matrix_get(matrix* ptr, int col, int row)
{
    return *(ptr->content + col + row * matrix_get_width(ptr));
}

int matrix_get_width(matrix* ptr)
{
    return ptr->cols;
}

int matrix_get_height(matrix* ptr)
{
    return ptr->rows;
}

int matrix_count(matrix* ptr)
{
    return matrix_get_width(ptr) * matrix_get_height(ptr);
}

matrix *matrix_minor(matrix *ptr, int col, int row)
{
    matrix *minor = matrix_copy(ptr);
    minor = matrix_delete_column(minor, col);
    minor = matrix_delete_row(minor, row);
    return minor;
}

matrix *matrix_delete_column(matrix *ptr, int del)
{
    matrix *new_matrix = matrix_init(matrix_get_width(ptr) - 1, matrix_get_height(ptr));
    int i = 0, j = 0;
    for(j = 0; j < matrix_get_height(ptr); ++j)
    {
        int a = 0;
        for(i = 0; i < matrix_get_width(ptr); ++i)
        {
            if(i == del)
            {
                a = -1;
                continue;
            }
            matrix_set(matrix_get(ptr, i, j), new_matrix, i + a, j);
        }
    }
    matrix_delete(ptr);
    return new_matrix;
}

matrix *matrix_delete_row(matrix *ptr, int del)
{
    matrix *new_matrix = matrix_init(matrix_get_width(ptr), matrix_get_height(ptr) - 1);
    int i = 0, j = 0;
    int a = 0;
    for(j = 0; j < matrix_get_height(ptr); ++j)
    {
        if(j == del)
        {
            a = -1;
            continue;
        }
        for(i = 0; i < matrix_get_width(ptr); ++i)
        {
            matrix_set(matrix_get(ptr, i, j), new_matrix, i, j + a);
        }
    }
    matrix_delete(ptr);
    return new_matrix;
}

int matrix_determinant(matrix *ptr)
{
    if(matrix_get_width(ptr) != matrix_get_height(ptr))
    {
        printf("You passed wrong matrix scrub\nreturning wrong value just because\n");
        return 42;
    }
    if(matrix_get_width(ptr) == 1)
        return matrix_get(ptr, 0, 0);
    int s = 0;
    int factor = 1;
    int i;
    for(i = 0; i < matrix_get_width(ptr); ++i)
    {
        s += matrix_get(ptr, i, 0)*factor*matrix_determinant(matrix_minor(ptr, i, 0));
        factor *= -1;
    }
    return s;
}

void matrix_show(matrix* ptr)
{
    printf("--------------------------------------\n");
    printf("height: %d\n", matrix_get_height(ptr));
    printf("width: %d\n", matrix_get_width(ptr));
    printf("\n\n");
    int i, j;
    for(j = 0; j < matrix_get_height(ptr); ++j)
    {
        for(i = 0; i < matrix_get_width(ptr); ++i)
        {
            printf("%10d ", matrix_get(ptr, i, j));
        }
        printf("\n");
    }
    printf("--------------------------------------\n\n\n");
}

void matrix_clear(matrix* ptr)
{
    int cols = matrix_get_width(ptr);
    int rows = matrix_get_height(ptr);
    int i, j;
    for(i = 0;i < cols; ++i)
    {
        for(j = 0; j < rows; ++j)
            *(ptr->content + i + j) = 0;
    }
}

int matrix_sum(matrix* ptr)
{
    int i;
    int s = 0;
    for(i = 0; i < matrix_get_height(ptr); ++i)
    {
        s += matrix_row_sum(ptr, i);
    }
    return s;
}

int matrix_column_sum(matrix* ptr, int col)
{
    int s = 0;
    int i;
    for(i = 0; i < matrix_get_height(ptr); ++i)
    {
        s += matrix_get(ptr, col, i);
    }
    return s;
}

int matrix_row_sum(matrix* ptr, int row)
{
    int s = 0;
    int i;
    for(i = 0; i < matrix_get_width(ptr); ++i)
    {
        s += matrix_get(ptr, i, row);
    }
    return s;
}

float matrix_column_avg(matrix* ptr, int col)
{
    return (float)matrix_column_sum(ptr, col)/matrix_get_height(ptr);
}

float matrix_row_avg(matrix* ptr, int row)
{
    return (float)matrix_row_sum(ptr, row)/matrix_get_width(ptr);
}

int matrix_min(matrix* ptr)
{
    int min = *(ptr->content);
    int i = 0;
    int count = matrix_count(ptr);
    for(i = 0; i < count; ++i)
    {
        if(  *(ptr->content + i) < min )
        {
            min = *(ptr->content + i);
        }
    }
    return min;
}

int matrix_max(matrix* ptr)
{
    int max = *(ptr->content);
    int i;
    int count = matrix_count(ptr);
    for(i = 0; i < count; ++i)
    {
        if(  *(ptr->content + i) > max )
        {
            max = *(ptr->content + i);
        }
    }
    return max;
}

matrix* matrix_transpose(matrix* ptr)
{
    matrix* p = matrix_init(matrix_get_height(ptr), matrix_get_width(ptr));
    int i, j;
    for(j = 0; j < matrix_get_height(p); ++j)
    {
        for(i = 0; i < matrix_get_width(p); ++i)
        {
            int x = matrix_get(ptr, j, i);
            matrix_set(x, p, i, j);
        }
    }
    return p;
}

int matrix_compare(matrix* ptr1, matrix* ptr2)
{
    if( (matrix_get_width(ptr1) != matrix_get_width(ptr2)) || matrix_get_height(ptr1) != matrix_get_height(ptr2) )
    {
        return -1;
    }
    int i, j;
    for(j = 0; j < matrix_get_height(ptr1); ++j)
    {
        for(i = 0; i < matrix_get_width(ptr1); ++i)
        {
            if( matrix_get(ptr1, i, j) != matrix_get(ptr2, i, j)  )
                return -2;
        }
    }
    return 0;
}

matrix* matrix_add(matrix* ptr1, matrix* ptr2)
{
    if( (matrix_get_width(ptr1) != matrix_get_width(ptr2)) || matrix_get_height(ptr1) != matrix_get_height(ptr2) )
    {
        printf("wrong matrices sizes\n\n");
        return NULL;
    }

    matrix* ptr = matrix_init(matrix_get_width(ptr1), matrix_get_height(ptr1));
    int i, j;
    for(j = 0; j < matrix_get_height(ptr1); ++j)
    {
        for(i = 0; i < matrix_get_width(ptr1); ++i)
        {
            *(ptr->content + i + j * matrix_get_width(ptr1)) = matrix_get(ptr1, i, j) + matrix_get(ptr2, i, j);
        }
    }
    return ptr;

}

matrix* matrix_mult(matrix* ptr1, matrix* ptr2)
{
    if( (matrix_get_width(ptr1) != matrix_get_height(ptr2))  )
    {
        printf("wrong matrix sizes\n\n");
        return NULL;
    }

    matrix* ptr = matrix_init(matrix_get_width(ptr2), matrix_get_height(ptr1));
    int i, j, k, s;
    for(j = 0; j < matrix_get_height(ptr); ++j)
    {
        for(i = 0; i < matrix_get_width(ptr); ++i)
        {
            s = 0;
            for(k = 0; k < matrix_get_height(ptr2); ++k)
            {
//                matrix_get(ptr, col, row)
                s += matrix_get(ptr1, k, j)*matrix_get(ptr2, i, k);
            }
            matrix_set(s, ptr, i, j);
        }
    }
    return ptr;
}

matrix* matrix_load(const char* file_name)
{
    int rows = 0, cols = 0;
    FILE* f;
    if ( (f = fopen(file_name, "r")) == NULL  )
    {
        printf("couldn't open a file\n\n");
        return NULL;
    }
    char buff;
    while(  (buff = fgetc(f) ) != '\n' )
    {

        if(buff == '\t')
        {
            ++cols;
        }
    }

    ++cols;

    fseek(f, 0, 0);

    while( (buff = fgetc(f) ) != EOF)
    {
        if(buff == '\n')
        {
            ++rows;
        }
    }
    matrix* ptr = matrix_init(cols, rows);

    int i, j;
    fseek(f, 0, 0);

    for(i = 0; i < rows; ++i)
    {
        for(j = 0; j < cols; ++j)
        {
            fscanf(f, "%d", ptr->content + j + i * cols);
        }
    }

    fclose(f);

    return ptr;
}

void matrix_delete(matrix* ptr)
{
    free(ptr);
}
