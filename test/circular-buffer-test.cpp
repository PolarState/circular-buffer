#include "gtest/gtest.h"
#include "circular-buffer.h"
#include <string.h>

void printBuffer(uint8_t* buffer, size_t length)
{
	for(int i = 0; i < length; i++)
	{
		printf("%02x ", buffer[i]);
	}
	printf("\n");
}

// circular_buffer_init TODO:
// - 

TEST(circular_buffer_init, empty)
{
	uint			l = 0;
	uint8_t 		a[l];
	CircularBuffer	b = 
	{
		.head = 0,
		.tail = 0,
		.buffer = a,
		.bufferLength = l,
	};

	EXPECT_EQ(-10, CircularBuffer_Init(&b));
}

TEST(circular_buffer_init, invalid_min)
{
	uint			l = 0;
	uint8_t 		a[l];
	CircularBuffer	b = 
	{
		.head = 0,
		.tail = 0,
		.buffer = a,
		.bufferLength = l,
	};

	EXPECT_EQ(-10, CircularBuffer_Init(&b));
}

TEST(circular_buffer_init, valid_min)
{
	uint			l = 2;
	uint8_t 		a[l];
	CircularBuffer	b = 
	{
		.head = 0,
		.tail = 0,
		.buffer = a,
		.bufferLength = l,
	};

	EXPECT_EQ(2, CircularBuffer_Init(&b));
}

// circular_buffer_rw TODO:
// - 
TEST(circular_buffer_rw, single_byte)
{
	// circular buffer variables
	uint			memoryLength = 10;
	uint8_t 		memory[memoryLength];
	CircularBuffer	buffer = 
	{
		.head = 0,
		.tail = 0,
		.buffer = memory,
		.bufferLength = memoryLength,
	};

	// bytes to write
	uint8_t byteIn = 0xff;
	uint8_t byteOut = 0x00;

	EXPECT_EQ(10, CircularBuffer_Init(&buffer));

	EXPECT_EQ(1, CircularBuffer_Write(&buffer, &byteIn, 1));
	EXPECT_EQ(1, CircularBuffer_Read(&buffer, &byteOut, 1));

	EXPECT_EQ(byteIn, byteOut);
}

TEST(circular_buffer_rw, overflow_SingleWrite)
{
	// circular buffer variables
	uint			bufferLength = 10;
	uint			memoryLength = bufferLength;
	uint8_t 		memory[memoryLength];
	CircularBuffer	buffer = 
	{
		.head = 0,
		.tail = 0,
		.buffer = memory,
		.bufferLength = memoryLength,
	};


	// bytes to write
	uint	byteLength = 12;
	uint8_t bytesIn[byteLength];
	uint8_t bytesOut[bufferLength];

	for(int i = 0; i < byteLength; i++)
	{
		bytesIn[i] = i;
	}

	EXPECT_EQ(bufferLength, CircularBuffer_Init(&buffer));

	EXPECT_EQ(byteLength, CircularBuffer_Write(&buffer, bytesIn, byteLength));
	EXPECT_EQ(bufferLength, CircularBuffer_Read(&buffer, bytesOut, bufferLength));

	EXPECT_EQ(0, memcmp(&bytesIn[2], &bytesOut[0], bufferLength));
}

TEST(circular_buffer_rw, read_without_write)
{
	// circular buffer variables
	uint	memoryLength = 10;
	uint8_t memory[memoryLength];
	CircularBuffer	buffer = 
	{
		.head = 0,
		.tail = 0,
		.buffer = memory,
		.bufferLength = memoryLength,
	};

	// bytes to write
	uint8_t byteIn = 0xff;
	uint8_t byteOut = 0x00;

	EXPECT_EQ(10, CircularBuffer_Init(&buffer));

	EXPECT_EQ(0, CircularBuffer_Read(&buffer, &byteOut, 1));

	EXPECT_EQ(0x00, byteOut);
}

// circular_buffer_copy TODO:
// - copy after read and write cycle.
// - attempt to copy too much.
TEST(circular_buffer_copy, copy_buffer_overflowed)
{
	// circular buffer variables
	uint			bufferLength = 10;
	uint			memoryLength = bufferLength;
	uint8_t 		memory[memoryLength];
	CircularBuffer	buffer = 
	{
		.head = 0,
		.tail = 0,
		.buffer = memory,
		.bufferLength = memoryLength,
	};


	// bytes to write.
	uint	byteLength = 12;
	uint8_t bytesIn[byteLength];
	
	// array to copy too.
	uint8_t arrayOut[bufferLength];

	for(int i = 0; i < byteLength; i++)
	{
		bytesIn[i] = i;
	}

	EXPECT_EQ(10, CircularBuffer_Init(&buffer));
	EXPECT_EQ(byteLength, CircularBuffer_Write(&buffer, bytesIn, byteLength));
	EXPECT_EQ(bufferLength, CircularBuffer_CopyToArray(&buffer, arrayOut, bufferLength));

	EXPECT_EQ(0, memcmp(&bytesIn[2], arrayOut, bufferLength));
}

// circular_buffer_read_only_copy TODO:
// - tests which update the buffer during use by the immutable copy.
// - null pointers passed for each parameter on init etc.
// - add comments... 
TEST(circular_buffer_read_only_copy, read_only_after_overflow)
{
	// circular buffer variables
	uint			bufferLength = 10;
	uint			memoryLength = bufferLength;
	uint8_t 		memory[memoryLength];
	CircularBuffer	buffer = 
	{
		.head = 0,
		.tail = 0,
		.buffer = memory,
		.bufferLength = memoryLength,
	};

	CircularBuffer_ImmutableCopy	immutableBuffer;
	uint	firstRead = 6;

	// bytes to write.
	uint	byteLength = 12;
	uint8_t bytesIn[byteLength];
	
	// circular buffer copy.
	uint8_t arrayOut[bufferLength];

	for(int i = 0; i < byteLength; i++)
	{
		bytesIn[i] = i;
	}

	EXPECT_EQ(bufferLength, CircularBuffer_Init(&buffer));
	EXPECT_EQ(byteLength, CircularBuffer_Write(&buffer, bytesIn, byteLength));

	EXPECT_EQ(0, CircularBuffer_Copy(&buffer, &immutableBuffer));

	EXPECT_EQ(firstRead, CircularBuffer_ImmutableRead(&immutableBuffer, arrayOut, firstRead));

	EXPECT_EQ(0, memcmp(&bytesIn[2], arrayOut, firstRead));

	EXPECT_EQ(bufferLength - firstRead, CircularBuffer_ImmutableRead(&immutableBuffer, &arrayOut[firstRead], bufferLength - firstRead));

	

	EXPECT_EQ(0, memcmp(&bytesIn[2], arrayOut, bufferLength));	
}
