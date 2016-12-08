#pragma once
//____________________REFERENCES___________________________

//_____________________DEFINES_____________________________

//____________________INCLUDES_____________________________

//____________________STRUCTURES___________________________

//___________________PROTOTYPES____________________________
int checkBit(unsigned int number, int idx) {
	unsigned int mask = 1;
	mask <<= idx;
	number &= mask;
	number >>= idx;
	return number;
}