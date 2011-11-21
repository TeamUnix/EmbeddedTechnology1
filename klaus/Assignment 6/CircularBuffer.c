/*
 ============================================================================
 Name        : CircularBuffer.c
 Author      : Team3#Dennis
 Version     :
 Copyright   : Steal the code!
 Description : Circular Buffer
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "CircularBuffer.h"

/****************************************************************************
 * Description: int put(cbuf *buf, int val)
 *
 * Checks if the buffer is full. If it is full and the mode is set to overwrite
 * Data is shiftet, so the read pointer still looks at the oldest value in the buffer.
 * If the overwrite is off, data is not written if the buffer is full.
 * If the buffer is not full, data is written and the write pointer is incremented.
 *
 * Parameters:
 * 		*buf 		: Pointer to the circular buffer structure (type cbuf)
 * 		val			: Value that should be written to the buffer
 *
 *		return		: -1 if buffer is full, 0 otherwise
 ***************************************************************************/
int put(cbuf *buf, int val){
	if(isFull(buf->count, buf->size) == FULL){	//Checks if buffer is full.
		if(buf->mode == NOOVERWRITE){			//Mode check
			return FULL;						//Return FULL flag if noowerwrite mode and buffer is full.
		}
		else if(buf->mode == OVERWRITE){		//Point read pointer to second oldest value if in overwrite mode
			if(buf->p_rd == buf->p_start+buf->size) buf->p_rd = buf->p_start;
			else buf->p_rd++;
		}
	}
	else{
		buf->count++;							//Increase count value (tells how much data the buffer contains)
	}

	*buf->p_wr = val;							//Put new data to the current position (write pointer)

		//If data has been written to the last place in the array, the pointer is pointed to the
		//start of the array. Otherwise the pointer is increased to point at the next data address.
	if(buf->p_wr == buf->p_start+buf->size) buf->p_wr = buf->p_start;
	else buf->p_wr++;

	return 0;
}

/****************************************************************************
 * Description: int get(cbuf *buf)
 *
 * Checks if the buffer is empty, if it is not, then the oldest value is returned
 *
 * Parameters:
 * 		*buf 		: Pointer to the circular buffer structure (type cbuf)
 *
 *		return		: Oldest value in the buffer. -1 if buffer is empty
 ***************************************************************************/
int get(cbuf *buf){
	int val;

	if(isEmpty(buf->count) == EMPTY){	//Checks if buffer is empty
		return EMPTY;					//Return if there is no data to read -2
	}

	buf->count--;			//Decrease count value (tells how much data the buffer contains)

	val = *buf->p_rd;		//Read data from the current position (read pointer)

		//If data has been read from the last place in the array, the pointer is pointed to the
		//start of the array. Otherwise the pointer is increased to point at the next data address.
	if(buf->p_rd == buf->p_start+buf->size) buf->p_rd = buf->p_start;
	else buf->p_rd++;

	return val;				//Return read data from buffer. -1 if buffer is empty
}

/****************************************************************************
 * Description: int isEmpty(int count)
 *
 * Checks if the buffer is empty
 *
 * Parameters:
 * 		count  	: number of data written to the buffer
 *
 *		return	: -2 if the buffer is empty, 0 otherwise
 ***************************************************************************/
int isEmpty(int count){
	if(count == 0){		//If count is 0, the array contains no data
		return EMPTY;	//EMPTY flag is returned
	}
	return 0;
}

/****************************************************************************
 * Description: int isFull(int count, int size)
 *
 * Checks if the buffer is full
 *
 * Parameters:
 *		size	: value containing the value of the cbuffer working on
 * 		count  	: number of data written to the buffer
 *
 *		return	: -1 if the buffer is full, 0 otherwise
 ***************************************************************************/
int isFull(int count, int size){
	if(count >= size){	//If the count value equal to the size of the array, the buffer is full
		return FULL;	//FULL flag is returned
	}
	return 0;
}

/****************************************************************************
 * Description: void initialise(cbuf *buf, int size, int overwrite)
 *
 * The function creates an int array of a certain size (parameter decided)
 * All values and pointers in the cbuf structure are zeroed.
 *
 * Parameters:
 * 		*buf 		: Pointer to the circular buffer structure (type cbuf)
 *		size		: Defines the size of the array that is created
 * 		overwrite 	: bit indicating the mode of the buffer
 *
 ***************************************************************************/
void initialise(cbuf *buf, int size, int overwrite){
	int *array;		//create a pointer of type int
					//create an array[size] in the heap and make the pointer created point to it
	array=(int *) malloc(size*sizeof(int));

	buf->p_rd = array;		//Point p_rd pointer point to start of the array
	buf->p_wr = array;		//Point p_wr 	-11-
	buf->p_start = array;	//Point p_start -11-
	buf->count = 0;			//reset counter (keeps track of number of data in the buffer)
	buf->mode = overwrite;	//mode bit (overwrite on / off when buffer is full)
	buf->size = size;		//holds value of buffer size
}
