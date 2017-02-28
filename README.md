# [Yet Another] Circular Buffer.

## Description:
This circular-buffer implementation can be used to store arbitrary bytes as well as fixed size 'objects'. If you are trying to use this to store fixed size objects make sure to pick a buffer size equal to a multiple of the object size. Otherwise partial objects may occur when the circular-buffer overwrites itself.

Implementation is targeted at embedded systems and therefore has no dependencies outside of the c standard library. Test setup is using gcc and the library for gtest_main.a was compiled on a mac.

## TODO:
- add exhaustive tests
- remove compiled gtest_main.a library.
- add cmake build script for test (increases portability)


## Usage:
simply copy source files to import circular-buffer 'library'

```
	// circular buffer parameters
	// this buffer has 10 bytes of storage for the user.
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

	uint	byteLength = 12;
	uint8_t bytesIn[byteLength];
	uint8_t bytesOut[bufferLength];

	for(int i = 0; i < byteLength; i++)
	{
		bytesIn[i] = i;
	}


	// initiate buffer
	CircularBuffer_Init(&buffer, memory, memoryLength);


	// buffer read and write examples

	// single bytes
	CircularBuffer_Write(&buffer, &byteIn, 1);
	CircularBuffer_Read(&buffer, &byteOut, 1);

	// multiple bytes
	CircularBuffer_Write(&buffer, bytesIn, byteLength);
	CircularBuffer_Read(&buffer, bytesOut, bufferLength);

```

For more example usage please see the circular-buffer-test.cpp in the folder test.