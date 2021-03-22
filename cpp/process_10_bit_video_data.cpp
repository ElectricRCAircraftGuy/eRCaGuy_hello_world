/*

GS
17 Mar. 2021

To compile and run (assuming you've already `cd`ed into this dir):
    mkdir -p bin && g++ -Wall -Wextra -Werror -ggdb -std=c++17 -o bin/process_10_bit_video_data \
    process_10_bit_video_data.cpp && bin/process_10_bit_video_data


References:
1. [my answer] https://stackoverflow.com/questions/66676585/add-bit-padding-bit-shifting-to-10bit-values-stored-in-a-byte-array/66678338#66678338

*/

#include <bitset>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>

// enum class PGroupErrorType
// {
//     ERROR_OK = 0,
//     ERROR_ARRAY_SIZE,
// };

// Get the number of elements in any C array
// - Usage example: [my own answer]:
//   https://arduino.stackexchange.com/questions/80236/initializing-array-of-structs/80289#80289
#define ARRAY_LEN(array) (sizeof(array)/sizeof(array[0]))

/// \brief      Process a packed video P group, which is 4 pixels of 10 bits each (exactly 5 uint8_t
///             bytes) into a uint16_t 4-element array (1 element per pixel).
/// \details    Each group of 10-bits for a pixel will be placed into a 16-bit word, with all 10
///             bits left-shifted to the far left edge, leaving 6 empty (zero) bits in the right
///             side of the word.
/// \param[in]  byteArrayIn  5 bytes of 10-bit pixel data for exactly 4 pixels; any array size < 5
///                        will result in undefined behavior! So, ensure you pass the proper array
///                        size in!
/// \param[out] twoByteArrayOut  The output array into which the 4 pixels will be packed, 10 bits per
///                        16-bit word, all 10 bits shifted to the left edge; any array size < 4
///                        will result in undefined behavior!
/// \return     None
void ProcessPGroup(const uint8_t byteArrayIn[5], uint16_t twoByteArrayOut[4])
{
    twoByteArrayOut[0] = (((uint16_t)byteArrayIn[0] & 0b11111111u) << (0 + 8)) | (((uint16_t)byteArrayIn[1] & 0b11000000u) << 0);
    twoByteArrayOut[1] = (((uint16_t)byteArrayIn[1] & 0b00111111u) << (2 + 8)) | (((uint16_t)byteArrayIn[2] & 0b11110000u) << 2);
    twoByteArrayOut[2] = (((uint16_t)byteArrayIn[2] & 0b00001111u) << (4 + 8)) | (((uint16_t)byteArrayIn[3] & 0b11111100u) << 4);
    twoByteArrayOut[3] = (((uint16_t)byteArrayIn[3] & 0b00000011u) << (6 + 8)) | (((uint16_t)byteArrayIn[4] & 0b11111111u) << 6);
}

// Reference: https://stackoverflow.com/questions/7349689/how-to-print-using-cout-a-number-in-binary-form/7349767
void PrintArrayAsBinary(const uint16_t* twoByteArray, size_t len)
{
    std::cout << "{\n";
    for (size_t i = 0; i < len; i++)
    {
        std::cout << std::bitset<16>(twoByteArray[i]);
        if (i < len - 1)
        {
            std::cout << ",";
        }
        std::cout << std::endl;
    }
    std::cout << "}\n";
}

int main()
{
    printf("Processing 10-bit video data example\n");

    constexpr uint8_t TEST_BYTE_ARRAY_INPUT[5] = {0b01110101, 0b01111010, 0b00001010, 0b11111010, 0b00000110};
    constexpr uint16_t TEST_TWO_BYTE_ARRAY_OUTPUT[4] = {
        0b0111010101000000, 0b1110100000000000, 0b1010111110000000, 0b1000000110000000};

    uint16_t twoByteArrayOut[4];
    ProcessPGroup(TEST_BYTE_ARRAY_INPUT, twoByteArrayOut);

    if (std::memcmp(twoByteArrayOut, TEST_TWO_BYTE_ARRAY_OUTPUT, sizeof(TEST_TWO_BYTE_ARRAY_OUTPUT)) == 0)
    {
        printf("TEST PASSED!\n");
    }
    else
    {
        printf("TEST ==FAILED!==\n");

        std::cout << "expected = \n";
        PrintArrayAsBinary(TEST_TWO_BYTE_ARRAY_OUTPUT, ARRAY_LEN(TEST_TWO_BYTE_ARRAY_OUTPUT));

        std::cout << "actual = \n";
        PrintArrayAsBinary(twoByteArrayOut, ARRAY_LEN(twoByteArrayOut));
    }

    return 0;
}

/*
SAMPLE OUTPUT:

    $ g++ -Wall -Wextra -Werror -ggdb -std=c++17 -o bin/process_10_bit_video_data     process_10_bit_video_data.cpp && bin/process_10_bit_video_data
    Processing 10-bit video data example
    TEST PASSED!

*/
