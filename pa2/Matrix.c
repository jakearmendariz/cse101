
#include "List.h"
#include "Matrix.h"

typedef struct MatrixObj
{
    List *rows; //I am trying to turn this into an array of undefinite size inside of Matrix.c newMatrix function
    int size;
    int largest_row;
    
} MatrixObj;

typedef struct EntryObj
{
    int column;
    double value;
} EntryObj;

/**
 * newMatrix
 * 
 * n is the size of the nxn matrix
 */
Matrix newMatrix(int n)
{
    if (n < 0)
    {
        fprintf(stderr, "Error in newMatrix function, n is less than 0\n");
        return NULL;
    }
    Matrix a = malloc(sizeof(Matrix));
    a->rows = malloc(sizeof(List) * n);
    a->size = n;
    a->largest_row = 0;
    for (int i = 0; i < n; i++)
    {
        a->rows[i] = newList();
    }
    return a;
}

/**
 * newEntry
 * 
 * Creates an entryObj pointern with a column value and value
 */
Entry newEntry(int col, double value)
{
    if (col < 0)
    {
        fprintf(stderr, "Error in newEntry function, col is less than 0\n");
        return NULL;
    }
    Entry a = malloc(sizeof(Entry));
    a->value = value;
    a->column = col;
    return a;
}

/**
 * insertInOrder
 * 
 * inserts e into L in the proper column order
 */
void insertInOrder(List L, Entry e)
{

    //List L = M->rows[r];
    if (length(L) == 0)
    {
        append(L, e);
        return;
    }
    else
    {
        moveFront(L);
        while (getCol(get(L)) < e->column)
        {
            moveNext(L);
            if (L->cursor_pos == -1)
            {
                break;
            }
        }
        if (index(L) == -1)
        {
            append(L, e);
        }
        else if (getCol(get(L)) == e->column)
        {
            editEntry(get(L), (double)e->value);
            //freeEntry(&e);
        }
        else
        {
            insertBefore(L, e);
        }
    }
}
// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
// Still working on this function need to free entries
void freeMatrix(Matrix *pM)
{
    Matrix M = *pM;
    for (int i = 0; i < M->size; i++)
    {
        List L = M->rows[i];
        moveFront(L);
        while(get(L) != NULL){
            //This causes an error when I try to free the Entry. I don't know why, it should works
            //Entry e = get(L);
            //freeEntry(&e);
            moveNext(L);
        }
        freeList(&L);
    }
    free(*pM);
    M = NULL;
    pM = NULL;
}

void freeEntry(Entry *e)
{
    free(*e);
    e = NULL;
}
// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M)
{
    if (M == NULL)
    {
        fprintf(stderr, "Error in size function M is null\n");
        return 0;
    }
    return M->size;
}
// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M)
{
    if (M == NULL)
    {
        fprintf(stderr, "Error in size function M is null\n");
    }
    int count = 0;
    for (int i = 0; i < M->largest_row; i++)
    {

        List L = M->rows[i];
        moveFront(L);
        for (int j = 0; j < length(L); j++)
        {
            if (getVal(get(L)) != 0)
            {
                count++;
            }
            moveNext(L);
        }
    }
    return count;
}

int NNZ_row(Matrix M, int r)
{
    List L = M->rows[r];
    int count = 0;
    moveFront(L);
    for (int j = 0; j < length(L); j++)
    {
        if (getVal(get(L)) != 0)
        {
            count++;
        }
        moveNext(L);
    }
    return count;
}

//equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B)
{
    if (A == NULL || B == NULL)
    {
        fprintf(stderr, "Error in equals function, A or B is null\n");
    }
    if (A == B)
    {
        return 1;
    }
    if (A->size != B->size)
    {
        return 0;
    }
    if (A->largest_row != B->largest_row)
    {
       // printf("Different longest Row\n");
        return 0;
    }
    for (int j = 0; j < A->largest_row; j++)
    {
       //printf("row = %d\n", j);
        List L1 = A->rows[j];
        List L2 = B->rows[j];
        moveFront(L1);
        moveFront(L2);
        int counter = 0;
        while(get(L1) != NULL && get(L2) != NULL){
           // printf("Counter: %d\n", counter);
            if(getCol(get(L1)) == getCol(get(L2))){
                if(getVal(get(L1)) != getVal(get(L2))){
              //       printf("Same column, different value, row: %d\n", j);
                    return 0;
                }
                //else
                moveNext(L1);
                moveNext(L2);
            }
            else if(getCol(get(L1)) < getCol(get(L2))){
                if(getVal(get(L1)) == 0){
                    
                      moveNext(L1);
                }else{
              //       printf("Excess entry in A, row: %d\n", j);
                    return 0;
                }
            }
             else if(getCol(get(L1)) > getCol(get(L2))){
                 if(getVal(get(L2)) == 0){
                      moveNext(L2);
                }
                else{
               //     printf("Excess entry in B, row: %d\n", j);
                    return 0;
                }
             }
             counter++;
        } 
        if(get(L2) == NULL){
           // printf("cursor in l2 is null\n");
        }
        if(get(L1) == NULL && get(L2) == NULL){
          //Both equal one
        }else if(get(L1) == NULL){
            while(get(L2) != NULL){
                if(getVal(get(L2)) != 0){
               //     printf("Non zero extra in L2\n");
                    return 0;
                }
                moveNext(L2);
            }
        }else if(get(L2) == NULL){
            while(get(L1) != NULL){
                if(getVal(get(L1)) != 0){
               //     printf("Non zero extra in L1\n");
                    return 0;
                }
                moveNext(L1);
            }
        }
    }
    return 1;
}



// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M)
{
    if (M == NULL)
    {
        fprintf(stderr, "Error in makeZero function M is null\n");
    }
    for (int i = 1; i <= M->largest_row; i++)
    {
        //freeList(M->rows[i - 1]);
        M->rows[i - 1] = newList();//This line is new, I am trying to reset it
    }
    M->largest_row = 0;
}



List addLists(List A, List B)
{
    if (A == NULL || B == NULL)
    {
        return NULL;
    }
    if (length(A) == 0)
    {
        return copyList(B);
    }
    if (length(B) == 0)
    {
        return copyList(A);
    }
    List C = newList();
    moveFront(A);
    //printf("A loop\n");
    for (int i = 0; i < length(A); i++)
    {
        moveFront(B);
        int inserted = 0;
        for (int j = 0; j < length(B); j++)
        {
            //printf("i = %d | j = %d\n", i, j);
            if (getCol(get(B)) == getCol(get(A)))
            {
                append(C, newEntry(getCol(get(B)), getVal(get(B)) + getVal(get(A))));
                inserted = 1;
            }
            moveNext(B);
        }
        if (inserted == 0)
        {
            append(C, newEntry(getCol(get(A)), getVal(get(A))));
        }
        moveNext(A);
    }
    //printf("B loop\n");
    moveFront(B);
    for (int i = 0; i < length(B); i++)
    {
        moveFront(A);
        int inserted = 0;
        for (int j = 0; j < length(A); j++)
        {
            //printf("i = %d | j = %d\n", i, j);
            if (getCol(get(A)) == getCol(get(B)))
            {
                insertInOrder(C, newEntry(getCol(get(A)), getVal(get(A)) + getVal(get(B))));
                inserted = 1;
            }
            moveNext(A);
        }
        if (inserted == 0)
        {
            insertInOrder(C, newEntry(getCol(get(B)), getVal(get(B))));
        }
        moveNext(B);
    }
    //printf("Finnished addList function");
    return C;
}

List subLists(List A, List B)
{
    if (A == NULL || B == NULL)
    {
        return NULL;
    }
    if (length(A) == 0)
    {
        return copyList(B);
    }
    if (length(B) == 0)
    {
        return copyList(A);
    }
    
    List C = newList();
    moveFront(A);
    
    for (int i = 0; i < length(A); i++)
    {
        moveFront(B);
        int inserted = 0;
        for (int j = 0; j < length(B); j++)
        {
            
            if (getCol(get(B)) == getCol(get(A)))
            {
                append(C, newEntry(getCol(get(B)), getVal(get(A)) - getVal(get(B))));
                inserted = 1;
            }
            moveNext(B);
        }
        if (inserted == 0)
        {
            append(C, newEntry(getCol(get(A)), getVal(get(A))));
        }
        moveNext(A);
    }
    
    moveFront(B);
    for (int i = 0; i < length(B); i++)
    {
        moveFront(A);
        int inserted = 0;
        for (int j = 0; j < length(A); j++)
        {
            //printf("i = %d | j = %d\n", i, j);
            if (getCol(get(A)) == getCol(get(B)))
            {
                insertInOrder(C, newEntry(getCol(get(A)), getVal(get(A)) - getVal(get(B))));
                inserted = 1;
            }
            moveNext(A);
        }
        if (inserted == 0)
        {
            insertInOrder(C, newEntry(getCol(get(B)), getVal(get(B))));
        }
        moveNext(B);
    }
    return C;
}

int largestRow(Matrix A)
{
    return A->largest_row;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x)
{
    //printf("value in changeEntry %.1f\n", x);
    if (M == NULL)
    {
        fprintf(stderr, "Error: in changeEntry, matrix is NULL\n");
        return;
    }
    int n = M->size;
    if (j > n || j < 1)
    {
        fprintf(stderr, "Error: in changeEntry, j does not fit in matrix. j = %d\n", j);
        return;
    }
    if (i > n || i < 1)
    {
        fprintf(stderr, "Error: in changeEntry, i does not fit in matrix. i = %d\n", i);
        return;
    }
    if (n == 0)
    {
        fprintf(stderr, "Error: in changeEntry, Matrix size 0\n");
        return;
    }
    Entry e = newEntry(j - 1, x);
    if (i > M->largest_row)
    {
        M->largest_row = i;
    }
    insertInOrder(M->rows[i - 1], e);
    
}

Entry editEntry(Entry e, double newValue)
{
    e->value = newValue;
    return e;
}
// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object  having the same entries as A
Matrix copy(Matrix A)
{
    if (A == NULL)
    {
        fprintf(stderr, "Error in size function, Matrix A is null\n");
        return NULL;
    }
    //printf("Begining to copy matrix\n");
    Matrix B = newMatrix(A->size);
    for (int i = 1; i <= A->largest_row; i++)
    {
        List L1 = A->rows[i - 1];
        moveFront(L1);
        for (int j = 1; j <= length(L1); j++)
        {
            // printf("Changing i = %d | j = %d\n", i , j);
            changeEntry(B, i, getCol(get(L1))+1, getVal(get(L1)));
            moveNext(L1);
        }
        moveFront(L1);
    }
    return B;
}
//  spose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A)
{
    if (A == NULL)
    {
        fprintf(stderr, "Error in transpose function, A is null\n");
        return NULL;
    }
    int n = A->size;
    Matrix B = newMatrix(n);
    for (int i = 0; i < A->largest_row; i++)
    {
        List L = A->rows[i];
        moveFront(L);
        if (B->largest_row < length(L))
        {
            B->largest_row = length(L);
        }
        for (int j = 0; j < length(L); j++)
        {
            // printf("adding in - %d\n", (getCol(get(L)) + 1));
            changeEntry(B, (getCol(get(L))) + 1, i + 1, getVal(get(L)));
            moveNext(L);
        }
    }
    return B;
}
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A)
{
    if (A == NULL)
    {
        fprintf(stderr, "Error in scalarMult function, A is null\n");
        return NULL;
    }
    int n = A->size;
    Matrix B = newMatrix(n);
    for (int i = 1; i <= A->largest_row; i++)
    {
        List L = A->rows[i - 1];
        moveFront(L);
        for (int j = 1; j <= length(L); j++)
        {
            double enter = x * getVal(get(L));
            //printf("%.1f\n", enter);
            changeEntry(B, i, getCol(get(L))+1, enter);
            //printf("i = %d | j = %d\n", i, j);
            moveNext(L);
        }
    }
    return B;
}

int maxOf(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

void fillZeros(Matrix A, Matrix B)
{
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B)
{
    if (A == NULL || B == NULL)
    {
        fprintf(stderr, "Error in sum function. A or B is(are) null\n");
        return NULL;
    }
    if (A->size != B->size)
    {
        fprintf(stderr, "Error in sum function. A and B are different sizes\n");
        return NULL;
    }
    if (A == B)
    {
        //printf("They are the same\n");
        return scalarMult(2, A);
    }
    Matrix C = newMatrix(A->size);
    C->largest_row = maxOf(A->largest_row, B->largest_row);
    for (int i = 0; i < C->largest_row; i++)
    {
        C->rows[i] = addLists(A->rows[i], B->rows[i]);
    }
    return C;
}
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B)
{
    if (A == NULL || B == NULL)
    {
        fprintf(stderr, "Error in sum function. A or B is(are) null\n");
        return NULL;
    }
    if (A->size != B->size)
    {
        fprintf(stderr, "Error in sum function. A and B are different sizes\n");
        return NULL;
    }
    if (A == B)
    {
        Matrix C = newMatrix(A->size);
        for(int i = 0; i < A->largest_row; i++){
            List L = A->rows[i];
            moveFront(L);
            while(get(L) != NULL){
                changeEntry(C, i+1, getCol(get(L))+1, 0);
                moveNext(L);
            }
        }
        return C;
    }
    Matrix C = newMatrix(A->size);
    C->largest_row = maxOf(A->largest_row, B->largest_row);
    for (int i = 0; i < C->largest_row; i++)
    {
        C->rows[i] = subLists(A->rows[i], B->rows[i]);
    }
    return C;
}

//Dot product between two rows
double dotProduct(Matrix M1, Matrix M2, int r1, int r2)
{
    List L1 = M1->rows[r1];
    List L2 = M2->rows[r2];
    if (L1 == NULL || L2 == NULL)
    {
        return 0.0;
    }
    double total = 0;
    moveFront(L1);
    moveFront(L2);
    //printf("Starting loop\n");

    while (get(L1) != NULL && get(L2) != NULL)
    {
        int a = getCol(get(L1));
        int b = getCol(get(L2));
        //printf("a = %d | b = %d\n", a,b);
        if (a == b)
        {
            total += getVal(get(L1)) * getVal(get(L2));
            moveNext(L2);
            moveNext(L1);
        }
        else if (a > b)
        {
            moveNext(L2);
        }
        else if (a < b)
        {
            moveNext(L1);
        }
    }

    return total;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B)
{
    if (A == NULL || B == NULL)
    {
        fprintf(stderr, "Error in sum function. A or B is(are) null\n");
        return NULL;
    }
    Matrix C = transpose(B); //What we will multiply by
    int n = A->size;
    Matrix D = newMatrix(n);
    for (int i = 0; i < A->largest_row; i++)
    {
        
        List L1 = A->rows[i];
        
        if(length(L1) != 0){
            for (int j = 0; j < C->largest_row; j++)
            {
                List L2 = C->rows[j];
                 if(length(L2) != 0){
                    double x =  dotProduct(A, C, i, j);
                    //printf("i = %d | j = %d | value = %.1f\n", i, j, x);
                    changeEntry(D, i + 1, j + 1, x);
                 }
            }
        }
    }
    //printf("Finnished product\n");
    return D;
}

double getVal(Entry e)
{
    if(e == NULL){
        printf("Errr, entry is null in getVal\n");
        return 0;
    }
    return e->value;
}

int getCol(Entry e)
{
    if(e == NULL){
        printf("Errr, entry is null in getCol\n");
        return 0;
    }
    return e->column;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE *out, Matrix M)
{
    if (M == NULL)
    {
        return;
    }
    //fprintf(out, "\n");
    for (int i = 0; i < M->largest_row; i++)
    {
        List L = M->rows[i];
        if (length(L) != 0)
        {
            //printf("length: %d\n", length(L));
            if (NNZ_row(M, i) != 0)
            {
                int k = i + 1;
                fprintf(out, "%d: ", k);
            }
            moveFront(L);
            // while(index(L) < length(L)-1){
            for (int j = 0; j < length(L); j++)
            {
                if (L->cursor_pos == -1)
                {
                    return;
                }
                 //fprintf(out, "(%d, %.1f) ", getCol(get(L)) + 1, getVal(get(L)));
                if (getVal(get(L)) != 0)
                {
                    fprintf(out, "(%d, %.1f) ", getCol(get(L)) + 1, getVal(get(L)));
                }
                moveNext(L);
            }
            if (NNZ_row(M, i) != 0)
            {
                fprintf(out, "\n");
            }
        }
    }
}