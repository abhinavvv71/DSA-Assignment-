/**
 * Assignment: Data Structures and Algorithms
 * Question 2: Circular Queue Implementation using Array (C)
 * 
 * Features:
 *  - Circular array queue without built-in queue libraries
 *  - ENQUEUE(x) with Queue Overflow handling
 *  - DEQUEUE() with Queue Underflow handling
 *  - FRONT() / Peek
 *  - DISPLAY() with circular traversal and slot-mapping visualization
 *  - Distinct state checks for Empty vs Full
 *  - Interactive menu-driven console interface
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_CAPACITY 5

typedef struct {
    int items[QUEUE_CAPACITY];
    int front;
    int rear;
} CircularQueue;

/**
 * Initializes the circular queue.
 * front and rear are both set to -1, indicating an empty queue.
 */
void initQueue(CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}

/**
 * Checks if the circular queue is empty.
 * Returns true if front == -1.
 */
bool isEmpty(const CircularQueue *q) {
    return (q->front == -1);
}

/**
 * Checks if the circular queue is full.
 * In a circular array of size N, the queue is full when the next position
 * of rear ((rear + 1) % N) wraps around and meets front.
 */
bool isFull(const CircularQueue *q) {
    return ((q->rear + 1) % QUEUE_CAPACITY == q->front);
}

/**
 * Computes the current number of elements in the queue.
 */
int getQueueSize(const CircularQueue *q) {
    if (isEmpty(q)) {
        return 0;
    }
    if (q->rear >= q->front) {
        return (q->rear - q->front + 1);
    }
    return (QUEUE_CAPACITY - (q->front - q->rear - 1));
}

/**
 * ENQUEUE(x): Inserts an element at the rear of the circular queue.
 * Handles Queue Overflow condition.
 * 
 * Time Complexity:  O(1)
 * Space Complexity: O(1) auxiliary
 */
bool enqueue(CircularQueue *q, int value) {
    if (isFull(q)) {
        printf("\n[ERROR] Queue Overflow! Cannot enqueue %d. Queue is currently full.\n", value);
        printf("        Capacity: %d, Front Index: %d, Rear Index: %d\n", 
               QUEUE_CAPACITY, q->front, q->rear);
        return false;
    }

    if (isEmpty(q)) {
        // First element being added
        q->front = 0;
        q->rear = 0;
    } else {
        // Circularly advance rear
        q->rear = (q->rear + 1) % QUEUE_CAPACITY;
    }

    q->items[q->rear] = value;
    printf("\n[SUCCESS] Enqueued %d at index [%d]. (Front: %d, Rear: %d, Count: %d/%d)\n",
           value, q->rear, q->front, q->rear, getQueueSize(q), QUEUE_CAPACITY);
    return true;
}

/**
 * DEQUEUE(): Removes and returns the front element from the circular queue.
 * Handles Queue Underflow condition.
 * 
 * Time Complexity:  O(1)
 * Space Complexity: O(1) auxiliary
 */
bool dequeue(CircularQueue *q, int *dequeuedValue) {
    if (isEmpty(q)) {
        printf("\n[ERROR] Queue Underflow! Cannot dequeue from an empty queue.\n");
        return false;
    }

    *dequeuedValue = q->items[q->front];
    printf("\n[SUCCESS] Dequeued %d from index [%d].\n", *dequeuedValue, q->front);

    if (q->front == q->rear) {
        // Queue had only one element; reset to empty state
        q->front = -1;
        q->rear = -1;
        printf("[INFO] Queue is now completely empty. front and rear reset to -1.\n");
    } else {
        // Circularly advance front
        q->front = (q->front + 1) % QUEUE_CAPACITY;
        printf("[INFO] New front index: %d, Rear index: %d (Remaining elements: %d)\n",
               q->front, q->rear, getQueueSize(q));
    }

    return true;
}

/**
 * FRONT(): Returns the front element without removing it.
 * 
 * Time Complexity:  O(1)
 * Space Complexity: O(1) auxiliary
 */
bool getFront(const CircularQueue *q, int *frontValue) {
    if (isEmpty(q)) {
        printf("\n[NOTICE] Queue is empty! No front element available.\n");
        return false;
    }

    *frontValue = q->items[q->front];
    printf("\n[INFO] Front element is: %d at index [%d].\n", *frontValue, q->front);
    return true;
}

/**
 * DISPLAY(): Displays all elements currently stored in the circular queue,
 * along with raw array indices to illustrate circular wrap-around.
 * 
 * Time Complexity:  O(N) where N is current count of elements
 * Space Complexity: O(1) auxiliary
 */
void display(const CircularQueue *q) {
    if (isEmpty(q)) {
        printf("\n[INFO] Queue is empty: [ ]\n");
        return;
    }

    printf("\n--- Circular Queue State (Capacity: %d, Occupied: %d) ---\n",
           QUEUE_CAPACITY, getQueueSize(q));
    printf("Logical Order\tArray Index\tValue\tRole\n");
    printf("--------------------------------------------------------\n");

    int i = q->front;
    int order = 1;
    while (true) {
        const char *role = "";
        if (i == q->front && i == q->rear) {
            role = "<-- FRONT & REAR";
        } else if (i == q->front) {
            role = "<-- FRONT";
        } else if (i == q->rear) {
            role = "<-- REAR";
        }

        printf("  #%d          \t[%d]        \t%d   \t%s\n", order, i, q->items[i], role);

        if (i == q->rear) {
            break;
        }
        i = (i + 1) % QUEUE_CAPACITY;
        order++;
    }
    printf("--------------------------------------------------------\n");

    // Display memory layout visualization
    printf("Array Memory Slots [0..%d]:\n[", QUEUE_CAPACITY - 1);
    for (int k = 0; k < QUEUE_CAPACITY; k++) {
        bool occupied = false;
        if (!isEmpty(q)) {
            if (q->front <= q->rear) {
                occupied = (k >= q->front && k <= q->rear);
            } else {
                occupied = (k >= q->front || k <= q->rear);
            }
        }
        if (occupied) {
            printf(" %d ", q->items[k]);
        } else {
            printf(" _ ");
        }
        if (k < QUEUE_CAPACITY - 1) printf("|");
    }
    printf("]\n");
}

/**
 * Clears standard input buffer.
 */
static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void) {
    CircularQueue q;
    initQueue(&q);

    int choice, value, dequeuedVal, frontVal;

    printf("=========================================================\n");
    printf("   DSA ASSIGNMENT - Q2: CIRCULAR QUEUE USING ARRAY (C)   \n");
    printf("   Queue Capacity: %d                                    \n", QUEUE_CAPACITY);
    printf("=========================================================\n");

    while (1) {
        printf("\n---------------- CIRCULAR QUEUE MENU ----------------\n");
        printf(" 1. ENQUEUE(x)  - Insert element into queue\n");
        printf(" 2. DEQUEUE()   - Remove element from queue\n");
        printf(" 3. FRONT()     - View front element\n");
        printf(" 4. DISPLAY()   - Display elements & memory layout\n");
        printf(" 5. CHECK STATUS (isEmpty / isFull / Front / Rear)\n");
        printf(" 6. EXIT\n");
        printf("-----------------------------------------------------\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1) {
            printf("\n[ERROR] Invalid input. Please enter a number between 1 and 6.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter integer value to enqueue: ");
                if (scanf("%d", &value) != 1) {
                    printf("\n[ERROR] Invalid input. Integer required.\n");
                    clearInputBuffer();
                } else {
                    enqueue(&q, value);
                }
                break;

            case 2:
                dequeue(&q, &dequeuedVal);
                break;

            case 3:
                getFront(&q, &frontVal);
                break;

            case 4:
                display(&q);
                break;

            case 5:
                printf("\n--- Circular Queue Status ---\n");
                printf("Is Empty: %s\n", isEmpty(&q) ? "YES" : "NO");
                printf("Is Full : %s\n", isFull(&q) ? "YES" : "NO");
                printf("Front Index: %d\n", q.front);
                printf("Rear  Index: %d\n", q.rear);
                printf("Current Count: %d / %d\n", getQueueSize(&q), QUEUE_CAPACITY);
                break;

            case 6:
                printf("\nExiting Circular Queue Program. Goodbye!\n");
                exit(0);

            default:
                printf("\n[ERROR] Invalid option! Please select between 1 and 6.\n");
                break;
        }
    }

    return 0;
}
