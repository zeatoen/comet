#include "arith.hpp"

std::optional<int> arith::add (int a,int b){
	if (b>=0 && a<std::numeric_limits<int>::max()-b || b<0 && a> std::numeric_limits<int>::min()-b)
	{
		return a+b;
	}
	return std::nullopt;
}
std::optional<int> arith::subtract (int a,int b){
	if (b<0 && a<std::numeric_limits<int>::max()+b || b>=0 && a > std::numeric_limits<int>::min()+b)
	{
		return a+b;
	}
	return std::nullopt;
}
bool will_mul_overflow(int a, int b) {
	if (a == 0 || b == 0) return false;

	if (a == -1 && b == std::numeric_limits<int>::min()) return true;
	if (b == -1 && a == std::numeric_limits<int>::min()) return true;

	    // General checks
	if (a > 0) {
		if (b > 0) return a > std::numeric_limits<int>::max() / b;
		else        return b < std::numeric_limits<int>::min() / a;
	    } else { // a < 0
	    	if (b > 0) return a < std::numeric_limits<int>::min() / b;
	    	else        return a != 0 && b < std::numeric_limits<int>::max() / a;
	    }
	}
std::optional<int> arith::mul (int a,int b){
	if (!will_mul_overflow(a,b))
	{
		return a*b;
	}
	return std::nullopt;
}

