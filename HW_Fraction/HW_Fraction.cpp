
#include <iostream>
#include "Fraction.h"

int main()
{
	//Fraction testS(10, 12);
	//testS.save("test.txt");
	Fraction lTest(40, 50);
	lTest.load("test.txt");
	lTest.show();
}