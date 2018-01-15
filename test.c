#include"matrix.h"
#include"stdio.h"
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define N 1
#define T 14
void print_matrix(float **m, int rows, int cols) {
     int r,c;
	  
     printf("[ ");
     for (r = 0; r < rows; r++) {
	  printf("[ ");
	  for (c = 0; c < cols; c++) {
	       printf("%f", m[r][c]);
	       if (c != cols -1 ) {
		    printf(", ");
	       }
	  }
	  printf(" ]\n");
     }
     printf("]\n");
     
}

float measure_time(int size){
    
    float time_sum = 0;
    float b_time_sum = 0;
    float ikj_time_sum = 0;
    float para_time_sum = 0;
    float para_ikj_time_sum = 0;
    for(int i = 0; i < N; i++){
        float **a = rand_matrix(size,size);
        float **b = rand_matrix(size,size);
        float **c = alloc_matrix(size,size);
        float **d = alloc_matrix(size,size);
        float **e = alloc_matrix(size,size);
        float **f = alloc_matrix(size,size);
        float **g = alloc_matrix(size,size);
        clock_t start = clock();
        mult(c, a,size,size,b,size,size); 
        clock_t end = clock();
        time_sum += (float)(end - start)/CLOCKS_PER_SEC;
        //printf("time sum is %f\n", time_sum);
        clock_t b_start = clock();
        block_mult(d, a,size,size,b,size,size); 
        clock_t b_end = clock();
        b_time_sum += (float)(b_end - b_start)/CLOCKS_PER_SEC;

        clock_t ikj_start = clock();
        ikj_mult(e, a,size,size,b,size,size); 
        clock_t ikj_end = clock();
        ikj_time_sum += (float)(ikj_end - ikj_start)/CLOCKS_PER_SEC;

        clock_t para_mult_start = clock();
        parallelMultiply(f, a,b,size); 
        clock_t para_mult_end = clock();
        para_time_sum += (float)(para_mult_end - para_mult_start)/CLOCKS_PER_SEC;

        clock_t para_ikj_start = clock();
        para_ikj_mult(g, a,size,size,b,size,size); 
        clock_t para_ikj_end = clock();
        para_ikj_time_sum += (float)(para_ikj_end - para_ikj_start)/CLOCKS_PER_SEC;


        // print_matrix(a, size, size);
        // print_matrix(b, size, size);
        // print_matrix(c, size, size);
        // print_matrix(d, size, size);
        // print_matrix(e, size, size);
        free(c);
        free(d);
        free(e);
        free(f);
        free(g);
    }
    printf("%f %f %f %f %f\n", (float) time_sum/(float)N, (float) b_time_sum/(float)N, (float) ikj_time_sum/(float)N, (float) para_time_sum/(float)N, (float) para_ikj_time_sum/(float)N);
    return (float) time_sum/(float)N;
    
}

int main(int argc, char *argv[]) {

    float time_arr[9] ;
    for(int i = 2; i <= T; i++){
        int size = (int)pow(2, i);
        float time = measure_time(size);
        time_arr[i-2] = time;
    }
    for(int i = 0; i < T - 1; i++){
        printf("%f\n", time_arr[i]);
    }
    for(int i = 0; i < T - 1; i++){
        printf("Size is %d * %d, time is %f.\n", (int)pow(2, i+2), (int)pow(2, i+2), time_arr[i]);
    }

    

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
