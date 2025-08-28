#ifndef ARITH_HPP
#define ARITH_HPP 
#include <optional>
#include<limits>
namespace arith{
	std::optional<int> add (int a,int b);
	std::optional<int> subtract (int a,int b);
	std::optional<int> mul (int a,int b);
}
#endif