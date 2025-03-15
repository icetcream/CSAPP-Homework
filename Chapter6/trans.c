/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, k, q;
    int bsize = 16;
    for(i = 0; i < N; i += bsize){
        for(j = 0; j < M; j += bsize){
            for(k = i; k < i + bsize && k < N; k++) {
                for(q = j; q < j + bsize && q < M; q++) {
                        B[q][k] = A[k][q];
                }
            }
        }
    }

}


char test4_desc[] = "test";
void solve_61_67(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, k, q;
    int bsize = 16;
    for(i = 0; i < N; i += bsize){
        for(j = 0; j < M; j += bsize){
            for(k = i; k < i + bsize && k < N; k++) {
                for(q = j; q < j + bsize && q < M; q++) {
                        B[q][k] = A[k][q];
                }
            }
        }
    }

}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

    

}


char test_desc[] = "test";
void transpose_test(int M, int N, int A[N][M], int B[M][N]){
    int i, j, k, q;
    int bsize = 8;
    int C[8];
    for(i = 0; i < N; i += bsize){
        for(j = 0; j < M; j += bsize){
            for(k = i; k < i + bsize && k < N; k++) {
                for(q = j; q < j + bsize && q < M; q++) {
                    if(q!=k){
                        B[q][k] = A[k][q];
                    }
                    else{
                        C[k] = A[k][q];
                    }
                }
            }
        }
        for(k = i; k < i + bsize && k < N&&k < M; k++) {
            B[k][k] = C[k];
        }
    }
}

char test2_desc[] = "test";
void solve_32(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;
    //大致计算一下，一个对角块中，每行是1次命中，列是第一次8miss，后面每一次都是1miss，所以对角块是23miss
    //非对角块是16miss，23*4+16*12 = 284
    for (i = 0; i < 32; i += 8) {     
        for (j = 0; j < 32; j += 8) {  

            for (int cnt = 0; cnt < 8; ++cnt, ++i) {  
                int temp1 = A[i][j];                  
                int temp2 = A[i][j + 1];
                int temp3 = A[i][j + 2];
                int temp4 = A[i][j + 3];
                int temp5 = A[i][j + 4];
                int temp6 = A[i][j + 5];
                int temp7 = A[i][j + 6];
                int temp8 = A[i][j + 7];

                B[j][i] = temp1; 
                B[j + 1][i] = temp2;
                B[j + 2][i] = temp3;
                B[j + 3][i] = temp4;
                B[j + 4][i] = temp5;
                B[j + 5][i] = temp6;
                B[j + 6][i] = temp7;
                B[j + 7][i] = temp8;
            }
            i -= 8;
        }
    }
}

char test3_desc[] = "test";
void solve_64(int M, int N, int A[N][M], int B[M][N])
{
    int i,j,k;
    int a0,a1,a2,a3,a4,a5,a6,a7;
    for(i = 0; i < N; i += 8){
        for(j = 0; j < M; j += 8){
            for(k = i;k < i+4;k ++){
                a0 = A[k][j];
                a1 = A[k][j+1];
                a2 = A[k][j+2];
                a3 = A[k][j+3];
                a4 = A[k][j+4];
                a5 = A[k][j+5];
                a6 = A[k][j+6];
                a7 = A[k][j+7];

                B[j][k] = a0;
                B[j+1][k] = a1;
                B[j+2][k] = a2;
                B[j+3][k] = a3;

                B[j][k+4] = a4;
                B[j+1][k+4] = a5;
                B[j+2][k+4] = a6;
                B[j+3][k+4] = a7;
            }
            for (int k = j; k < j + 4; k++){
                // 得到B的第2块
                a0 = B[k][i + 4];
                a1 = B[k][i + 5];
                a2 = B[k][i + 6];
                a3 = B[k][i + 7];
                // 得到A的第3块
                a4 = A[i + 4][k];
                a5 = A[i + 5][k];
                a6 = A[i + 6][k];
                a7 = A[i + 7][k];
                // 复制给B的第2块
                B[k][i + 4] = a4;
                B[k][i + 5] = a5;
                B[k][i + 6] = a6;
                B[k][i + 7] = a7;
                // B原来的第2块移动到第3块
                B[k + 4][i + 0] = a0;
                B[k + 4][i + 1] = a1;
                B[k + 4][i + 2] = a2;
                B[k + 4][i + 3] = a3;
            }

            for(k = i+4;k < i+8;k ++){
                a0 = A[k][j+4];
                a1 = A[k][j+5];
                a2 = A[k][j+6];
                a3 = A[k][j+7];

                B[j+4][k] = a0;
                B[j+5][k] = a1;
                B[j+6][k] = a2;
                B[j+7][k] = a3;
            }
        }
    }
}
/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    registerTransFunction(trans, trans_desc); 

    
    registerTransFunction(solve_32, test2_desc); 

    registerTransFunction(solve_64, test3_desc); 

    registerTransFunction(solve_61_67, test4_desc); 
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

