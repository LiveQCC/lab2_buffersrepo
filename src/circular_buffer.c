#include <stdio.h>
#include <limits.h>
#include "circular_buffer.h"



void initCircularBuffer(struct circularBuffer* bufferPtr, int* data, int maxLength) {
  bufferPtr->data = data;
  bufferPtr->head = 0;
  bufferPtr->tail = 0;
  bufferPtr->maxLength = maxLength;
  bufferPtr->numData = 0; // empty size at beginning
}

  inline int positive_modulo(int i, int n) {
    return (i % n + n) % n;
}


int isEmpty(struct circularBuffer* bufferPtr){
  if(bufferPtr->numData == 0){
      return 1;
    } else{
      return 0;
  }
  
  }

int isFull(struct circularBuffer* bufferPtr){
    if(bufferPtr-> numData == bufferPtr->maxLength)
    {
      return 1;
    } else{
      return 0;
    }
  }

int addElement(struct circularBuffer* bufferPtr, int value){
  if(isFull(bufferPtr)){
      return INT_MIN;
  }  
  bufferPtr->data[bufferPtr->tail] = value;
  bufferPtr->numData++;
  bufferPtr->tail = positive_modulo(bufferPtr->tail-1, bufferPtr->maxLength);
  return value;
}

int removeHead(struct circularBuffer* bufferPtr){
  int removedValue;
  if(isEmpty(bufferPtr)){
    return INT_MIN;
  }
  removedValue = bufferPtr->data[bufferPtr->head];
  bufferPtr->numData--;
  bufferPtr->head = positive_modulo(bufferPtr->head - 1, bufferPtr->maxLength);

  return removedValue;
}


int contains(struct circularBuffer* bufferPtr, int value){
  int index = bufferPtr->tail;
  int valueFound;
  if (isEmpty(bufferPtr))
  {
    return INT_MIN;
  }
  for(int i = 0; i<bufferPtr->maxLength; i++){
      if(bufferPtr->data[index] == value){
        valueFound = 1;
      } 
    index = (index + 1 ) % bufferPtr->maxLength;
  }
  if(valueFound == 1){
    return value;
  } else{
  return INT_MIN;
  }

}

int removeValue(struct circularBuffer* bufferPtr, int value){
 // int index = bufferPtr->tail;
  //int temp;
  //int count = bufferPtr->numData;
  //int removedValue;
  //int replacement = 77;
  //int valueRemoved;
  int index, nextIndex;
  int valueRemoved = 0; // Initially, no value is removed.
  int count = bufferPtr->numData; // Number of elements to check.

  if(isEmpty(bufferPtr)){
    return INT_MIN;
  }



    for(int i = 0; i < count; i++){
        index = (bufferPtr->head + i) % bufferPtr->maxLength; // Calculate current index in a circular manner.
        if(bufferPtr->data[index] == value){
            // Shift all subsequent elements one position towards the head.
            for(int j = i; j < count - 1; j++){
                nextIndex = (bufferPtr->head + j) % bufferPtr->maxLength;
                int nextIndexPlusOne = (bufferPtr->head + j + 1) % bufferPtr->maxLength;
                bufferPtr->data[nextIndex] = bufferPtr->data[nextIndexPlusOne];
            }
            bufferPtr->numData--; // Decrease the number of data elements.
            bufferPtr->tail = (bufferPtr->tail - 1 + bufferPtr->maxLength) % bufferPtr->maxLength; // Update the tail position in a circular manner.
            valueRemoved = 1; // Mark that a value has been removed.
            i--; // Adjust loop index since we've removed an element.
            count--; // Decrease count since the total number of elements has decreased.
        }
    }
  
  /*for(int i = 0; i<bufferPtr->maxLength; i++){
    if(bufferPtr->data[index] == value){
      removedValue = bufferPtr->data[index];
      bufferPtr->numData--;
      valueRemoved = 1;
      for(int y = 0; y<bufferPtr->maxLength; y++){
        bufferPtr->data[index] = bufferPtr->data[i+1];
      }
    bufferPtr->tail = positive_modulo(bufferPtr->tail-1,bufferPtr->maxLength) ;

    }
    index = positive_modulo(index - 1, bufferPtr->maxLength);

  }
 */

  /*
  for(int i = 0; i<bufferPtr->maxLength; i++){
    if(bufferPtr->data[index] == value){
      removedValue = bufferPtr->data[index];

      bufferPtr->data[index] = bufferPtr->data[index+1];
      //bufferPtr->data[index+1] = replacement;
      valueRemoved = 1;
      bufferPtr->numData--;
      bufferPtr->tail = positive_modulo(bufferPtr->tail-1,bufferPtr->maxLength) ;

    }
    index = positive_modulo(index - 1, bufferPtr->maxLength);
  }*/
  if(valueRemoved == 1){
      return value;
    }else{
      return INT_MIN;
    }

}
/*void printBuffer(struct circularBuffer* bufferPtr) {
    if (bufferPtr->numData == 0) {
        printf("Buffer is empty.\n");
        return;
    }

    printf("Buffer contents: ");
    int i = bufferPtr->head;
    do {
        printf("%d ", bufferPtr->data[i]);
        i = (i + 1) % bufferPtr->maxLength; 
    } while (i != bufferPtr->tail);
    printf("\n");
}
*/

void printBuffer(struct circularBuffer* bufferPtr){
  //int index = bufferPtr->tail;
  printf("dis da tail %d ", bufferPtr->tail );
  printf("dis da head %d ", bufferPtr->head );
  for(int i = 0; i < bufferPtr->numData; i++){
    printf("Value is %d\n ", bufferPtr->data[positive_modulo(bufferPtr->head-i,bufferPtr->maxLength)]);
    
   // index = (index + 1) % bufferPtr -> maxLength;
  } printf("\n");
}





