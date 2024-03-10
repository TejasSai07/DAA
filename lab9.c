#include <stdio.h>
#include <string.h>

#define MAX 256

void preprocessShiftTable(char *pattern, int patternLength, int shiftTable[MAX]) {
    int i;
    for (i = 0; i < MAX; i++)
        shiftTable[i] = patternLength;
    for (i = 0; i < patternLength - 1; i++)
        shiftTable[pattern[i]] = patternLength - 1 - i;
}

int horspoolStringSearch(char *text, int textLength, char *pattern, int patternLength, int *comparisons) {
    int shiftTable[MAX];
    preprocessShiftTable(pattern, patternLength, shiftTable);
    int i = patternLength - 1;
    while (i < textLength) {
        int k = 0;
        while (k < patternLength && pattern[patternLength - 1 - k] == text[i - k]) {
            k++;
            (*comparisons)++;
        }
        if (k == patternLength)
            return i - patternLength + 1; 
        else
            i += shiftTable[text[i]]; 
    }
    return -1; 
}

int main() {
    char text[] = "exampletextforexample";
    char pattern[] = "example";
    int textLength = strlen(text);
    int patternLength = strlen(pattern);
    int comparisons = 0;

    int position = horspoolStringSearch(text, textLength, pattern, patternLength, &comparisons);
    if (position != -1)
        printf("Pattern found at position: %d\n", position);
    else
        printf("Pattern not found\n");
    printf("Number of key comparisons: %d\n", comparisons);

    return 0;
}




---------

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node *table[SIZE];
} HashTable;

void initializeHashTable(HashTable *hashTable) {
    for (int i = 0; i < SIZE; i++)
        hashTable->table[i] = NULL;
}

int hashFunction(int key) {
    return key % SIZE;
}

void insertKey(HashTable *hashTable, int key) {
    int index = hashFunction(key);
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = key;
    newNode->next = NULL;
    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = newNode;
    } else {
        newNode->next = hashTable->table[index];
        hashTable->table[index] = newNode;
    }
}

Node *searchKey(HashTable *hashTable, int key) {
    int index = hashFunction(key);
    Node *current = hashTable->table[index];
    while (current != NULL) {
        if (current->data == key)
            return current;
        current = current->next;
    }
    return NULL;
}

int countKeyComparisons(HashTable *hashTable, int key, int *successfulComparisons, int *unsuccessfulComparisons) {
    Node *result = searchKey(hashTable, key);
    if (result != NULL)
        (*successfulComparisons)++;
    else
        (*unsuccessfulComparisons)++;
}

int main() {
    HashTable hashTable;
    initializeHashTable(&hashTable);

    insertKey(&hashTable, 5);
    insertKey(&hashTable, 15);
    insertKey(&hashTable, 25);

    int successfulComparisons = 0, unsuccessfulComparisons = 0;
    countKeyComparisons(&hashTable, 5, &successfulComparisons, &unsuccessfulComparisons);
    countKeyComparisons(&hashTable, 15, &successfulComparisons, &unsuccessfulComparisons);
    countKeyComparisons(&hashTable, 30, &successfulComparisons, &unsuccessfulComparisons);

    printf("Number of key comparisons for successful search: %d\n", successfulComparisons);
    printf("Number of key comparisons for unsuccessful search: %d\n", unsuccessfulComparisons);

    return 0;
}


-----

  #include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

typedef struct {
    int key;
    bool occupied;
} HashTableEntry;

void initializeHashTable(HashTableEntry *hashTable, int size) {
    for (int i = 0; i < size; i++) {
        hashTable[i].key = -1;
        hashTable[i].occupied = false;
    }
}

int hashFunction(int key) {
    return key % SIZE;
}

void insertKey(HashTableEntry *hashTable, int key) {
    int index = hashFunction(key);
    int i = 0;
    while (hashTable[(index + i) % SIZE].occupied) {
        i++;
    }
    hashTable[(index + i) % SIZE].key = key;
    hashTable[(index + i) % SIZE].occupied = true;
}

bool searchKey(HashTableEntry *hashTable, int key) {
    int index = hashFunction(key);
    int i = 0;
    while (hashTable[(index + i) % SIZE].occupied) {
        if (hashTable[(index + i) % SIZE].key == key)
            return true;
        i++;
    }
    return false;
}

int main() {
    HashTableEntry hashTable[SIZE];
    initializeHashTable(hashTable, SIZE);

    insertKey(hashTable, 5);
    insertKey(hashTable, 15);
    insertKey(hashTable, 25);

    printf("Key 5 found in the hash table: %s\n", searchKey(hashTable, 5) ? "Yes" : "No");
    printf("Key 15 found in the hash table: %s\n", searchKey(hashTable, 15) ? "Yes" : "No");
    printf("Key 30 found in the hash table: %s\n", searchKey(hashTable, 30) ? "Yes" : "No");

    return 0;
}

