#pragma once
#include <sstream>
#include <boost/multiprecision/cpp_dec_float.hpp>

auto calculator(std::stringstream& in) -> boost::multiprecision::cpp_dec_float_100;