#include "head.h"
void words2Str(u16 value, char str[5])
{
	int i = 4;
	while (value) {
		str[i--] = (char)(value % 10 + 48);
		value /= 10;
	}
	while (i > -1) str[i--] = 48;
}

void Uint8toStr(u8 value, char str[2])
{
	char low = value & 0x0f;
	char up = ((value & 0xf0) >> 4);
	low = low <= 9 ? low + 48 : low + 55;
	up = up <= 9 ? up + 48 : up + 55;
	str[0] = up;
	str[1] = low;
	return;
}
