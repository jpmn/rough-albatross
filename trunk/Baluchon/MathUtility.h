#pragma once

namespace baluchon { namespace utilities {

class MathUtility
{
public:
	static int min(int n1, int n2, int n3);
	static int max(int n1, int n2, int n3);

private:
	MathUtility(void) {};
	~MathUtility(void) {};
};

}};