#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int mat_size = 1024;
int num_threads = 4;
void *thread_func(void *arg){
    // int tid = *(int*)(arg);
    int i, j, k;
    // int start = tid * mat_size / num_threads;
    // int end = (tid + 1) * mat_size / num_threads;
    //printf("start is %d, end is %d\n", start, end);
    clock_t start_time = clock();
    for (i = 0; i <1024; i++) {
        for(j = 0; j < 1024; j++) {
            for(k = 0; k < 1024; k++) {
            }
        } 
    }
    clock_t end_time = clock();
    printf("Tid is %d, start is %f, end is %f, time is %f\n", 111, (float)start_time/CLOCKS_PER_SEC, (float)end_time/CLOCKS_PER_SEC, (float)(end_time - start_time)/CLOCKS_PER_SEC);
}

int main(int argc, char *argv[]) {

    pthread_t threads[num_threads];
    for(int i = 0; i < num_threads; i++){
        int *tid;
        tid = (int *) malloc( sizeof(int) );
        *tid = i;
        pthread_create(&threads[i], NULL, thread_func, (void*)tid);
        //free(tid);
    }
    for(int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }

    clock_t start_time = clock();
    // int nn = 0;
    for (int i = 0; i < mat_size; i++) {
        for(int j = 0; j < mat_size; j++) {
            //mc[i][j] = 0;
            for(int k = 0; k < mat_size; k++) {
               //mc[i][j] += ma[i][k] * mb[k][j];
            }
        } 
    }
    clock_t end_time = clock();
    printf("Tid is %d, start is %f, end is %f, time is %f\n", 1, (float)start_time/CLOCKS_PER_SEC, (float)end_time/CLOCKS_PER_SEC, (float)(end_time - start_time)/CLOCKS_PER_SEC);

    // float time_arr[9] ;
    // for(int i = 2; i <= T; i++){
    //     int size = (int)pow(2, i);
    //     float time = measure_time(size);
    //     time_arr[i-2] = time;
    // }
    // for(int i = 0; i < T - 1; i++){
    //     printf("%f\n", time_arr[i]);
    // }
    // for(int i = 0; i < T - 1; i++){
    //     printf("Size is %d * %d, time is %f.\n", (int)pow(2, i+2), (int)pow(2, i+2), time_arr[i]);
    // }

    

    //  float **a = rand_matrix(4,4);
    //  float **b = rand_matrix(4,4);
    //  float **c = alloc_matrix(4,4);

    //  mult(c, a,4,4,b,4,4);

    //  print_matrix(c, 4,4);

     
    //  a = rand_matrix(4,2);
    //  b = rand_matrix(2,4);
    //  mult(c, a,4,2,b,2,4);
    //  print_matrix(c, 4,4);
    //  free(c);

    //  float **a2 = alloc_matrix(2, 2);
    //  float **b2 = alloc_matrix(2, 2);

    //  a2[0][0] = 1;
    //  a2[0][1] = 0;
    //  a2[1][0] = 0;
    //  a2[1][1] = 1;

    //  b2[0][0] = 0;
    //  b2[0][1] = 1;
    //  b2[1][0] = 1;
    //  b2[1][1] = 0;

    //  c = alloc_matrix(2,2);
     
    //  mult(c, a2, 2, 2,
	//       b2, 2, 2);
    //  print_matrix(c, 2,2);
    //  free(c);

    //  /*
    //  c = mult([[2,0],
	//        [0,2]], 2, 2,
	//       [[2,0],
	//        [0,2]], 2, 2);
    //  print_matrix(c, 2,2);
    //  free(c);*/

}