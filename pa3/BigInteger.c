/**
BigInteger.c
Jake Armendariz
jsarmend
pa4
This contains the functions and routines to multiply extremly large integers
using a linked list of longs it can provide long massive calculations in very little time
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "List.h"
#include "BigInteger.h"
#include <math.h>
// Exported type -------------------------------------------------------------
// BigInteger reference type
typedef struct BigIntegerObj
{
    List values; //Array of values
    int base;
    int power;
    int sign;
    long length;
} BigIntegerObj;

//Basic power function, got errors on the server using math.pow
int powerTo(int n, int a){
    int total = 1;
    for(int i = 0; i < a; i++){
        total *= n;
    }
    return total;
}
//typedef struct BigIntegerObj *BigInteger;
// Constructors-Destructors ---------------------------------------------------
// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger()
{
    BigInteger a = malloc(sizeof(BigIntegerObj));
    a->values = newList();
    a->power = 9;
    a->base = powerTo(10, a->power);
    a->sign = 0;
    a->length = 0;
    return a;
}

//Useless
void setPower(BigInteger N, int power)
{
    N->power = power;
    N->base = powerTo(10, N->power);
}
// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger *pN)
{
    List L = (*pN)->values;
    freeList(&L);
    free(*pN);
    *pN = NULL;
}
// Access functions -----------------------------------------------------------
// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N)
{
    return N->sign;
}
// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B)
{
    if (A == NULL || B == NULL)
    {
        fprintf(stderr, "Error in equals function, null obj\n");
    }
    if(A == B){
        //printf("A == B\n");
        return 0;
    }
      if (A->sign < B->sign)
    {
        //printf("A is negative\n");
        return -1;
    }
    if (A->sign > B->sign)
    {
         //printf("B is negative\n");
        return 1;
    }
    if (A->length < B->length)
    {
        //printf("B is longer\n");
        //return -1;
    }
    if (A->length > B->length)
    {
        //printf("A is longer\n");
       // return 1;
    }
    if (equals(A, B))
    {
        //printf("A.equalsB");
        return 0;
    }
    List L1 = A->values;
    List L2 = B->values;
    if(length(L1) > length(L2)){
        //printf("L1 is smaller\n");
        return 1;
    }else if(length(L1) > length(L2)){
        //printf("L2 is smaller\n");
        return -1;
    }
    moveFront(L1);
    moveFront(L2);
    if (length(L1) != length(L2))
    {
        //return 0;
    }
    while (index(L1) != -1)
    {
        if (get(L1) > get(L2))
        {
            return 1;
        }
        else if (get(L1) < get(L2))
        {
            return -1;
        }
        moveNext(L1);
        moveNext(L2);
    }
    //printf("End of compare method, should never be here\n");
    return 0;
}
// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B)
{
    if (A == NULL || B == NULL)
    {
        fprintf(stderr, "Error in equals function, null obj\n");
    }
    if (A->length != B->length)
    {
        //return 0;
    }

    if (A->sign != B->sign)
    {
        return 0;
    }
    List L1 = A->values;
    List L2 = B->values;
    moveFront(L1);
    moveFront(L2);
    if (length(L1) != length(L2))
    {
        return 0;
    }
    while (index(L1) != -1)
    {
        if (get(L1) != get(L2))
        {
            return 0;
        }
        moveNext(L1);
        moveNext(L2);
    }
    return 1;
}
// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N)
{
    freeList(&(N->values));
    N->values = newList();
    N->sign = 0;
    N->length = 0;
}
// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N)
{
    N->sign *= -1;
}
// BigInteger Arithmetic operations -----------------------------------------------
// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char *s)
{
    BigInteger a = newBigInteger();
    long beginsAt = 0;

    if (s[0] == '-')
    {
        a->sign = -1;
        beginsAt = 1;
    }
    else if (s[0] == '+')
    {
        a->sign = 1;
        beginsAt = 1;
    }else{
        a->sign = 1;
    }

    for (long i = strlen(s) - 1; i >= beginsAt;)
    {
        //long til = i - a->power;
        long num = 0;
        for (long j = 0; j < a->power; j++)
        {
            long temp = (long)s[i] - 48;
            //printf("%ld", temp);
            num += (long)powerTo(10, j) * temp;
            a->length++;
            i--;
            if (i < beginsAt)
            {
                //printf("length is not divisible by power\n");
                break;
            }
        }
        prepend(a->values, num);
    }
    //a->length -= trimFront(a->values);
    //printf("\n");
    return a;
}
// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N)
{
    if (N == NULL)
    {
        return NULL;
    }
    BigInteger a = newBigInteger();
    a->values = copyList(N->values);
    a->base = N->base;
    a->power = N->power;
    a->sign = N->sign;
    a->length = N->length;
    return a;
}

//Returns the number of digits in this long
long numberofdigits(long a)
{
    if (a == 0)
    {
        return 1;
    }
    long counter = 0;
    if (a < 0)
    {
        a *= -1;
    }
    while (a > 0)
    {
        a /= 10;
        counter++;
    }
    return counter;
}

//Returns the max integer of the two
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
// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B)
{
    BigInteger temp = sum(A, B);
    S->sign = temp->sign;
    S->length = temp->length;
    freeList(&(S->values));
    S->values = copyList(temp->values);
    freeBigInteger(&temp);
}
// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B)
{
    List L = newList();
    List L1 = A->values;
    List L2 = B->values;
    int mult = 1;
    if (A->sign == B->sign && A->sign == -1)
    { //If both are negative we multiply the result by a negative number
        mult = -1;
    }
    else if (A->sign == -1)
    {
        //printf("In sum: A is negative | B is positive. Subtracting B-A\n");
        A->sign = 1;
        BigInteger C = diff(B, A);
        A->sign = -1;
        return C;
    }
    else if (B->sign == -1)
    {
        //printf("In sum: B is negative | A is positive. Subtracting B-A\n");
        B->sign = 1;
        BigInteger C = diff(A, B);
        B->sign = -1;
        return C;
    }
    long carry = 0;
    long length = 0;
    moveBack(L1);
    moveBack(L2);
    while (index(L1) != -1 || index(L2) != -1)
    {
        long add = get(L1) + get(L2) + carry;
        if (add >= A->base)
        {
            carry = 1;
            add -= A->base;
        }
        else
        {
            carry = 0;
        }
        length += numberofdigits(add);
        prepend(L, add);
        movePrev(L1);
        movePrev(L2);
    }
    if (carry == 1)
    {
        length++;
        prepend(L, carry);
    }
    BigInteger big = newBigInteger();
    big->values = L;
    big->base = A->base;
    big->power = A->power;
    big->sign = mult;
    big->length = A->length;
    return big;
}
// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B)
{
    BigInteger temp = diff(A, B);
    D->sign = temp->sign;
    D->length = temp->length;
    freeList(&(D->values));
    D->values = copyList(temp->values);
    freeBigInteger(&temp);
}
// diff()
// Returns a reference to a new BigInteger object representing A - B.
//I am assuming its a positive - positive
//-Big +small
//small - Big
BigInteger diff(BigInteger A, BigInteger B)
{
    List L = newList();
    int i = compare(A, B);
    //int i = 1;
    int mult = 1; // If B > A then we will mult by -1
    List L1;
    List L2;
    //printf("Compare: %d\n", i);
    if (i == 1)
    {
        L1 = A->values;
        L2 = B->values;
    }
    else if (i == 0)
    {
        return newBigInteger();
    }
    else
    {
        //printf("B>A\n");
        L1 = B->values;
        L2 = A->values;
        mult = -1;
    }
    if (A->sign == -1 && A->sign == B->sign)
    {
        //printf("Both are negative\n");
        A->sign = 1;
        B->sign = 1;
        BigInteger C = diff(B, A);
        A->sign = -1;
        B->sign = -1;
        if(i == -1){
            C->sign = -1;
        }
        return C;
    }
    else if (A->sign == -1 && B->sign == 1)
    { //If only A is negative, then add a negative version of B
        //printf("In diff: A is negative | B is positive. Adding them and flipping sign\n");
        A->sign = 1;
        BigInteger C = sum(A, B);
        A->sign = -1;
        C->sign = -1;
        return C;
    }
    else if (B->sign == -1)
    {
        //printf("In diff: A is positive | B is negative. Adding a positive version of B to A\n");
        B->sign = 1;
        BigInteger C = sum(A, B);
        B->sign = -1;
        return C;
    }
   
    long carry = 0;
    long length = 0;
    moveBack(L1);
    moveBack(L2);
    while (index(L1) != -1 || index(L2) != -1)
    {
        long add = get(L1) - get(L2) + carry;
        //printf("add: %ld\n", add);
        carry = 0;

        while (add < 0)
        {
            carry--;
            add += powerTo(10, A->power);
        }
       
        length += numberofdigits(add);
        prepend(L, add);
        movePrev(L1);
        movePrev(L2);
    }
    BigInteger big = newBigInteger();
    big->sign = mult;
    big->values = L;
    big->base = A->base;
    big->power = A->power;
    big->length = length;
    return big;
}

/*
Multiplies A by the base by adding 0s to the back of the list
*/
void MultiplyByBase(BigInteger A)
{
    A->length += A->base;
    append(A->values, 0);
}

/**
 * Multiples A by a constant values
 */
BigInteger MultiplyByConstant(BigInteger A, long c)
{
    BigInteger B = newBigInteger();
    append(B->values, c);
    B->length = 1;
    B->sign = 1;
    BigInteger C = prod(A, B);
    //printf("Scalar times BigInteger\n");
    //printBigInteger(stdout, C);
    freeBigInteger(&B);
    return C;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B)
{
    BigInteger temp = prod(A, B);
    P->sign = temp->sign;
    P->length = temp->length;
    freeList(&(P->values));
    P->values = copyList(temp->values);
    freeBigInteger(&temp);
}
// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B)
{
    List L = newList();
    List L1 = A->values;
    List L2 = B->values;
    if(L1 == L2){
        L2 = copyList(B->values);
    }
    BigInteger C = newBigInteger();
    BigInteger temp = newBigInteger();
    moveBack(L1);

    int length = 0;
    BigInteger big = newBigInteger();
    //printf("product function\n");
    long carry = 0;
    int ind = 0;
    /*
    Main traversal, over the two lists of numbers, multiplies each long indiviudally and adding it to correct section in the product function
    */
    while (index(L1) != -1)
    {
        moveBack(L2);
        prepend(L, 0);
        moveBack(L);
        while (index(L2) != -1)
        {
            long whole = get(L1) * get(L2);
            long large, small;
            if (whole == 0)
            {
                large = 0;
                small = 0;
            }
            else
            {
                large = whole / A->base;
                if (large != 0)
                {
                    small = whole % (large * A->base);
                }
                else
                {
                    small = whole;
                }
            }
            movePrev(L2);
            set(L, small + carry);
            prepend(L, large);
            movePrev(L);
            carry = large;
            //printf("whole: %ld   large: %ld    small: %ld\n", whole, large, small);
            length += numberofdigits(small);
        }
        trimFront(L);
        //printf("Printing List:\n");
        //printList(stdout, L);
        carry = 0;
        movePrev(L1);
        freeList(&(temp->values));
        temp->values = copyList(L);
        temp->length = length;
        freeList(&L);
        L = newList();
        for (int i = 0; i < ind; i++)
        {
            MultiplyByBase(temp);
        }
        ind++;
        trimFront(temp->values);     
        add(big, C, temp);
        freeList(&(C->values));
        trimFront(big->values);
        C->values = copyList(big->values);
    }
    freeBigInteger(&C);
    freeBigInteger(&temp);
    freeList(&L);
    big->sign = A->sign * B->sign;
    big->length = length;
    //printf("5\n");
    return big;
}
// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE *out, BigInteger N)
{
    // printf("Start of printInteger\n");
    trimFront(N->values);
    List L = N->values;
    moveFront(L);
    if (N->sign == -1)
    {
        fprintf(out, "-");
    }
    if (length(L) == 0)
    {
        fprintf(out, "0\n");
        return;
    }
    while (index(L) != -1)
    {
        //In case there are 0's before the digit in case of 508 when it is deliminated into a base 100 system
        int diff = numberofdigits(get(L)) - N->power;
        // printf("diff = %d\n", diff);
        while (diff < 0 && index(L) != 0)
        {
            fprintf(out, "0");
            diff++;
        }
        fprintf(out, "%ld", get(L));
        moveNext(L);
    }
    fprintf(out, "\n");
    //   printf("PrintBigInteger function is over\n");
}