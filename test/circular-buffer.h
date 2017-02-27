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
// -1 : null pointer passed
// -2 : length too short

#ifdef __cplusplus
extern "C" 
{
#endif // __cplusplus

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Initalizes a new instance of circular buffer.
// Parameters:
//	circularBuffer	- opaque pointer to circularBuffer instance.
//	emptyMemory		- initalized memory to use for the buffer. !! Allocation of memory must last the duration of buffer usage.
//	length			- length of array passed. Minimum length returned by CircularBuffer_GetMinimumLength.
//  Errors (negatives) or length of bytes in circular buffer usable for data storage (positive)
int CircularBuffer_Init(void** circularBuffer, uint8_t*  emptyMemory, size_t length);

// Writes byte-wise to buffer.
// Parameters:
//	circularBuffer	- opaque pointer to circularBuffer instance.
//	bytesIn			- byte array to write into buffer.
//	length			- length of byte array to write. -- can be longer than circular buffer but first values stored will be overwritten.
// Returns:
//  Errors (negatives) or number of bytes written (positive)
int CircularBuffer_Write(void* circularBuffer, uint8_t* bytesIn, size_t length);

// Reads byte-wise to buffer.
// Parameters:
//	circularBuffer	- opaque pointer to circularBuffer instance.
//	bytesIn			- byte array to read into buffer.
//	length			- length of byte array to read. -- can be longer than circular buffer but those bytes will go unwritten.
// Returns:
//  Errors (negatives) or number of bytes read (positive)
int CircularBuffer_Read(void* circularBuffer, uint8_t* bytesOut, size_t length);

// Returns memory required to maintain an instance of CircularBuffer. 
// This is all overhead; useable buffer is in addition to this minimim.
size_t CircularBuffer_GetMinimumLength(void);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif //__CIRCULAR_BUFFER__
