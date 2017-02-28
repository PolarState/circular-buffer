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

#ifndef __CIRCULAR_BUFFER__
#define __CIRCULAR_BUFFER__

// Circular Buffer implementation
//
// Error defines:
// -1	: null CircularBuffer pointer passed.
// -2	: null CircularBuffer->buffer pointer passed.
// -3	: null in/out buffer passed.
// -10	: buffer length too short.


#ifdef __cplusplus
extern "C" 
{
#endif // __cplusplus

#include <stdint.h>
#include <stdlib.h>
#include <string.h>


typedef struct CircularBuffer
{
	size_t head;
	size_t tail;
	size_t bytesAvailable;
	size_t bufferLength;
	uint8_t* buffer;

} CircularBuffer;


// Initalizes a new instance of circular buffer.
// Parameters:
//	circularBuffer	- pointer to circularBuffer instance.
//	emptyMemory		- initalized memory to use for the buffer. !! Allocation of memory must last the duration of buffer usage.
//	length			- length of array passed. Minimum length returned by CircularBuffer_GetMinimumLength.
//  Errors (negatives) or length of bytes in circular buffer usable for data storage (positive)
int CircularBuffer_Init(CircularBuffer* circularBuffer);

// Writes byte-wise to buffer.
// Parameters:
//	circularBuffer	- pointer to circularBuffer instance.
//	bytesIn			- byte array to write into buffer.
//	length			- length of byte array to write. -- can be longer than circular buffer but first values stored will be overwritten.
// Returns:
//  Errors (negatives) or number of bytes written (positive)
int CircularBuffer_Write(CircularBuffer* circularBuffer, uint8_t* bytesIn, size_t length);

// Reads byte-wise to buffer.
// Parameters:
//	circularBuffer	- pointer to circularBuffer instance.
//	bytesIn			- byte array to read into buffer.
//	length			- length of byte array to read. -- can be longer than circular buffer but those bytes will go unwritten.
// Returns:
//  Errors (negatives) or number of bytes read (positive)
int CircularBuffer_Read(CircularBuffer* circularBuffer, uint8_t* bytesOut, size_t length);

// Coppies byte-wise to buffer. Does not remove data coppied from buffer.
// Parameters:
//	circularBuffer	- pointer to circularBuffer instance.
//	arrayOut		- byte array to read into buffer.
//	length			- length of byte array to copy. -- can be longer than circular buffer but those bytes will go unwritten.
// Returns:
//  Errors (negatives) or number of bytes read (positive)
int CircularBuffer_CopyToArray(CircularBuffer* circularBuffer, uint8_t* arrayOut, size_t length);

// Bytes available to read.
// Parameters:
//	circularBuffer	- pointer to circularBuffer instance.
// Returns:
//  Errors (negatives) or number of bytes available (positive).
int CircularBuffer_GetAvailableBytes(CircularBuffer* circularBuffer);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif //__CIRCULAR_BUFFER__
