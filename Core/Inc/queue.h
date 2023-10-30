/*
 * queue
 *
 *  Created on: Oct 29, 2023
 *      Author: u9923001
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#include <inttypes.h>
#include <stddef.h>
#include <assert.h>


#ifdef __cplusplus
extern "C"
{
#endif

#define Queue_ASSERT(x) assert(x)

/**
 * Checks if the buffer_size is a power of two.
 * Due to the design only <tt> RING_BUFFER_SIZE-1 </tt> items
 * can be contained in the buffer.
 * buffer_size must be a power of two.
*/
#define Queue_IS_POWER_OF_TWO(buffer_size) ((buffer_size & (buffer_size - 1)) == 0)

/**
 * Used as a modulo operator
 * as <tt> a % b = (a & (b − 1)) </tt>
 * where \c a is a positive index in the buffer and
 * \c b is the (power of two) size of the buffer.
 */
#define Queue_MASK(rb) (rb->buffer_mask)

/**
 * Structure which holds a ring buffer.
 * The buffer contains a buffer array
 * as well as metadata for the ring buffer.
 */
typedef struct {
  /** Buffer memory. */
  char *buffer;
  /** Buffer mask. */
  int buffer_mask;
  /** Index of tail. */
  int tail_index;
  /** Index of head. */
  int head_index;
}Queue_t;

/**
 * Initializes the ring buffer pointed to by <em>buffer</em>.
 * This function can also be used to empty/reset the buffer.
 * The resulting buffer can contain <em>buf_size-1</em> bytes.
 * @param buffer The ring buffer to initialize.
 * @param buf The buffer allocated for the ringbuffer.
 * @param buf_size The size of the allocated ringbuffer.
 */
void QueueInit(Queue_t *buffer, char *buf, int buf_size);

/**
 * Adds a byte to a ring buffer.
 * @param buffer The buffer in which the data should be placed.
 * @param data The byte to place.
 */
void QueueWrite(Queue_t *buffer, char data);

/**
 * Adds an array of bytes to a ring buffer.
 * @param buffer The buffer in which the data should be placed.
 * @param data A pointer to the array of bytes to place in the queue.
 * @param size The size of the array.
 */
void QueueWriteBlock(Queue_t *buffer, const char *data, int size);

/**
 * Returns the oldest byte in a ring buffer.
 * @param buffer The buffer from which the data should be returned.
 * @param data A pointer to the location at which the data should be placed.
 * @return 1 if data was returned; 0 otherwise.
 */
uint8_t QueueRead(Queue_t *buffer, char *data);

/**
 * Returns the <em>len</em> oldest bytes in a ring buffer.
 * @param buffer The buffer from which the data should be returned.
 * @param data A pointer to the array at which the data should be placed.
 * @param len The maximum number of bytes to return.
 * @return The number of bytes returned.
 */
int QueueReadBlock(Queue_t *buffer, char *data, int len);

/**
 * Returns whether a ring buffer is empty.
 * @param buffer The buffer for which it should be returned whether it is empty.
 * @return 1 if empty; 0 otherwise.
 */
inline uint8_t QueueIsEmpty(Queue_t *buffer) {
  return (buffer->head_index == buffer->tail_index);
}

/**
 * Returns whether a ring buffer is full.
 * @param buffer The buffer for which it should be returned whether it is full.
 * @return 1 if full; 0 otherwise.
 */
inline uint8_t QueueIsFull(Queue_t *buffer) {
  return ((buffer->head_index - buffer->tail_index) & Queue_MASK(buffer)) == Queue_MASK(buffer);
}

/**
 * Returns the number of items in a ring buffer.
 * @param buffer The buffer for which the number of items should be returned.
 * @return The number of items in the ring buffer.
 */
inline int QueueNumItems(Queue_t *buffer) {
  return ((buffer->head_index - buffer->tail_index) & Queue_MASK(buffer));
}

#ifdef __cplusplus
}
#endif


#endif /* INC_QUEUE_H_ */
