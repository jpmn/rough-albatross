#include "MathUtility.h"

namespace baluchon { namespace utilities {

	int MathUtility::min(int n1, int n2, int n3) {
		return (n1 < n2)? (n1 < n3)? n1 : n3 : n2;
	}

	int MathUtility::max(int n1, int n2, int n3) {
		return (n1 > n2)? (n1 > n3)? n1 : n3 : n2;
	}

}};