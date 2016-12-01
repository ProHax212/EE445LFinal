#include "Color.h"

	//Returns bit 7 (refresh bit)
	bool getRefresh(char pixel){
		return pixel & 0x80;
	}

	//Returns bit 6 (opacity bit)
	bool getOpacity(char pixel){
		return pixel & 0x40;
	}

	//Maps 8 bit colors to 16 bit colors
	uint16_t getColor_16(char pixel){
		switch(pixel){
			case (char) WHITE:
				return WHITE_16;
			case (char) BLACK:
				return BLACK_16;
			case (char) SKY:
				return SKY_16;
			case (char) BROWN:
				return BROWN_16;
			case (char) PEACH:
				return PEACH_16;
			case (char) ORANGE:
				return ORANGE_16;
			case (char) LIGHT_GREEN:
				return LIGHT_GREEN_16;
			case (char) GREEN:
				return GREEN_16;
			case (char) OLIVE:
				return OLIVE_16;
			case (char) RED:
				return RED_16;
			case (char) BLUE:
				return BLUE_16;
			default:
				return CLEAR_16;
		}
	}
