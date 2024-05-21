#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "MatrixTraits.hpp"

namespace algebra{
	//define the enumerator for the type of storage of the Matrix
	enum class StorageOrder {
		Row_Wise,
		Column_Wise
	};

    // Declaration of the class Matrix
	template<typename T, StorageOrder Order>
	class Matrix;

    //Declaration of the vector_mult operator
    template<typename T, StorageOrder Order>
    typename T::Vector_type vector_mult(Matrix<T,Order> A, const typename T::Vector_type& v);

	template<typename T, StorageOrder Order>
	class Matrix{
	public:
		//constructor
		Matrix(std::size_t rows, std::size_t columns);
		struct Comparisonbycolumns{
			bool compare(const std::array<std::size_t,2> & a, const std::array<std::size_t,2> & b);
		};
		//public methods
		//function that converts to a compressed sparse matrix
		void compress();
		//function that converts to a uncompressed sparse matrix
		void uncompress();
		//function that verifies if a matrix is compressed
		bool is_compressed() const;
		//call operators const and not const
		typename T::Scalar& operator()(std::size_t i, std::size_t j) const;
		typename T::Scalar& operator()(std::size_t i, std::size_t j);
		//multipication between two matrices
		typename T::Matrix_type& matrix_mult(const typename T::Matrix_type& A, const typename T::Matrix_type& B);
		//declaration of the friend function for the product between a matrix and a vector
		friend typename T::Vector_type vector_mult<T, Order>(Matrix<T,Order> A, const typename T::Vector_type& v);		//reader of the matrices in the matrix market format
		void reader_matrices(const std::string& filename);
		//getter
		std::size_t get_rows(){
			return m_rows;
		}
		std::size_t get_cols(){
			return m_cols;
		}

	//declaration of the private members
	private:
		//private method to resize the matrix
		void resize_matrix(std::size_t rows, std::size_t columns);
		//private method to check that the indexes are in the bound
		bool in_range(std::size_t i, std::size_t j);
		//number of rows
		std::size_t m_rows;
		//number of columns
		std::size_t m_cols;
		//matrix in uncompressed format by rows 
		typename T::Matrix_type m_mat;
		//matrix in uncompressed format by columns 
		typename T::Matrix_type_c m_mat_c;
		//bool variable to understand if the matrix is compressed or uncompressed
		bool uncompressed = true;
		//vectors for the compressed format of the matrix
		std::vector<std::size_t> inner;
		std::vector<std::size_t> outer;
		std::vector<typename T::Scalar> values;
	};

}

#endif /*MATRIX_HPP*/
