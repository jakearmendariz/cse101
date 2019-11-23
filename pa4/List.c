/**
 * List.c
 * 
 * Jake Armendariz
 * 
 *  Description:
 * Contains a doubly linked list manipulation routines
 * Can create new nodes, insert nodes to the list at the end of based off of values
 * Can delete singular nodes or the entire list
 */

#include "stdio.h"
#include "List.h"

typedef struct ListObj
{
    int length;
    int cursor_pos; //Position of cursor
    struct Node *cursor;
    struct Node *front; /* ptr to pos 0 */
    struct Node *back;  /* ptr to last position */
} ListObj;

/**
 * newList();
 * 
 * creates new list frees up memory and sets values to default
 */
List newList()
{
    List lst = malloc(sizeof(ListObj));
    lst->length = 0;
    lst->cursor_pos = -1;
    lst->cursor = NULL;
    lst->front = NULL;
    lst->back = NULL;
    return lst;
}

/**
 * newNode
 * 
 * creates a Node and allocates memory for it
 */
Node *newNode(int val)
{
    Node *a = malloc(sizeof(Node));
    a->value = val;
    a->prev = NULL;
    a->next = NULL;
    return a;
}

/**
 * freeList
 * 
 * free the list and sets pointers to NULL
 */
void freeList(List *pL)
{
    if (pL == NULL)
    {
        fprintf(stderr, "Error: pointer to list is null in freeList function parameter");
        return;
    }
    Node *a = (*pL)->front;
    for (int i = 0; i < (*pL)->length; i++)
    {
        Node *temp = a;
        a = a->next;
        free(temp);
    }
    free(*pL);
    pL = NULL;
}

/**
 * FreeNode
 * 
 * Frees the individual nodes in the list
 */
void freeNode(Node *a)
{
    if (a != NULL)
    {
        a->prev = NULL;
        a->next = NULL;
        free(a);
        a = NULL;
    }
}
// Access functions -----------------------------------------------------------
// Returns the number of elements in L.
int length(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is undefinded in length function\n");
    }
    return L->length;
}
//Position of cursor
int indexIt(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is undefinded in index() function\n");
        return -1;
    }
    if (L->cursor_pos == -1)
    {
        //fprintf(stderr, "Error: cursor_pos is -1 in index() function\n");
        return -1;
    }
    return L->cursor_pos;
}
//Returns value at front of list
int front(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is undefinded in front() function\n");
        return 0;
    }
    if (L->length > 0)
    {
        return L->front->value;
    }
    else
    {
        fprintf(stderr, "Error: List is empty in front() function\n");
        return 0;
    }
}
//Returns the value of back element
int back(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is undefinded in back() function\n");
        return 0;
    }
    if (L->length > 0)
    {
        return L->back->value;
    }
    else
    {
        fprintf(stderr, "Error: List is empty in back() function\n");
        return 0;
    }
}
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is undefinded in get() function\n");
        return 0;
    }
    if (L->length == 0)
    {
        //fprintf(stderr, "Error: List is empty in get() function\n");
        return 0;
    }
    if (L->cursor_pos == -1)
    {
        //fprintf(stderr, "Error: cursor is undefinded");
        return -1;
    }
    else if (L->length == 0)
    {
        fprintf(stderr, "Error: list is empty");
        return -1;
    }
    if (L->cursor == NULL)
    {
        fprintf(stderr, "Error: cursor is undefinded");
        return -1;
    }
    return L->cursor->value;
}

/**
 * equals
 * 
 * Checks if every element is the same
 */
int equals(List A, List B)
{
    if (A == NULL && B == NULL)
    {
        return 1;
    }
    else if (A == NULL)
    {
        return 0;
    }
    else if (B == NULL)
    {
        return 0;
    }
    else if (A->length != B->length)
    {
        return 0;
    }
    Node *a = A->front;
    Node *b = B->front;
    for (int i = 0; i < A->length; i++)
    {
        if (a->value != b->value)
        {
            return 0;
        }
        a = a->next;
        b = b->next;
    }
    return 1;

} // Returns true (1) iff Lists A and B are in same
  // state, and returns false (0) otherwise.
// Manipulation procedures ----------------------------------------------------
void clear(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is undefinded in clear() function\n");
        return;
    }
    L->cursor_pos = -1;
    L->cursor = NULL;
    L->front = NULL;
    L->back = NULL;
    L->length = 0;
} // Resets L to its original empty state.

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is NULL in moveFront function");
        return;
    }
    if (L->length == 0)
    {
        return;
    }
    L->cursor_pos = 0;
    L->cursor = L->front;
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is NULL in moveBack function");
        return;
    }
    if (L->length == 0)
    {
        return;
    }
    L->cursor_pos = L->length - 1;
    L->cursor = L->back;
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is NULL in movePrev function");
        return;
    }
    if (L->cursor_pos <= 0)
    {
        // printf("Cursor moved too far left: undefined\n");
        L->cursor_pos = -1;
        L->cursor = NULL;
        return;
    }
    if (L->cursor->prev == NULL && L->cursor_pos != 0)
    {
        //printf("Node previous is NULL: pos = %d\n", L->cursor_pos);
    }
    L->cursor_pos--;
    L->cursor = L->cursor->prev;
}

//Moves the cursor over by 1 to the right, increasing order
void moveNext(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is NULL in moveNext function");
        return;
    }
    if (L->cursor_pos >= L->length - 1)
    {
        // printf("Cursor moved too far right: undefined\n");
        L->cursor_pos = -1;
        L->cursor = NULL;
        return;
    }
    L->cursor_pos++;
    L->cursor = L->cursor->next;
}



void insertInOrder(List L, int data){
    if(length(L) == 0){
        append(L, data);
        return;
    }
  //  Node a = newNode(data);
    moveFront(L);
    while(get(L) != -1 && get(L) < data){
        moveNext(L);
    }
    if(get(L) == -1){
        append(L, data);
        return;
    }
    insertBefore(L, data);
}


/**
 * prepend
 * 
 * adds a new node: data into the list at the front position
 */
void prepend(List L, int data)
{
    //printf("In prepend\n");
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is Null in prepend parameter");
        return;
    }
    else if (L->length == 0)
    { //First element in list
        L->front = newNode(data);
        L->back = L->front;
    }
    else if (L->length == 1)
    {
        L->front = newNode(data);
        L->front->next = L->back;
        L->back->prev = L->front;
    }
    else
    {
        Node *temp = L->front;
        L->front = newNode(data);
        L->front->next = temp;
        temp->prev = L->front;
    }
    L->length++;
    if (L->cursor_pos != -1)
    {
        L->cursor_pos++;
    }
}

/**
 * append
 * 
 * adds a new node: data into the list at the back position
 */
void append(List L, int data)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is Null in prepend parameter");
        return;
    }
    else if (L->length == 0)
    { //First element in list
        //printf("attempting to append\n");
        L->front = newNode(data);
        L->back = L->front;
    }
    else if (L->length == 1)
    {
        L->back = newNode(data);
        L->front->next = L->back;
        L->back->prev = L->front;
    }
    else
    {
        Node *temp = L->back;
        Node *a = newNode(data);
        temp->next = a;
        a->prev = temp;
        L->back = a;
    }
    L->length++;
}

/**
 * insertBefores
 * 
 * Inserts a node before the cursor
 * If Null, empty or undefined ursor nothing happens
 */
void insertBefore(List L, int data)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is Null in insertBefore() parameter");
        return;
    }
    if (L->cursor_pos == -1)
    {
        fprintf(stderr, "Error: cursor is undefinded in insertBefore");
        return;
    }
    if (L->cursor == NULL)
    {
        fprintf(stderr, "Error: cursor is undefinded in insertBefore");
        return;
    }
    //If we can insert, create Node
    Node *insert = newNode(data);
    if (L->cursor_pos == 0 && L->length == 1)
    {
        Node *back = L->back;
        L->front = insert;
        insert->next = back;
        back->prev = insert;
        L->length++;
        return;
    }
    if (L->cursor_pos == 0)
    {
        L->front = insert;
        insert->next = L->cursor;
        L->cursor->prev = insert;
        L->cursor_pos++;
        L->length++;
        return;
    }
    Node *previ = L->cursor->prev;
    insert->prev = previ;
    previ->next = insert;
    insert->next = L->cursor;
    L->cursor->prev = insert;
    L->length++;
    L->cursor_pos++;
}

/**
 * insertAfter
 * 
 * Inserts a node after the cursor
 * If Null, empty or undefined ursor nothing happens
 */
void insertAfter(List L, int data)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is Null in insertAfter() parameter");
        return;
    }
    if (L->cursor == NULL)
    {
        // printf("Cursor is NULL in insertAfter function\n");
        return;
    }
    Node *insert = newNode(data);
    if (L->length <= 0)
    {
        fprintf(stderr, "Error: List is empty");
        return;
    }
    if (L->cursor_pos < 0)
    {
        fprintf(stderr, "Error: cursor is undefinded in insertAfter");
        return;
    }
    if (L->cursor_pos == 0 && L->length == 1)
    {
        Node *previ = L->front;
        L->back = insert;
        insert->prev = previ;
        previ->next = insert;
        L->length++;
        return;
    }
    if (L->cursor_pos == 0)
    {
        // printf("2\n");
        Node *post = L->cursor->next;
        L->cursor->next = insert;
        insert->prev = L->cursor;
        post->prev = insert;
        insert->next = post;
        L->length++;
        return;
    }
    if (L->cursor_pos == L->length - 1)
    { // End of the list

        L->cursor->next = insert;
        insert->prev = L->cursor;
        L->back = insert;
        L->length++;
        return;
    }

    Node *post = L->cursor->next;
    L->cursor->next = insert;
    insert->prev = L->cursor;
    insert->next = post;
    post->prev = insert;
    L->length++;
    return;
}
// Delete the front element. Pre: length()>0
//GOOOOOD
void deleteFront(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is Null in deleteFront() parameter");
        return;
    }
    if (L->length <= 0)
    {
        return;
    }
    if (L->cursor_pos == 0)
    {
        L->cursor_pos = -1;
        L->cursor = NULL;
    }
    if (L->length == 1)
    {
        freeNode(L->front);
        L->front = NULL;
        L->back = NULL;
        L->length = 0;
        return;
    }
    Node *temp = L->front;
    L->front = L->front->next;
    L->front->prev = NULL;
    freeNode(temp);
    L->length--;
    if (L->cursor_pos != -1)
    {
        L->cursor_pos--;
    }
}

// Delete the back element. Pre: length()>0
void deleteBack(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is Null in deleteBack() parameter");
        return;
    }
    if (L->length <= 0)
    {
        return;
    }
    if (L->cursor_pos == L->length - 1)
    {
        L->cursor_pos = -1;
        L->cursor = NULL;
    }
    if (L->length == 1)
    {
        clear(L);
        return;
    }
    Node *temp = L->back;
    L->back = L->back->prev;
    L->back->next = NULL;
    freeNode(temp);
    L->length--;
}

//Gives the value at a given position in the array
int valueAt(List L, int pos)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is Null in deleteBack() parameter\n");
        return 0;
    }
    if (L->length < pos)
    {
        fprintf(stderr, "Cannot find value of index in valueAt, list length is %d\n", L->length);
        return 0;
    }
    int curr = 0;
    Node *a = L->front;
    for (int i = 0; i < L->length; i++)
    {
        if (a == NULL)
        {
            //printf("Node is null inside list in valueAt function\n");
            return 0;
        }
        if (curr == pos)
        {
            return a->value;
        }
        a = a->next;
        curr++;
    }
    return -1;
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
// Other operations -----------------------------------------------------------
void delete (List L)
{
    //printf("deleteing %d\n", L->cursor->value);
    if (L == NULL)
    {
        fprintf(stderr, "Error: List is Null in deleteIt() parameter\n");
        return;
    }
    if (L->cursor == NULL)
    {
        return;
    }
    if (L->cursor_pos == L->length - 1)
    {
        deleteBack(L);
        return;
    }
    if (L->cursor_pos == 0)
    {
        deleteFront(L);
        return;
    }
    Node *previous = L->cursor->prev;
    Node *next_node = L->cursor->next;
    previous->next = next_node;
    next_node->prev = previous;
    L->cursor_pos = -1;
    L->length--;
    freeNode(L->cursor); //Sets cursor to NULL as well
}

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE *out, List L)
{
    Node *a = L->front;
    for (int i = 0; i < L->length; i++)
    {
        if (a != NULL)
        {
            Node *temp = a;
            a = a->next;
            fprintf(out, "%d", temp->value);
            if(a != NULL){
                 fprintf(out, " ");
            }
        }
    }
    //fprintf(out, "\n");
}
//print list reversed
void printListRev(FILE *out, List L)
{
    Node *a = L->back;
    for (int i = L->length - 1; i >= 0; i--)
    {
        Node *temp = a;
        a = a->prev;
        fprintf(out, "%d ", temp->value);
    }
    //fprintf(out, "\n");
}

//I think this is done
List copyList(List L)
{
    if (L == NULL)
    {
        return NULL;
    }
    List a = newList();
    a->length = L->length;
    if (L->length == 0)
    {
        return a;
    }
    Node *temp = L->front;
    a->front = newNode(temp->value);
    Node *aa = a->front;
    temp = temp->next;
    for (int i = 1; i < L->length; i++)
    {
        aa->next = newNode(temp->value);
        temp = temp->next;
        if (i < L->length - 1)
        {
            aa = aa->next;
        }
    }
    a->back = aa;
    return a;
}

// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B)
{
    if (A == NULL || B == NULL)
    {
        fprintf(stderr, "Error in concatList function, List provided is null\n");
        return NULL;
    }
    List C = newList();
    Node *current = A->front;
    for (int i = 0; i < A->length; i++)
    {
        append(C, current->value);
        current = current->next;
    }
    current = B->front;
    for (int i = 0; i < B->length; i++)
    {
        append(C, current->value);
        current = current->next;
    }
    return C;
}
