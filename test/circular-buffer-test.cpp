#include "gtest/gtest.h"
#include "circular-buffer.h"
#include <string.h>

TEST(circular_buffer_init, empty)
{
	void*	b;
	void*	placeholder = b;
	uint	l = 0;
	uint8_t a[l];

	EXPECT_EQ(-2, CircularBuffer_Init(&b, a, l));
	EXPECT_EQ(b, placeholder);
	EXPECT_NE(b, (void*)a);
}

TEST(circular_buffer_init, invalid_min)
{
	void*	b;
	void*	placeholder = b;
	uint	l = CircularBuffer_GetMinimumLength();
	uint8_t a[l];

	EXPECT_NE(0, l);
	EXPECT_EQ(-2, CircularBuffer_Init(&b, a, l));
	EXPECT_EQ(b, placeholder);
	EXPECT_NE(b, (void*)a);
}

TEST(circular_buffer_init, valid_min)
{
	void*	b;
	void*	placeholder = b;
	uint	l = CircularBuffer_GetMinimumLength() + 2;
	uint8_t a[l];

	EXPECT_NE(2, l);
	EXPECT_EQ(2, CircularBuffer_Init(&b, a, l));
	EXPECT_NE(b, placeholder);
	EXPECT_EQ(b, (void*)a);
}

TEST(circular_buffer_rw, single_byte)
{
	// circular buffer variables
	void*	buffer;
	uint	memoryLength = CircularBuffer_GetMinimumLength() + 10;
	uint8_t memory[memoryLength];

	// bytes to write
	uint8_t byteIn = 0xff;
	uint8_t byteOut = 0x00;

	EXPECT_EQ(10, CircularBuffer_Init(&buffer, memory, memoryLength));

	EXPECT_EQ(1, CircularBuffer_Write(buffer, &byteIn, 1));
	EXPECT_EQ(1, CircularBuffer_Read(buffer, &byteOut, 1));

	EXPECT_EQ(byteIn, byteOut);
}

TEST(circular_buffer_rw, overflow_SingleWrite)
{
	// circular buffer variables
	void*	buffer;
	uint	bufferLength = 10;
	uint	memoryLength = CircularBuffer_GetMinimumLength() + bufferLength;
	uint8_t memory[memoryLength];

	// bytes to write
	uint	byteLength = 12;
	uint8_t bytesIn[byteLength];
	uint8_t bytesOut[bufferLength];

	for(int i = 0; i < byteLength; i++)
	{
		bytesIn[i] = i;
	}

	EXPECT_EQ(bufferLength, CircularBuffer_Init(&buffer, memory, memoryLength));

	EXPECT_EQ(byteLength, CircularBuffer_Write(buffer, bytesIn, byteLength));
	EXPECT_EQ(bufferLength, CircularBuffer_Read(buffer, bytesOut, bufferLength));

	EXPECT_EQ(0, memcmp(&bytesIn[2], &bytesOut[0], bufferLength));
}

TEST(circular_buffer_rw, read_without_write)
{
	// circular buffer variables
	void*	buffer;
	uint	memoryLength = CircularBuffer_GetMinimumLength() + 10;
	uint8_t memory[memoryLength];

	// bytes to write
	uint8_t byteIn = 0xff;
	uint8_t byteOut = 0x00;

	EXPECT_EQ(10, CircularBuffer_Init(&buffer, memory, memoryLength));

	EXPECT_EQ(0, CircularBuffer_Read(buffer, &byteOut, 1));

	EXPECT_EQ(0x00, byteOut);
}

