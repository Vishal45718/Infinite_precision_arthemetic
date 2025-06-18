#include <iostream>
#include <string>
#include "integer1.hh"
#include "float1.hh"
int main(int argc, char** argv)
{
	if(argc != 5)
	{
		std::cout << "Invalid input\n";
		return 1;
	}
	std::string type = argv[1];
	std::string operation = argv[2];
	std::string o1 = argv[3];
	std::string o2 = argv[4];
	if(type == "int")
	{
		InfiniteArithmetic::Integer A(o1);
		InfiniteArithmetic::Integer B(o2);
		if(operation == "add")
			displayInteger(A+B);
		else if(operation == "sub")
			displayInteger(A-B);
		else if(operation == "mul")
			displayInteger(A*B);
		else if(operation == "div")
			displayInteger(A/B);
		else
		{
			std::cout << "Please enter valid operator.\n";
			return 1;
		}
	}
	else if(type == "float")
	{
		InfiniteArithmetic::Float A(o1);
		InfiniteArithmetic::Float B(o2);
		if(operation == "add")
                        displayFloat(A+B);
                else if(operation == "sub")
                        displayFloat(A-B);
                else if(operation == "mul")
                        displayFloat(A*B);
                else if(operation == "div")
                        displayFloat(A/B);
                else
		{
                        std::cout << "Please enter valid operator.\n";
			return 1;
		}
        }
	else
	{
		std::cout << "Please enter valid type(int or float).\n";
		return 1;
	}
	return 0;
}
