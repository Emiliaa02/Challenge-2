#ifndef MATRIXIMPLEMENTATION_HPP
#define MATRIXIMPLEMENTATION_HPP

#include "Matrix.hpp"

namespace algebra{

//definition of the constructor
template<typename T,StorageOrder Order>
Matrix<T, Order>::Matrix(std::size_t rows, std::size_t columns){
	//I resize the matrix
	resize_matrix(rows, columns);
}

//method to resize the matrix. I need it in the constructor
template<typename T,StorageOrder Order>
void Matrix<T, Order>::resize_matrix(std::size_t rows, std::size_t columns){
	if(Order == StorageOrder::Row_Wise){
		//I always create the matrix in the uncompressed state
		if(is_compressed()){
			uncompress();
		}
		if(rows < m_rows || columns < m_cols){
			for(auto it=m_mat.begin(); it!=m_mat.end(); ++it){
				//I erase the elements with an index of row or an index of column out of the new bounds
				if(it->first[0] >= rows || it->first[1] >= columns)
					m_mat.erase(it);
			}	
		}
	}
	else{
		//I always create the matrix in the uncompressed state
		if(is_compressed()){
			uncompress();
		}
		if(rows < m_rows || columns < m_cols){
			for(auto it=m_mat_c.begin(); it!=m_mat_c.end(); ++it){
				//I erase the elements with an index of row or an index of column out of the new bounds
				if(it->first[0] >= rows || it->first[1] >= columns)
					m_mat_c.erase(it);
			}	
		}
	}
	//I set m_rows and m_cols using the current numbers of rows and columns
	m_rows = rows;
	m_cols = columns;
}

//definition of the method to compress an uncompressed matrix
template<typename T, StorageOrder Order>
void Matrix<T, Order>::compress(){
	//first I check if it is uncompressed or not
	if(!is_compressed()){
		std::size_t count=0;
		if(Order == StorageOrder::Row_Wise){
			inner.resize(m_rows+1);
			inner[0] = 0;	
			for(std::size_t i=0; i < m_rows; ++i){
				for(std::size_t j=0; j < m_cols; ++j){
					auto it = m_mat.find({i,j});
					if(it!=m_mat.end()){
						outer.push_back(j);
						values.push_back(it->second);
						count++;
					}
				}
				inner[i+1] = count;
			}
			//after populating the three vectors, I empty the matrix
			m_mat.clear();
		}
		else{
			inner.resize(m_cols+1);
			inner[0] = 0;
			for(std::size_t j=0; j < m_cols; ++j){
				for(std::size_t i=0; i < m_rows; ++i){
					auto it = m_mat_c.find({i,j});
					if(it!=m_mat_c.end()){
						outer.push_back(i);
						values.push_back(it->second);
						count++;
					}
				}
				inner[j+1] = count;
			}
			//after populating the three vectors, I empty the matrix
			m_mat_c.clear();
		}
		//I set the bool variable uncompressed as false
		uncompressed = false;
	}
}

//definition of the method to uncompress a compressed matrix
template<typename T, StorageOrder Order>
void Matrix<T, Order>::uncompress(){
	//fist I check if it is compressed or not
	if(is_compressed()){
		if(Order == StorageOrder::Row_Wise){
			resize_matrix(m_rows, m_cols);
			for(std::size_t i=0; i < m_rows; ++i){
				for(std::size_t k=inner[i]; k<inner[i+1]; ++k){
					std::array<std::size_t, 2> v = {i,outer[k]};
					m_mat[v]=values[k];
				}
			}
		}
		else{
			resize_matrix(m_rows, m_cols);
			for(std::size_t j=0; j < m_cols; ++j){
				for(std::size_t k=inner[j]; k<inner[j+1]; ++k){
					std::array<std::size_t, 2> v = {outer[k],j};
					m_mat_c[v]=values[k];
				}
			}
		}
	//after populating the map I empy the three vectors of the compressed state
	inner.clear();
	outer.clear();
	values.clear();
	//I set the bool variable uncompressed as true
	uncompressed = true;
	}		
}

//bool method to understand if the matrix is compressed or uncompressed
template<typename T, StorageOrder Order>
bool Matrix<T, Order>::is_compressed() const{
	return !uncompressed;
}

//bool method to check if the two indexes are in range or out of bounds
template<typename T, StorageOrder Order>
bool Matrix<T, Order>::in_range(std::size_t i, std::size_t j){
	return i<m_rows && j<m_cols;  
}

//const version of the call operator
template<typename T, StorageOrder Order>
typename T::Scalar& Matrix<T, Order>::operator()(std::size_t i, std::size_t j) const{
	//I create a static variable to return in the default cases
	static typename T::Scalar def;
	//First we check if the indexes are in range or not
	if(in_range(i,j)){
		if(!is_compressed()){
			if(Order==StorageOrder::Row_Wise){
				auto it = m_mat.find({i,j});
				//if I don't find the indexes in the map, I return a default value
				if(it==m_mat.cend()){
					return def;
				}
				//if I find it I return the value
				else
					return it->second;
			}
			//the same for the column-wise matrix
			else{
				auto it = m_mat_c.find({i,j});
				if(it==m_mat_c.cend()){
					return def;
				}	
				else
					return it->second;
			}
		}
		//Now I do the same for compressed state both for the row-wise and the column-wise ordering
		else{
			if(Order == StorageOrder::Row_Wise){
				for(std::size_t k=inner[i]; k<inner[i+1]; ++k){
					if(outer[k]==j){
						return values[k];
					}
				}
				return def;
			}
			else{
				for(std::size_t k=inner[j]; k<inner[j+1]; ++k){
					if(outer[k]==i){
						return values[k];
					}
				}
				return def;
			}
		}
	}
	else{
		//if the indexes are out of bounds I print a runtime error
		throw std::runtime_error("Out of bounds");
	}	
}


//non const version of the call operator
template<typename T, StorageOrder Order>
typename T::Scalar& Matrix<T, Order>::operator()(std::size_t i, std::size_t j){
	//if the indexes are out of bounds I print a runtime error
	if(!in_range(i,j)){
		throw std::runtime_error("Out of bounds");
	}
	if(!is_compressed()){
		if(Order == StorageOrder::Row_Wise){
			auto it = m_mat.find({i,j});
			if(it==m_mat.end()){
				//if I don't find the indexes in the map, I add them with a default value
				std::array<std::size_t, 2> v={i,j};
				return m_mat[v];
			}
			else{
				//if I find the indexes in the map, I return the corrensponding value
				return it->second;
			}
		}
		else{
			auto it = m_mat_c.find({i,j});
			if(it==m_mat_c.end()){
				//if I don't find the indexes in the map, I add them with a default value
				std::array<std::size_t, 2> v={i,j};
				return m_mat_c[v];
			}
			else{
				//if I find the indexes in the map, I return the corrensponding value
				return it->second;
			}
		}
	}
	//I do the same for the compressed state, but if I don't find the indexes I return a default value
	else{
		if(Order == StorageOrder::Row_Wise){
			for(std::size_t k=inner[i]; k<inner[i+1]; ++k){
				if(outer[k]==j){
					return values[k];
				}
			}
			static typename T::Scalar def;
			return def;
		}
		else{
			for(std::size_t k=inner[j]; k<inner[j+1]; ++k){
				if(outer[k]==i){
					return values[k];
				}
			}
			static typename T::Scalar def;
			return def;
		}
	}
}

//method to read a matrix in the Market matrix format
template<typename T, StorageOrder Order>
	void Matrix<T, Order>::reader_matrices(const std::string& filename){
		//local variables
		std::size_t rows; 
		std::size_t columns;
		std::size_t nonzeroes;
		std::size_t i;
		std::size_t j;
		double value;
		std::ifstream data(filename);
		std::string line;
		std::getline(data,line);

		//I go throw all the commented rows
		while(line[0] == '%'){
			std::getline(data, line);
		}

		//I create a stream in which saving the different lines of the file one by one
		std::istringstream data_s(line);
		data_s >> rows >> columns >> nonzeroes;
		resize_matrix(rows, columns);

		//reading the lines of the files I add the elements to the map both in the row-wise and in the column-wise ordering
		if(Order == StorageOrder::Row_Wise){
			for(std::size_t cont=0; cont<nonzeroes; ++cont){
				std::getline(data, line);
				std::istringstream data_s(line);
				data_s >> i >> j >> value;
				std::array<std::size_t, 2> v= {i-1,j-1};
				m_mat[v]=value;
			}
		}
		else{
			for(std::size_t cont=0; cont<nonzeroes; ++cont){
				std::getline(data, line);
				std::istringstream data_s(line);
				data_s >> i >> j >> value;
				std::array<std::size_t, 2> v= {i-1,j-1};
				m_mat_c[v]=value;
			}
		}
	}
};

#endif /*MATRIXIMPLEMENTATION_HPP*/
