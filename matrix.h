#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED

float** mult(float **C,
	     float **A,
	     int a_rows,
	     int a_cols,
	     float **B,
	     int b_rows,
		 int b_cols);

float** block_mult(float **C,
	     float **A,
	     int a_rows,
	     int a_cols,
	     float **B,
	     int b_rows,
		 int b_cols);
			  
float** ikj_mult(float **C,
	     float **A,
	     int a_rows,
	     int a_cols,
	     float **B,
	     int b_rows,
	     int b_cols);

float** para_mult(float **C,
	     float **A,
	     int a_rows,
	     int a_cols,
	     float **B,
	     int b_rows,
		 int b_cols);

float** para_ikj_mult(float **C,
	     float **A,
	     int a_rows,
	     int a_cols,
	     float **B,
	     int b_rows,
	     int b_cols);
float** mp_mult(float **C,
	     float **A,
	     int a_rows,
	     int a_cols,
	     float **B,
	     int b_rows,
	     int b_cols);

		 double parallelMultiply(float** matrixA, float** matrixB, float** matrixC, int dimension);
			  

float **rand_matrix(int rows, int cols);

float **alloc_matrix(int rows, int cols);

#endif
