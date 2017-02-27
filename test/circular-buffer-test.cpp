#include "gtest/gtest.h"
#include "circular-buffer.h"
#include <string.h>

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
	uint			l = CircularBuffer_MinimumLength;
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
	uint			l = CircularBuffer_MinimumLength + 2;
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

TEST(circular_buffer_rw, single_byte)
{
	// circular buffer variables
	uint			memoryLength = CircularBuffer_MinimumLength + 10;
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
	uint			memoryLength = CircularBuffer_MinimumLength + bufferLength;
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
	uint	memoryLength = CircularBuffer_MinimumLength + 10;
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

