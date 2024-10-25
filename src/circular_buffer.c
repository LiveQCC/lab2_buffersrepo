#include <stdio.h>
#include <limits.h>
#include "circular_buffer.h"

void initCircularBuffer(struct circularBuffer* bufferPtr, int* data, int maxLength) {
    bufferPtr->data = data;
    bufferPtr->head = 0;
    bufferPtr->tail = 0;
    bufferPtr->maxLength = maxLength;
    bufferPtr->numData = 0;
}

inline int positive_modulo(int i, int n) {
    return (i % n + n) % n;
}

int isEmpty(struct circularBuffer* bufferPtr) {
    return bufferPtr->numData == 0;
}

int isFull(struct circularBuffer* bufferPtr) {
    return bufferPtr->numData == bufferPtr->maxLength;
}

int addElement(struct circularBuffer* bufferPtr, int value) {
    if (isFull(bufferPtr)) {
        return INT_MIN;
    }
    
    bufferPtr->data[bufferPtr->tail] = value;
    bufferPtr->tail = (bufferPtr->tail + 1) % bufferPtr->maxLength;  // Increment tail
    bufferPtr->numData++;
    return value;
}

int removeHead(struct circularBuffer* bufferPtr) {
    if (isEmpty(bufferPtr)) {
        return INT_MIN;
    }
    
    int removedValue = bufferPtr->data[bufferPtr->head];
    bufferPtr->head = (bufferPtr->head + 1) % bufferPtr->maxLength;  // Increment head
    bufferPtr->numData--;
    return removedValue;
}

int contains(struct circularBuffer* bufferPtr, int value) {
    if (isEmpty(bufferPtr)) {
        return INT_MIN;
    }
    
    int count = bufferPtr->numData;
    for (int i = 0; i < count; i++) {
        int index = (bufferPtr->head + i) % bufferPtr->maxLength;
        if (bufferPtr->data[index] == value) {
            return value;
        }
    }
    return INT_MIN;
}

int removeValue(struct circularBuffer* bufferPtr, int value) {
    if (isEmpty(bufferPtr)) {
        return INT_MIN;
    }

    int valueFound = 0;
    int writeIndex = bufferPtr->head;
    int readIndex = bufferPtr->head;
    int count = bufferPtr->numData;

    // Scan through all elements
    for (int i = 0; i < count; i++) {
        readIndex = (bufferPtr->head + i) % bufferPtr->maxLength;
        
        if (bufferPtr->data[readIndex] != value) {
            // Keep this element
            if (writeIndex != readIndex) {
                bufferPtr->data[writeIndex] = bufferPtr->data[readIndex];
            }
            writeIndex = (writeIndex + 1) % bufferPtr->maxLength;
        } else {
            valueFound = 1;
            bufferPtr->numData--;
        }
    }

    // Update tail to point to the next empty position
    if (bufferPtr->numData > 0) {
        bufferPtr->tail = (bufferPtr->head + bufferPtr->numData) % bufferPtr->maxLength;
    } else {
        bufferPtr->head = bufferPtr->tail = 0;
    }

    return valueFound ? value : INT_MIN;
}

void printBuffer(struct circularBuffer* bufferPtr) {
    if (isEmpty(bufferPtr)) {
        printf("Buffer is empty\n");
        return;
    }
    
    printf("Head: %d, Tail: %d, Count: %d\nValues: ", 
           bufferPtr->head, bufferPtr->tail, bufferPtr->numData);
           
    for (int i = 0; i < bufferPtr->numData; i++) {
        int index = (bufferPtr->head + i) % bufferPtr->maxLength;
        printf("%d ", bufferPtr->data[index]);
    }
    printf("\n");
}