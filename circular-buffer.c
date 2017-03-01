// Copyright 2017 Dakota Boin
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "circular-buffer.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" 
{
#endif // __cplusplus

size_t CB_Peek(CircularBuffer*c, size_t p)
{
	return((p + 1) % c->bufferLength);
}

void CB_IncrementImmutableTail(CircularBuffer_ImmutableCopy* ci)
{

}

void CB_IncrementTail(size_t* tail, size_t* bytesAvailable, size_t bufferLength)
{
	if((*bytesAvailable) == 0)
		return;

	(*tail) = ((*tail) + 1) % bufferLength;

	(*bytesAvailable)--;
}

void CB_IncrementHead(CircularBuffer* c)
{
	if(c->bytesAvailable == c->bufferLength)
		CB_IncrementTail(&(c->tail), &(c->bytesAvailable), c->bufferLength);

	c->head = (c->head + 1) % c->bufferLength;

	c->bytesAvailable++;
}

int CB_IsCBIValid(CircularBuffer_ImmutableCopy* ci)
{
	if(ci == 0)
		return(-4);

	if(ci->original == 0)
		return(-5);

	return(1);
}

int CB_IsCBValid(CircularBuffer* c)
{
	if(c == 0)
		return(-1);

	if(c->buffer == 0)
		return(-2);

	if(c->bufferLength < 2)
		return(-10);

	return(1);
}

int CircularBuffer_Init(CircularBuffer* c)
{
	int error;

	// verify parameters
	if((error = CB_IsCBValid(c)) != 1)
		return(error);

	c->head = 0;
	c->tail = 0;
	c->bytesAvailable = 0;

	return(c->bufferLength);
}

int CircularBuffer_Write(CircularBuffer* c, uint8_t* bytesIn, size_t length)
{
	int error;

	// verify parameters
	if((error = CB_IsCBValid(c)) != 1)
		return(error);

	if(bytesIn == 0)
		return(-3);

	for(int i = 0; i < length; i++)
	{
		c->buffer[c->head] = bytesIn[i];
		CB_IncrementHead(c);
	}

	return(length);
}

int CircularBuffer_Read(CircularBuffer* c, uint8_t* bytesOut, size_t length)
{
	int error;
	int readBytes = 0;

	// verify parameters
	if((error = CB_IsCBValid(c)) != 1)
		return(error);

	if(bytesOut == 0)
		return(-3);

	// load bytes into buffer.
	for(int i = 0; i < length; i++)
	{
		if(c->bytesAvailable == 0)
			return(readBytes);

		readBytes++;
		bytesOut[i] = c->buffer[c->tail];
		CB_IncrementTail(&(c->tail), &(c->bytesAvailable), c->bufferLength);
	}

	return(readBytes);
}

int CircularBuffer_GetAvailableBytes(CircularBuffer* c)
{
	int error;

	// verify parameters
	if((error = CB_IsCBValid(c)) != 1)
		return(error);

	return(c->bytesAvailable);
}

int CircularBuffer_CopyToArray(CircularBuffer* c, uint8_t* arrayOut, size_t length)
{
	int error;
	int bytesCoppied = 0;
	size_t t;

	// verify parameters
	if((error = CB_IsCBValid(c)) != 1)
		return(error);

	if(arrayOut == 0)
		return(-3);

	t = c->tail;
	for(int i = 0; i < length; i++)
	{
		if(c->bytesAvailable == i)
			return(bytesCoppied);

		arrayOut[i] = c->buffer[t];
		t = CB_Peek(c, t);
		bytesCoppied++;
	}

	return(bytesCoppied);
}


int CircularBuffer_Copy(CircularBuffer* c, CircularBuffer_ImmutableCopy* ci)
{
	int error;

	// verify parameters
	if((error = CB_IsCBValid(c)) != 1)
		return(error);

	if(ci == 0)
		return(-4);

	ci->tail = c->tail;
	ci->bytesAvailable = c->bytesAvailable;
	ci->original = c;

	return(0);
}


int CircularBuffer_ImmutableRead(CircularBuffer_ImmutableCopy* ci, uint8_t* bytesOut, size_t length)
{
	int error;
	int readBytes = 0;

	if((error = CB_IsCBIValid(ci)) != 1)
		return(error);

	if(bytesOut == 0)
		return(-3);

	// load bytes into buffer.
	for(int i = 0; i < length; i++)
	{
		if(ci->bytesAvailable == 0)
			return(readBytes);

		readBytes++;
		bytesOut[i] = ci->original->buffer[ci->tail];
		CB_IncrementTail(&(ci->tail), &(ci->bytesAvailable), ci->original->bufferLength);
	}

	return(readBytes);
}


int CircularBuffer_ImmutableSeek(CircularBuffer_ImmutableCopy* ci, size_t offset)
{
	int error;

	// verify parameters
	if((error = CB_IsCBIValid(ci)) != 1)
		return(error);

	return(0);
}

#ifdef __cplusplus
}
#endif //__cplusplus
