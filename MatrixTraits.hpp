#ifndef MATRIXTRAITS_HPP
#define MATRIXTRAITS_HPP

#include <iostream>
#include <functional>
#include <map>
#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <complex>

//I create a struct to introduce the comparison by columns to define the column-wise maps
struct Comparisonbycolumns{
	bool operator()(const std::array<std::size_t,2> & a, const std::array<std::size_t,2> & b) const{
		if (a[1] < b[1]) return true;
        if (a[1] > b[1]) return false;
        // If columns are equal, I compare based on the rows
        return a[0] < b[0];
	}
};
//I have implemented a class MatrixTraits to define the common types to use in my code
class MatrixTraits{
public:
	using Scalar = double; //to comment if you want to use the complex numbers
	//using Scalar = std::complex<double>; //to uncomment if you want to use the complex numbers
	using Matrix_type = std::map<std::array<std::size_t, 2>, Scalar>;
	using Matrix_type_c = std::map<std::array<std::size_t, 2>, Scalar,Comparisonbycolumns>;
	using Vector_type = std::vector<Scalar>;
};

#endif /*MATRIXTRAITS_HPP*/