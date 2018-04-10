#include<iostream>
int main(int argc, char** argv)
{
	union
	{
		short s;
		char c[sizeof(short)];
	} un;
	un.s = 0x0102;

	if (sizeof(short) == 2)
	{
		if (un.c[0] == 1 && un.c[1] == 2)
			std::cout << "big-endian" << std::endl;
		else if (un.c[0] == 2 && un.c[1] == 1)
			std::cout << "little-endian" << std::endl;
		else
			std::cout << "unlnown" << std::endl;
	}
	else
		std::cout << "sizeof(short) = " << sizeof(short) << std::endl;
	return 0;
}