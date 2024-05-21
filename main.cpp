#include "Matrix.hpp"
#include "MatrixImplementation.hpp"
#include "chrono.hpp"
#include <iostream>

using T=MatrixTraits;
using namespace algebra;
using namespace Timings;



int main(){
	/*//DOUBLE
	//creation of an uncompressed matrix with a row-wise ordering
	Matrix<T, StorageOrder::Row_Wise> mat_r(0,0);
	//I read the matrix in the Matrix Market format
	mat_r.reader_matrices("Insp_131.mtx");

	//creation of an uncompressed matrix with a column-wise ordering
	Matrix<T, StorageOrder::Column_Wise> mat_c(0,0);
	//I read the matrix in the Matrix Market format
	mat_c.reader_matrices("Insp_131.mtx");

	Chrono chrono;
	typename T::Vector_type v(mat_r.get_cols(), 0.0);
	typename T::Vector_type result1;
	//using chrono I measure tha time of the vector multiplication with the row and column wise matrices
	chrono.start();
	result1=vector_mult(mat_r,v);
	chrono.stop();
	//print the time
	std::cout<<"Time for the UNCOMPRESSED MATRIX - ROW-WISE"<<std::endl;
	std::cout<<chrono<<std::endl;

	typename T::Vector_type result2;
	chrono.start();
	result2=vector_mult(mat_c,v);
	chrono.stop();
	//print the time
	std::cout<<"Time for the UNCOMPRESSED MATRIX - COLUMN-WISE"<<std::endl;
	std::cout<<chrono<<std::endl;

	//now I do the same after compressing the matrices
	typename T::Vector_type result3;
	mat_r.compress();
	chrono.start();
	result3=vector_mult(mat_r,v);
	chrono.stop();
	//print the time
	std::cout<<"Time for the COMPRESSED MATRIX - ROW-WISE"<<std::endl;
	std::cout<<chrono<<std::endl;

	typename T::Vector_type result4;
	mat_c.compress();
	chrono.start();
	result4=vector_mult(mat_c,v);
	chrono.stop();
	//print the time
	std::cout<<"Time for the COMPRESSED MATRIX - COLUMN-WISE"<<std::endl;
	std::cout<<chrono<<std::endl;*/

	//CHECK THAT THE FUNCTIONS ARE GOOD ALSO FOR THE COMPLEX NUMBERS
	
	Matrix<T, StorageOrder::Row_Wise> mat_r(2,2);
	mat_r(0,0)=std::complex<double>(1.0,1.0);
	mat_r(0,1)=std::complex<double>(1.0,1.0);
	mat_r(1,0)=std::complex<double>(1.0,1.0);
	mat_r(1,1)=std::complex<double>(1.0,1.0);

	typename T::Vector_type v(2, std::complex<double>(1.0,1.0));
	typename T::Vector_type result1;
	
	Chrono chrono;
	chrono.start();
	result1 = vector_mult(mat_r, v);
	chrono.stop();
	std::cout<<"Time for the UNCOMPRESSED MATRIX - ROW-WISE"<<std::endl;
	std::cout<<chrono<<std::endl;

	Matrix<T, StorageOrder::Column_Wise> mat_c(2,2);
	mat_c(0,0)=std::complex<double>(1.0,1.0);
	mat_c(0,1)=std::complex<double>(1.0,1.0);
	mat_c(1,0)=std::complex<double>(1.0,1.0);
	mat_c(1,1)=std::complex<double>(1.0,1.0);

    // using call const operator - not working
/*    const Matrix<T, StorageOrder::Column_Wise> mat_c_const(mat_c);
    std::cout << "element (0,1) of the complex matrix: " << mat_c_const(0,1) << std::endl; */

	typename T::Vector_type result2;
	chrono.start();
	result2 = vector_mult(mat_r, v);
	chrono.stop();
	std::cout<<"Time for the UNCOMPRESSED MATRIX - COLUMN-WISE"<<std::endl;
	std::cout<<chrono<<std::endl;

	typename T::Vector_type result3;
	mat_r.compress();
	chrono.start();
	result3 = vector_mult(mat_r, v);
	chrono.stop();
	std::cout<<"Time for the COMPRESSED MATRIX - ROW-WISE"<<std::endl;
	std::cout<<chrono<<std::endl;

	typename T::Vector_type result4;
	mat_c.compress();
	chrono.start();
	result4 = vector_mult(mat_r, v);
	chrono.stop();
	std::cout<<"Time for the COMPRESSED MATRIX - COLUMN-WISE"<<std::endl;
	std::cout<<chrono<<std::endl;
	
	
	return 0;
}
