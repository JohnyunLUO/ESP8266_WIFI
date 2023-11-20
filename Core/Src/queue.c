/*
 * queue.c
 *
 *  Created on: Oct 29, 2023
 *      Author: u9923001
 */

#include "queue.h"

void QueueInit(Queue_t *buffer, char *buf, int buf_size) {
  buffer->data = buf;
  buffer->capacity = buf_size;
  buffer->back = -1;
  buffer->front = 0;
  buffer->size = 0;
}

void QueueWrite(Queue_t *buffer, char data) {
	int position = (buffer->back + 1) % buffer->capacity;
	if (buffer->size < buffer->capacity)
	{
		buffer->back = position;
		buffer->data[buffer->back] = data;
		buffer->size++;
		return;
	}
	else
	{
		return;
	}
}

void QueueWriteBlock(Queue_t *buffer, const char *data, int size) {
  /* Add bytes; one by one */
  int i;
  for(i = 0; i < size; i++) {
	  QueueWrite(buffer, data[i]);
  }
}

uint8_t QueueRead(Queue_t *buffer, char *data) {
	int position = (buffer->front+ 1) % buffer->capacity;
	if (buffer->size>0)
	{
		int front_element = buffer->data[buffer->front];
		buffer->front = position;
		buffer->size--;
		*data = front_element;
		return 1;
	}
	else
	{
		return 0;
	}
}

int QueueReadBlock(Queue_t *buffer, char *data, int len) {
  if(QueueIsEmpty(buffer)) {
    /* No items */
    return 0;
  }

  char *data_ptr = data;
  int cnt = 0;
  while((cnt < len) && QueueRead(buffer, data_ptr)) {
    cnt++;
    data_ptr++;
  }
  return cnt;
}

extern inline uint8_t QueueIsEmpty(Queue_t *buffer);
extern inline uint8_t QueueIsFull(Queue_t *buffer);
extern inline int QueueNumItems(Queue_t *buffer);

