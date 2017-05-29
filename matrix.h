#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED







typedef struct matrix matrix;

//all functions take pointer to matrix, never matrix by value

int matrix_irandom(int, int);
//from krowa.h library
//renamed to avoid conflicts

matrix* matrix_init(int, int);
//creates matrix with int1 columns and int2 rows
//returns pointer to created matrix

matrix* matrix_init1(int);
//creates identity matrix intXint
//returns pointer to created matrix

matrix *matrix_copy(matrix *);
//copies matrix
//returns pointer to created matrix

void matrix_set(int, matrix*, int, int);
//sets cell in matrix* matrix int2 col and int3 row to int1 value

void matrix_randomize(matrix*);
//sets all cells in marix to random values

int matrix_get(matrix*, int, int);
//return value in matrix in int1 column and int2 row


int matrix_get_width(matrix*);
//returns width of matrix (number of columns)

int matrix_get_height(matrix*);
//return height of matrix (number of rows)

int matrix_count(matrix*);
//return number of elements in matrix

int matrix_sum(matrix*);
//returns sum of all elements in matrix

int matrix_column_sum(matrix*, int);
//returns sum of elements in column int1 in matrix

float matrix_column_avg(matrix*, int);
//return average of elements in int1 column in matrix

int matrix_row_sum(matrix*, int);
//return sum of elements in int1 row in matrix

float matrix_row_avg(matrix*, int);
//returns average in int1 row in matrix

int matrix_min(matrix*);
//return lowest value in matrix

int matrix_max(matrix*);
//return highest value in matrix

matrix* matrix_transpose(matrix*);
//creates transposed matrix
//return pointer to created matrix

int matrix_compare(matrix*, matrix*);
//compares matrix1 and matrix2
// returns -1 if sizes are differens
// returns -2 if not all of their elements are equal
// returns 0 matrix1 is equal to matrix2

matrix* matrix_add(matrix*, matrix*);
//adds matrix1 and matrix2 and creates new matrix
//returns pointer to created matrix

matrix* matrix_mult(matrix*, matrix*);
//multiplies matrix1 and matrix2 and creates new matrix
//returns pointer to created matrix

matrix *matrix_minor(matrix *, int, int);
//creates minor of a matrix after deleting int1 column and int 2 row
//returns pointer to minor

matrix *matrix_delete_column(matrix *, int);
//creates a matrix from original matrix after removing int column
//returns pointer to created matrix old pointer is invalid
//memory of old matrix is freed

matrix *matrix_delete_row(matrix *, int);
//creates a matrix from original matrix after removing int row
//returns pointer to created matrix old pointer is invalid
//memory of old matrix is freed

int matrix_determinant(matrix *);
//returns determinant of a matrix
//doesn't work on matrices larger than 4x4 (probably not enough memory or just because i'm a scrub)

void matrix_show(matrix*);
//prints matrix's height, width and elements

void matrix_clear(matrix*);
//sets all of matrix's elements to 0

matrix* matrix_load(const char*);
//loads matrix from file at path char*1
//files format:
// cells in every row should be seperated with tab characters
// every row should ends with new line chracter (including last one)

void matrix_delete(matrix*);
//deletes matrix from memory


#endif // MATRIX_H_INCLUDED
