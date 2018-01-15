#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define BLOCK_SIZE 4

float **ma;
float **mb;
float **mc;
int mat_size;
int num_threads = 4;

float** alloc_matrix(int rows, int cols) {
     float **C = (float **)malloc(sizeof(float*)*rows);
     int r;
     for (r = 0; r < rows; ++r) {
	  C[r] = (float *)malloc(sizeof(float)*cols);
     }
     return C;
}

float** rand_matrix(int rows, int cols) {
     int r;
     int c;
     float **C = alloc_matrix(rows, cols);
     for (r = 0; r < rows; ++r) {
	  for (c = 0; c < cols; ++c) {
	       C[r][c] = (rand()+0.0)/(RAND_MAX+0.0);
	  }
     }
     return C;
}

float** mult(float **C,
	     float **A,
	     int a_rows,
	     int a_cols,
	     float **B,
	     int b_rows,
	     int b_cols) {
     int i, j, k;
     int r;
     int nn = 0;
     for (i = 0; i < a_rows; i++) {
	  for(j = 0; j < b_cols; j++) {
	       //C[i][j] = 0;
	       for(k = 0; k < a_cols; k++) {
		    //C[i][j] += A[i][k] * B[k][j];
            //nn++;
	       }
	  } 
     }
     return C;
}

float** mp_mult(float **C,
	     float **A,
	     int a_rows,
	     int a_cols,
	     float **B,
	     int b_rows,
	     int b_cols) {

     int i, j, k;
     int r;
         #pragma omp parallel shared(A, B, C) private(i,j,k)

       #pragma omp for schedule (static) 

     for (i = 0; i < a_rows; i++) {
	  for(j = 0; j < b_cols; j++) {
	       C[i][j] = 0;
	       for(k = 0; k < a_cols; k++) {
		    C[i][j] += A[i][k] * B[k][j];
	       }
	  } 
     }

     return C;
}

double parallelMultiply(float** matrixA, float** matrixB, float** matrixC, int dimension){

	// struct timeval t0, t1;
	// gettimeofday(&t0, 0);
    // int nthreads = omp_get_num_threads();
    // printf("Starting matrix multiple example with %d threads\n",nthreads);
    clock_t start = clock();

	#pragma omp parallel for
	for(int i=0; i<dimension; i++){
       //printf("Thread id is %d, cpu is %d.\n", omp_get_thread_num(), sched_getcpu());
		for(int j=0; j<dimension; j++){
			for(int k=0; k<dimension; k++){
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}
    clock_t end = clock();

	//gettimeofday(&t1, 0);
	float elapsed = (float)(end-start) /CLOCKS_PER_SEC;
    printf("time openmp is %f\n", elapsed);
	return elapsed;
}

void *thread_func(void *arg){
    int tid = *(int*)(arg);
    int i, j, k;
    int start = tid * mat_size / num_threads;
    int end = (tid + 1) * mat_size / num_threads;
    printf("start is %d, end is %d\n", start, end);
    clock_t start_time = clock();
    int nn = 0;
    for (i = start; i < end; i++) {
        for(j = 0; j < mat_size; j++) {
            //mc[i][j] = 0;
            for(k = 0; k < mat_size; k++) {
               //mc[i][j] += ma[i][k] * mb[k][j];
            }
        } 
    }
    clock_t end_time = clock();
    printf("Tid is %d, start is %f, end is %f, time is %f\n", tid, (float)start_time/CLOCKS_PER_SEC, (float)end_time/CLOCKS_PER_SEC, (float)(end_time - start_time)/CLOCKS_PER_SEC);
}

void *thread_func_ikj(void *arg){
    int tid = *(int*)arg;
    int i, j, k;
    int start = tid * mat_size / num_threads;
    int end = (tid + 1) * mat_size / num_threads;


     for (i = start; i < end; i++) {
	   for(k = 0; k < mat_size; k++) {
	       //C[i][j] = 0;
	       for(j = 0; j < mat_size; j++){
		    mc[i][j] += ma[i][k] * mb[k][j];
	       }
	  } 
     }

}

float** para_mult(float **C,
	     float **A,
	     int a_rows,
	     int a_cols,
	     float **B,
	     int b_rows,
	     int b_cols) {

    ma = A;
    mb = B;
    mc = C;
    mat_size = a_rows;
    pthread_t threads[num_threads];
    for(int i = 0; i < num_threads; i++){
        int tid = i;
        pthread_create(&threads[i], NULL, thread_func, (void*)&tid);
    }
    for(int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }
     
}

float** ikj_mult(float **C,
	     float **A,
	     int a_rows,
	     int a_cols,
	     float **B,
	     int b_rows,
	     int b_cols) {
     int i, j, k;
     int r;
     
     for (i = 0; i < a_rows; i++) {
	   for(k = 0; k < a_cols; k++) {
	       //C[i][j] = 0;
	       for(j = 0; j < b_cols; j++){
		    C[i][j] += A[i][k] * B[k][j];
	       }
	  } 
     }

     return C;
}
void *print_message_function( void *ptr )
{
    clock_t start_time = clock();
     char *message;
     message = (char *) ptr;
     printf("%s \n", message);
     clock_t end_time = clock();
    printf("Tid is %d, start is %f, end is %f, time is %f\n", 1, (float)start_time/CLOCKS_PER_SEC, (float)end_time/CLOCKS_PER_SEC, (float)(end_time - start_time)/CLOCKS_PER_SEC);
}
float** para_ikj_mult(float **C,
	     float **A,
	     int a_rows,
	     int a_cols,
	     float **B,
	     int b_rows,
	     int b_cols) {
     ma = A;
    mb = B;
    mc = C;
    mat_size = a_rows;
    pthread_t threads[num_threads];
    for(int i = 0; i < num_threads; i++){
        int *tid;
        tid = (int *) malloc( sizeof(int) );
        *tid = i;
        pthread_create(&threads[i], NULL, thread_func, (void*)tid);
        free(tid);
    }
    for(int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }
    // pthread_t thread1, thread2;
    //  char *message1 = "Thread 1";
    //  char *message2 = "Thread 2";
    //  int  iret1, iret2;

    // /* Create independent threads each of which will execute function */
    // clock_t time1 = clock();
    //  iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);
    //  clock_t time2 = clock();
    //  iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2);
    //  printf("time1 is %f, time2 is %f\n", (float)time1/CLOCKS_PER_SEC, (float)time2/CLOCKS_PER_SEC);

    //  /* Wait till threads are complete before main continues. Unless we  */
    //  /* wait we run the risk of executing an exit which will terminate   */
    //  /* the process and all threads before the threads have completed.   */

    //  pthread_join( thread1, NULL);
    //  pthread_join( thread2, NULL); 

    //  printf("Thread 1 returns: %d\n",iret1);
    //  printf("Thread 2 returns: %d\n",iret2);
     //exit(0);
}



float** block_mult(float **C,
	     float **A,
	     int a_rows,
	     int a_cols,
	     float **B,
	     int b_rows,
	     int b_cols) {

     int i, j, k;
     int n = a_rows;
     for(int kk = 0; kk < n; kk += BLOCK_SIZE){
            for(int jj = 0; jj < n; jj += BLOCK_SIZE){
                for (i = 0; i < n; i++) {
                    for(int j = jj; j < jj + BLOCK_SIZE;j++){
                        float temp = 0;
                        for(int k = kk;k < kk + BLOCK_SIZE;k++){
                             temp += A[i][k] * B[k][j];
                        }
                        C[i][j] += temp;
                    }
                }
            }
        }

     return C;
}