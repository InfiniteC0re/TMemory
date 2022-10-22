#include "TMemory.h"
#include <iostream>

struct MyStruct
{
	float a;
	float b;
	float c;
	float d;
	float e;
	float f;
};

int main(int argc, char** argv)
{
	Toshi::TMemory mem;
	mem.Init();

	MyStruct* myStruct = (MyStruct*)TCalloc(2, sizeof(MyStruct));
	myStruct[0].a = 9;
	myStruct[1].c = 8;

	std::cout << myStruct << std::endl;
	TFree(myStruct);
	
	std::cin.get();

	return 0;
}