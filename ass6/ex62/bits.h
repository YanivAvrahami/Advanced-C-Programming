#ifndef BITS_H
#define BITS_H

// gets mask with LSB set
#define LSB_SET_MASK(TYPE) ((TYPE)1)

// gets mask with LSB clear
#define LSB_CLEAR_MASK(TYPE) (~(TYPE)1)

// gets mask with the first 8 LSB set
#define LSB8_SET_MASK(TYPE) ((TYPE)0xFF)

// gets mask with all bits set
#define ALL_BIT_SET_MASK(TYPE) (~(TYPE)0)

// gets mask with the i bit set
#define BIT_I_SET_MASK(I,TYPE) ((TYPE)(1) << I)

// gets mask with the i bit clear
#define BIT_I_CLEAR_MASK(I,TYPE) (~((TYPE)(1) << I))

// gets mask with the MSB set
#define MSB_SET_MASK(TYPE) ((TYPE)(1) << (8 * sizeof(TYPE) - 1))

// sets the i bit of a given number
#define SET_BIT(NUM,I,TYPE) (NUM |= BIT_I_SET_MASK(I,TYPE))

// clears the i bit of a given number
#define CLEAR_BIT(NUM,I,TYPE) (NUM &= BIT_I_CLEAR_MASK(I,TYPE))

// checks if the i bit is set in a given number
#define IS_BIT_I_SET(NUM,I) ((NUM >> I) & 1)

// gets mask with N LSB set
#define N_LSB_SET_MASK(TYPE, N) ((LSB_SET_MASK(TYPE) << N) - 1)

// gets mask with N LSB clear
#define N_LSB_CLEAR_MASK(TYPE, N) (~N_LSB_SET_MASK(TYPE, N))

// gets mask with set bits in a given range
#define RANGE_BIT_SET_MASK(TYPE, FROM, TO) \
			(N_LSB_SET_MASK(TYPE, (TO - FROM + 1)) << FROM)

// gets mask with clear bits in a given range
#define RANGE_BIT_CLEAR_MASK(TYPE, FROM, TO) \
			(~RANGE_BIT_SET_MASK(TYPE, FROM, TO))

// sets range of bits in a given number
#define RANGE_BIT_SET(NUM, TYPE, FROM, TO) \
			(RANGE_BIT_SET_MASK(TYPE, FROM, TO) | NUM)

// clears range of bits in a given number
#define RANGE_BIT_CLEAR(NUM, TYPE, FROM, TO) \
			(RANGE_BIT_CLEAR_MASK(TYPE, FROM, TO) & NUM)

// prints a long int in binary
void printLongInBin(unsigned long x);
// prints an int in binary
void printIntInBin(unsigned int x);
// prints a char in binary
void printCharInBin(unsigned char x);
// counts the number of bits in a given bits arr
int countSetBits(unsigned char *bitsArr, int size);
// creates a bit array
unsigned char *createBitsArr(int size);
// sets the i bit in a given char
void setBit(unsigned char *pch, int i);
// prints a given char array in binary
void printCharArrInBin(unsigned char *arr, int size);

#endif