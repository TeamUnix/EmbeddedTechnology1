/*
 * CircularBuffer.h
 *
 *  Created on: Nov 15, 2011
 *      Author: Team3#Dennis
 */

#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

// Structures
typedef struct{
	int *p_rd;	//pointer to current read add of the buffer
	int *p_wr;	//pointer to current write add of the buffer
	int *p_start; //pointer to start of the buffer
	int count;	//continues the amount of data written to the buffer
	int mode;	//holds the mode of the buffer (overwrite / no overwrite)
	int size;	//size of the array
} cbuf, *pbuf;

// Prototypes
int put(cbuf *buf, int val);
int get(cbuf *buf);
int isEmpty(int count);
int isFull(int count, int size);
void initialise(cbuf *buf, int size, int overwrite);
void delete(cbuf *buf);

// Defines
#define FULL -1
#define EMPTY -2

#define NOOVERWRITE 0
#define OVERWRITE   1

#endif /* CIRCULARBUFFER_H_ */
