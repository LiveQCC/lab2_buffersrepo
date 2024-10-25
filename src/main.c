#include <stdio.h>
#include <stdlib.h>
#include <esp32/rom/ets_sys.h>
#include "circular_buffer.h"

/*
 * SET BUFFER SIZE VALIE HERE
 */ 
#define BUFFER_SIZE 4
struct circularBuffer buffer;
/*
    addElement(&buffer, 1);
    addElement(&buffer,2);
    addElement(&buffer, 1);
    addElement(&buffer, 3);
    printBuffer(&buffer);
    removeHead(&buffer);
    printBuffer(&buffer);
    removeHead(&buffer);
    removeHead(&buffer);
    removeHead(&buffer);
*/
/*
    addElement(&buffer,1);
    printBuffer(&buffer);
    addElement(&buffer,2);
    printBuffer(&buffer);
    removeHead(&buffer);
    printBuffer(&buffer);
    removeHead(&buffer);
    printBuffer(&buffer);
*/
void test_addElement() {
    printf("Testing addElement...\n");
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);
    for(int i = 0; i < BUFFER_SIZE; i++) {
        addElement(&buffer, i);
    }
    // Expected: Buffer is full with elements 0, 1, 2, 3
    printBuffer(&buffer);
    free(buffer_data);
}

void test_removeHead() {
    printf("Testing removeHead...\n");
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);
    for(int i = 0; i < BUFFER_SIZE; i++) {
        addElement(&buffer, i);
    }
    removeHead(&buffer);
    // Expected: First element is removed, buffer contains 1, 2, 3
    printBuffer(&buffer);
    free(buffer_data);
}

void test_removeValue() {
    printf("Testing removeValue...\n");
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);
    addElement(&buffer, 2);
    addElement(&buffer, 0);
    addElement(&buffer, 1);
    addElement(&buffer, 2);
    printBuffer(&buffer);
    removeValue(&buffer, 2);
    // Expected: Element 2 is removed, buffer contains 0,1
    printBuffer(&buffer);
    free(buffer_data);
}

void test_contains() {
    printf("Testing contains...\n");
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);
    for(int i = 0; i < BUFFER_SIZE; i++) {
        addElement(&buffer, i);
    }
    int result = contains(&buffer, 3);
    printf("Contains 3: %d\n", result); // Expected: 3:3 (true)
    result = contains(&buffer, 5);
    printf("Contains 5: %d\n", result); // Expected: 5:INT_MIN (false)
    free(buffer_data);
}

void run_whitebox_tests() {
    test_addElement();
    test_removeHead();
    test_removeValue();
    test_contains();
}

void blackBoxTest_first() {
    int value = 5;
    addElement(&buffer, value);
    printBuffer(&buffer);
    removeHead(&buffer);
    printBuffer(&buffer);
}

void blackBoxTest_second() {
    int firstValue = 1, secondValue = 2;
    addElement(&buffer, firstValue);
    addElement(&buffer, secondValue);
    printBuffer(&buffer);
    removeHead(&buffer);
    printBuffer(&buffer);
    removeHead(&buffer);
    printBuffer(&buffer);
}

void blackBoxTest_third() {
    for(int i = 1; i < BUFFER_SIZE+1; i++) {
        addElement(&buffer, i);
        printBuffer(&buffer);
    }
    for(int i = 0; i < BUFFER_SIZE; i++) {
        removeHead(&buffer);
        printBuffer(&buffer);
    }
    printBuffer(&buffer);
}

void blackBoxTest_fourth() {
    for(int i = 0; i < BUFFER_SIZE + 1; i++) {
        int result = addElement(&buffer, i + 1);
        printBuffer(&buffer);
        printf("%d", result);
    }
    removeHead(&buffer);
    removeHead(&buffer);
    removeHead(&buffer);
    removeHead(&buffer);

    printBuffer(&buffer);
}

void blackBoxTest_fifth() {
    for(int i = 1; i < 3 ; i++) {
        addElement(&buffer, i);
        printBuffer(&buffer);
    }
    for (int i = 0; i < 2; i++)
    {
        removeHead(&buffer);
        printBuffer(&buffer);
    }
    
}

void blackBoxTest_sixth() {
    int result = contains(&buffer, 10);
        printf("%d", result);
}

void blackBoxTest_seventh() {
    int value = 7;
    addElement(&buffer, value);
    printBuffer(&buffer);
    int result = contains(&buffer, value);
        printf("%d", result);
    removeHead(&buffer);
}

void blackBoxTest_eighth() {
    int firstValue = 8, secondValue = 9;
    addElement(&buffer, firstValue);
    addElement(&buffer, secondValue);
    printBuffer(&buffer);
    int result = contains(&buffer, secondValue);
        printf("%d", result);
}

void blackBoxTest_ninth() {
    for(int i = 1; i < BUFFER_SIZE+1; i++) {
        addElement(&buffer, i); // Ensure different values
    }
    printBuffer(&buffer);
    int result = contains(&buffer, BUFFER_SIZE); // Last added value
        printf("%d", result);
    removeHead(&buffer);
    removeHead(&buffer);
    removeHead(&buffer);
    removeHead(&buffer);
}
void app_main() {

    // Some code to help you get started
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE);
    ets_delay_us(2000000ul);

    run_whitebox_tests();

    printf("\n\n\n");

}
