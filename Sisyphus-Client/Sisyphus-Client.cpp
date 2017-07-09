// Sisyphus-Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "board.h"
#include <iostream>
int main()
{
	init_board();
	is_attacked(42, White);
	std::cin.get();
}

