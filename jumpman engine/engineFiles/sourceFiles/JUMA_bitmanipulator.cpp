#include "stdafx.h"
#include <JUMA_bitmanipulator.h>

int checkBit(unsigned int number, int idx) {
	unsigned int mask = 1;
	mask <<= idx;
	number &= mask;
	number >>= idx;
	return number;
}