/*
 ============================================================================
 Name        : main.c
 Author      : Team3#Dennis
 Version     :
 Copyright   : Steal the code!
 Description : Circular Buffer TEST program
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "CircularBuffer.h"

#define SIZE 10

int main(void){
	int i, val, fail = 0;
	cbuf lbuf1, lbuf2;
	int array[SIZE*2];

	//Initialize a circular buffer with no overwrite mode.
	initialise(&lbuf1, SIZE, NOOVERWRITE);

	//Check 1: Buffer empty at start
	if(get(&lbuf1) != EMPTY) fail++;

	//Check 2: write until buffer is full, count number of data sent + save sent data in local array
	i=0;
	while(1){
		val = rand()%100;
		array[i] = val;
		if(put(&lbuf1, val) == FULL) break;
		i++;
		if(i>SIZE*2) break;		//Timeout
	}
	if(i != SIZE) fail++;

	//Check3: Read all data from buffer and compare to local array
	i=0;
	while(1){
		val = get(&lbuf1);
		if(val == EMPTY) break;
		if(val != array[i]) fail++;
		i++;
		if(i>SIZE*2) break;		//Timeout
	}
	if(i != SIZE) fail++;

	//Check4: Write + read data right after each other to avoid FULL flag, do this 3xSIZE of the array
	//		  In the end, check if the buffer is empty (as it should be).
	for(i=0; i<SIZE*3; i++){
		put(&lbuf1, i);
		val = get(&lbuf1);
		if(val == EMPTY) fail++;
		if(val != i) fail++;
	}
	if(get(&lbuf1) != EMPTY) fail++;

	//Initialize a circular buffer with overwrite mode on and a different size than the first buffer
	initialise(&lbuf2, SIZE*2, OVERWRITE);

	//Check5: Write twice size of data as the buffer is wide without getting any FULL flags
	for(i=0; i<SIZE*4; i++){
		if(put(&lbuf2, i) == FULL) fail++;
		if(i<SIZE*2) array[i] = i;
		else array[i-(SIZE*2)] = i;
	}

	//Check6: Check the overrun buffer for correct data
	i=0;
	while(1){
		val = get(&lbuf2);
		if(val == EMPTY) break;
		if(val != array[i]) fail++;
		i++;
		if(i>SIZE*4) break;		//Timeout
	}
	if(i != SIZE*2) fail++;

	//Check7: Write to both circular buffers (one with overwrite on, and one where it is off)
	i=0;
	while(1){
		val = rand()%100;
		if(put(&lbuf2, val*2) == FULL) break;
		if(put(&lbuf1, val) == FULL) break;
		array[i] = val;
		i++;
		if(i>SIZE*4) break;		//Timeout
	}
	if(i != SIZE) fail++;

	//Check8: Read both buffers and see if they contain the right data.
	i=0;
	while(1){
		val = get(&lbuf1);
		if(val == EMPTY) break;
		if(val != array[i]) fail++;
		val = get(&lbuf2);
		if(val == EMPTY) break;
		if(val != array[i]*2) fail++;
		i++;
		if(i>SIZE*2) break;		//Timeout
	}
	if(i != SIZE) fail++;

	// Write out number of errors, if any.
	if(fail > 0) printf("NUMBER OF FAILS: %d",fail);
	else printf("TEST OK");
	return 0;
}
