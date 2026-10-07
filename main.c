/**
 * Assignment: Data Structures and Algorithms
 * Question 1: Stack Implementation using Array (C)
 * 
 * Features:
 *  - Fixed-size array stack without built-in stack libraries
 *  - PUSH(x) with Stack Overflow handling
 *  - POP() with Stack Underflow handling
 *  - PEEK()
 *  - DISPLAY()
 *  - Interactive menu-driven interface with input validation
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CAPACITY 5

typedef struct {
    int data[MAX_CAPACITY];
    int top;
} Stack;

/**
 * Initializes the stack.
 * Sets top to -1 indicating that the stack is empty.
 */
void initStack(Stack *s) {
    s->top = -1;
}

/**
 * Checks if the stack is empty.
 * Returns true if top == -1, false otherwise.
 */
bool isEmpty(const Stack *s) {
    return (s->top == -1);
}

/**
 * Checks if the stack is full.
 * Returns true if top == MAX_CAPACITY - 1, false otherwise.
 */
bool isFull(const Stack *s) {
    return (s->top == MAX_CAPACITY - 1);
}

/**
 * PUSH(x): Inserts an element on top of the stack.
 * Handles Stack Overflow condition.
 * 
 * Time Complexity:  O(1)
 * Space Complexity: O(1) auxiliary
 */
bool push(Stack *s, int value) {
    if (isFull(s)) {
        printf("\n[ERROR] Stack Overflow! Cannot push %d. Maximum capacity (%d) reached.\n", 
               value, MAX_CAPACITY);
        return false;
    }
    s->top++;
    s->data[s->top] = value;
    printf("\n[SUCCESS] Successfully pushed %d onto the stack. (Current size: %d/%d)\n", 
           value, s->top + 1, MAX_CAPACITY);
    return true;
}

/**
 * POP(): Removes and returns the top element of the stack.
 * Handles Stack Underflow condition.
 * 
 * Time Complexity:  O(1)
 * Space Complexity: O(1) auxiliary
 */
bool pop(Stack *s, int *poppedValue) {
    if (isEmpty(s)) {
        printf("\n[ERROR] Stack Underflow! Cannot pop from an empty stack.\n");
        return false;
    }
    *poppedValue = s->data[s->top];
    s->top--;
    printf("\n[SUCCESS] Successfully popped %d from the stack. (Remaining elements: %d)\n", 
           *poppedValue, s->top + 1);
    return true;
}

/**
 * PEEK(): Returns the top element without removing it.
 * Handles empty stack condition.
 * 
 * Time Complexity:  O(1)
 * Space Complexity: O(1) auxiliary
 */
bool peek(const Stack *s, int *topValue) {
    if (isEmpty(s)) {
        printf("\n[NOTICE] Stack is empty! No element to peek.\n");
        return false;
    }
    *topValue = s->data[s->top];
    printf("\n[INFO] Top element is: %d (Index: %d)\n", *topValue, s->top);
    return true;
}

/**
 * DISPLAY(): Prints all elements in the stack from top to bottom.
 * 
 * Time Complexity:  O(N) where N is the current number of elements
 * Space Complexity: O(1) auxiliary
 */
void display(const Stack *s) {
    if (isEmpty(s)) {
        printf("\n[INFO] Stack is empty: [ ]\n");
        return;
    }

    printf("\n--- Current Stack (Capacity: %d, Occupied: %d) ---\n", 
           MAX_CAPACITY, s->top + 1);
    printf("Position\tIndex\tValue\n");
    printf("----------------------------------------\n");
    for (int i = s->top; i >= 0; i--) {
        if (i == s->top) {
            printf("[TOP] -> \t[%d]\t%d\n", i, s->data[i]);
        } else {
            printf("         \t[%d]\t%d\n", i, s->data[i]);
        }
    }
    printf("----------------------------------------\n");
}

/**
 * Helper function to clear standard input buffer in case of invalid input.
 */
static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void) {
    Stack stack;
    initStack(&stack);

    int choice, value, poppedVal, topVal;

    printf("==================================================\n");
    printf("   DSA ASSIGNMENT - Q1: STACK USING ARRAY (C)     \n");
    printf("   Stack Capacity: %d                              \n", MAX_CAPACITY);
    printf("==================================================\n");

    while (1) {
        printf("\n------------- STACK OPERATIONS -------------\n");
        printf(" 1. PUSH(x)   - Insert element\n");
        printf(" 2. POP()     - Remove top element\n");
        printf(" 3. PEEK()    - View top element\n");
        printf(" 4. DISPLAY() - Display all elements\n");
        printf(" 5. CHECK STATUS (isEmpty / isFull / Size)\n");
        printf(" 6. EXIT\n");
        printf("--------------------------------------------\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1) {
            printf("\n[ERROR] Invalid input. Please enter a number between 1 and 6.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter integer value to push: ");
                if (scanf("%d", &value) != 1) {
                    printf("\n[ERROR] Invalid input. Integer required.\n");
                    clearInputBuffer();
                } else {
                    push(&stack, value);
                }
                break;

            case 2:
                pop(&stack, &poppedVal);
                break;

            case 3:
                peek(&stack, &topVal);
                break;

            case 4:
                display(&stack);
                break;

            case 5:
                printf("\n--- Stack Status ---\n");
                printf("Is Empty: %s\n", isEmpty(&stack) ? "YES" : "NO");
                printf("Is Full : %s\n", isFull(&stack) ? "YES" : "NO");
                printf("Current Size: %d / %d\n", stack.top + 1, MAX_CAPACITY);
                break;

            case 6:
                printf("\nExiting Stack Program. Goodbye!\n");
                exit(0);

            default:
                printf("\n[ERROR] Choice out of range. Please choose between 1 and 6.\n");
                break;
        }
    }

    return 0;
}
