#pragma once

namespace baluchon { namespace utilities {

class MathUtility
{
public:
	template <typename T>
	static T min(T n1, T n2, T n3) {
		return std::min(n1, std::min(n2, n3));

		//return ((n1 < n2)? ((n1 < n3)? n1 : n3) : ((n2 < n3)? n2 : n3));
	}

	template <typename T>
	static T max(T n1, T n2, T n3) {
		/*if (n1 > n2)
			if (n1 > n3)
				return n1;
			else
				return n3;
		else if (n2 > n3)
			return n2;
		else //if (n3 > n1)
			return n3;
		*/
		return std::max(n1, std::max(n2, n3));

		//return ((n1 > n2)? ((n1 > n3)? n1 : n3) : ((n2 > n3)? n2 : n3));
	}

private:
	MathUtility(void) {};
	~MathUtility(void) {};
};

}};