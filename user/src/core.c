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
