#include <stdint.h>
	#include <stdbool.h>

	//Bit 7: refresh bit
	//Bit 6: opacity bit
	//Bits 5-0: 6 bits mapping to colors
	#define WHITE 0xFF
	#define BLACK 0xC0
	#define CLEAR 0x00
	#define SKY 0xC1
	#define BROWN 0xC2
	#define PEACH 0xC3
	#define ORANGE 0xC4
	#define LIGHT_GREEN 0xC5
	#define GREEN 0xC6
	#define OLIVE 0xC7
	#define RED 0xC8
	#define BLUE 0xC9
	#define DARK_BROWN 0xCA

	#define WHITE_16 0xFFFF
	#define BLACK_16 0x0020
	#define CLEAR_16 0x0000
	#define SKY_16 0xFCAB
	#define BROWN_16 0x0273
	#define PEACH_16 0xC67F
	#define ORANGE_16 0x24FC
	#define LIGHT_GREEN_16 0x16B0
	#define GREEN_16 0x0560
	#define OLIVE_16 0x036D
	#define RED_16 0x21B6
	#define BLUE_16 0xFDE7
	#define DARK_BROWN_16 0x9120 //TODO

	//Return bit 7 (refresh bit)
	bool getRefresh(char pixel);

	//Returns bit 6 (opacity bit)
	bool getOpacity(char pixel);

	//Returns RGB565 color
	uint16_t getColor_16(char pixel);
