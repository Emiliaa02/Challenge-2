# Challenge-2

The purpose of this code is to compare the different methods that we can use to store a sparse matrix in the memory, based on its ordering (ROW_WISE or COLUMN-WISE) and on the type of storage inside the memory (Compressed or Uncompressed, as defined in the text of the Challenge). To introduce the comparison by columns in the Uncompressed state (std::map<std::array<std::size_t, 2>, T::Scalar>) I have used a struct defined in the MatrixTraits.hpp header file. 
In particular, in my code I have compared the speed in computing the product between a vector and the sparse matrix in the various formats.
The output obtained is the list of the different performance times and we can conclude that this operation is faster if we have the matrix in the compressed format (both row-wise and column-wise).

Firsty, the matrix is read from a file in which it is saved in a Matrix Market format, through the reader_matrices method, and is saved in an uncompressed state; then the multiplication for a vector is done (NOTE: before doing this I have checked that the sizes are compatible, so that the number of columns of the matrix is equal to the number of rows of the vector).
To do this I have used the templates. Specifically, I have defined the most involved types in an header file called MatrixTraits.hpp and I have used them in the other header files Matrix.hpp and MatrixImplementation.hpp to implement the various methods. All the methods are implemented for the four formats of the matrix.


TO RUN MY CODE, you have just to clone my repository and write: 

git clone git@github.com:Emiliaa02/Challenge-2.git

make

./main


VERSION WITH THE COMPLEX NUMBERS

The code works also if we use the complex numbers instead of the double. To do this it is necessary to include the complex library,to comment in MatrixTraits.hpp row 26 (using Scalar = double;) and uncomment row 27 (using Scalar = std::complex<double>;).
Moreover, if you want to test the code with the complex you have to comment the current rows in the main.cpp (corrensponding to the part "//DOUBLE") and uncomment the ones corrensponding to the part "/*CHECK THAT THE FUNCTIONS ARE GOOD ALSO FOR THE COMPLEX NUMBERS".




