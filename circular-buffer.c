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

#ifdef __cplusplus
extern "C" 
{
#endif // __cplusplus

size_t CB_Peek(CircularBuffer*c, size_t p)
{
	if(p == c->bufferLength - 1)
		return(0);
	else
		return(p + 1);
}

int CB_IsData(CircularBuffer* c)
{
	if(c->tail == c->head)
		return(0);
	else
		return(1);
}

void CB_IncrementTail(CircularBuffer* c)
{
	if(c->tail != c->head)
	{
		if(c->tail == c->bufferLength - 1)
			c->tail = 0;
		else
			c->tail++;
	}
}

void CB_IncrementHead(CircularBuffer* c)
{
	size_t peekHead = CB_Peek(c, c->head);

	if(c->tail == peekHead)
		CB_IncrementTail(c);

	if(c->head == c->bufferLength - 1)
		c->head = 0;
	else
		c->head++;
}

int CB_IsCBValid(CircularBuffer* c)
{
	if(c == 0)
		return(-1);

	if(c->buffer == 0)
		return(-2);

	if(c->bufferLength <= CircularBuffer_MinimumLength)
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

	return(c->bufferLength - CircularBuffer_MinimumLength);
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

	// verify parameters
	if((error = CB_IsCBValid(c)) != 1)
		return(error);

	if(bytesOut == 0)
		return(-3);

	int readBytes = 0;

	for(int i = 0; i < length; i++)
	{
		if(!CB_IsData(c))
			return(readBytes);

		readBytes++;
		bytesOut[i] = c->buffer[c->tail];
		CB_IncrementTail(c);
	}

	return(readBytes);
}

#ifdef __cplusplus
}
#endif //__cplusplus