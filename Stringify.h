#ifndef __STRINGIFY_H__
#define __STRINGIFY_H__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class CStringify
{
public:
	static std::string Int(int x);
	static std::string Char(char* x);
	static std::string Float(float x);
	static std::string Double(double x);

	static int ToInt(const std::string& String);
	static float ToFloat(const std::string& String);
	static double ToDouble(const std::string& String);

	static std::vector<std::string> Explode(std::string str, const std::string& separator);
};

#endif
