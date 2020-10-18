#pragma once
#include <string>

std::string str_to_upr(std::string string) // male pismenka na velke
{
	for (int i = 0; i < (int)string.length(); i++)
	{
		if (string[i] >= 97 && string[i] <= 122)
			string[i] = string[i] - 32;
	}

	return string;
}

std::string str_to_lwr(std::string string)
{
	for (int i = 0; i < (int)string.length(); i++) // velke pismenka na male
	{
		if (string[i] >= 65 && string[i] <= 90)
			string[i] = string[i] + 32;
	}

	return string;
}