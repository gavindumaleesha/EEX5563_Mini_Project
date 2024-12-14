#include <stdio.h>
#include <stdlib.h>

// array
int tree[2050], i, j, k;

// Function prototypes
void segmentalloc(int, int);
void makedivided(int);
void makefree(int);
void printing(int, int);
int place(int);
int power(int, int);

int main() {
    int totsize, req, ch;

    // Display program information
    printf("\nEEX5563_G.G.Maleesha_621437488\n");
    printf("\nBuddy Syetem Memory Allocation Syestem\n");

    // Input total size of memory
    printf("\nEnter total size of memory: ");
    scanf("%d", &totsize);

    for (;;) {
        // Display menu
        printf("\n1. Allocate a new into memory\n2. Remove job from memory\n3. Display buddy algorthm view (Tree View)\n4. Exit\nEnter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                // Allocate memory
                printf("\nMemory Allocation: ");
                printf("\nEnter size of job: ");
                scanf("%d", &req);
                segmentalloc(totsize, req);
                break;

            case 2:
                // Deallocate memory
                printf("\nMemory Deallocation: ");
                printf("\nEnter size of job to be removed: ");
                scanf("%d", &req);
                makefree(req);
                break;

            case 3:
                // Display the tree view of the buddy system
                printf("\nMemory Allocation Map: ");
                printing(totsize, 0);
                break;

            default:
                exit(0);
        }
    }
}

// Function to allocate memory to a job
void segmentalloc(int total, int req) {
    int size = total, flevel = 0;

    // Check if the requested size exceeds available memory
    if (req > size) {
        printf("\nSystem does not have enough memory! ");
        return;
    }

    // Determine the smallest block size that can accommodate the request
    while (1) {
        if (req <= size && req > size / 2) {
            break;
        } else {
            size = size / 2;
            flevel++;
        }
    }

    // Traverse the tree to find a suitable block
    for (int i = power(2, flevel) - 1; i <= power(2, flevel + 1) - 2; i++) {
        if (tree[i] == 0 && place(i)) {
            tree[i] = req;
            makedivided(i);
            printf("\nSuccessful allocation! ");
            break;
        }
    }

    if (i == power(2, flevel + 1) - 1) {
        printf("\nSystem does not have enough memory! ");
    }
}

// Function to check if a node can be allocated
int place(int node) {
    while (node != 0) {
        node = (node % 2 == 0) ? (node - 1) / 2 : node / 2;
        if (tree[node] > 1)
            return 0;
    }
    return 1;
}

// Function to mark parent nodes as divided
void makedivided(int node) {
    while (node != 0) {
        node = (node % 2 == 0) ? (node - 1) / 2 : node / 2;
        tree[node] = 1;
    }
}

// Function to deallocate memory for a job
void makefree(int req) {
    int node = 0;

    while (1) {
        if (tree[node] == req)
            break;
        else
            node++;
    }

    tree[node] = 0;
    while (node != 0) {
        if (tree[node] == 0 && tree[(node % 2 == 0) ? (node - 1) : node + 1] == 0) {
            tree[(node % 2 == 0) ? (node - 1) / 2 : node / 2] = 0;
            node = (node % 2 == 0) ? (node - 1) / 2 : node / 2;
        } else
            break;
    }
}

// Function to display the memory tree
void printing(int tot, int node) {
    if (node >= 2050)
        return;

    int perm = 0, limit = 0, ulimit = 0, tab = 0;
    if (node == 0)
        perm = 1;
    else if (node % 2 == 0)
        perm = tree[(node - 1) / 2] == 1 ? 1 : 0;
    else
        perm = tree[node / 2] == 1 ? 1 : 0;

    if (perm) {
        // Calculate level and block size
        limit = 0;
        ulimit = 0;
        tab = 0;

        while (1) {
            if (node >= limit && node <= ulimit)
                break;
            else {
                tab++;
                limit = ulimit + 1;
                ulimit = 2 * ulimit + 2;
            }
        }

        if (power(2, tab) == 0) {
            printf("\nError: Division by zero detected.\n");
            return;
        }

        // Print block information
        printf("%d", tot / power(2, tab));
        if (tree[node] > 1)
            printf("-->Allocated %d", tree[node]);
        else if (tree[node] == 1)
            printf("-->Divided");
        else
            printf("-->Free");

        printf("\n");

        // Recursively print child nodes
        printing(tot, 2 * node + 1);
        printing(tot, 2 * node + 2);
    }
}

// Function to calculate power of a number
int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}



// EEX5563 - Mini Project
// Buddy System Implementation
// Reg No - 621437488
// Name - G.G. Maleesha
