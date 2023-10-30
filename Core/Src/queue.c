/*
 * queue.c
 *
 *  Created on: Oct 29, 2023
 *      Author: u9923001
 */

#include "queue.h"

void QueueInit(Queue_t *buffer, char *buf, int buf_size) {
  Queue_ASSERT(Queue_IS_POWER_OF_TWO(buf_size) == 1);
  buffer->buffer = buf;
  buffer->buffer_mask = buf_size - 1;
  buffer->tail_index = 0;
  buffer->head_index = 0;
}

void QueueWrite(Queue_t *buffer, char data) {
  /* Is buffer full? */
  if(QueueIsFull(buffer)) {
    /* Is going to overwrite the oldest byte */
    /* Increase tail index */
    buffer->tail_index = ((buffer->tail_index + 1) & Queue_MASK(buffer));
  }

  /* Place data in buffer */
  buffer->buffer[buffer->head_index] = data;
  buffer->head_index = ((buffer->head_index + 1) & Queue_MASK(buffer));
}

void QueueWriteBlock(Queue_t *buffer, const char *data, int size) {
  /* Add bytes; one by one */
  int i;
  for(i = 0; i < size; i++) {
	  QueueWrite(buffer, data[i]);
  }
}

uint8_t QueueRead(Queue_t *buffer, char *data) {
  if(QueueIsEmpty(buffer)) {
    /* No items */
    return 0;
  }

  *data = buffer->buffer[buffer->tail_index];
  buffer->tail_index = ((buffer->tail_index + 1) & Queue_MASK(buffer));
  return 1;
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

