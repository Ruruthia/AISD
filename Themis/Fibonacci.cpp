#include<stdio.h>

long long* mmult(long long A[], long long B[], int m){
  long long* C = new long long[4];
  C[0]=((A[0]*B[0])+(A[1]*B[2]))%m;
  C[1]=((A[0]*B[1])+(A[1]*B[3]))%m;
  C[2]=((A[2]*B[0])+(A[3]*B[2]))%m;
  C[3]=((A[2]*B[1])+(A[3]*B[3]))%m;
  return C;
}

long long* square(long long A[], int m)
{
    return mmult(A,A,m);
}

long long* power(long long matrix[], int n, int m){
  if(n==1){
    return matrix;
  }
  else if(n%2){
    return mmult(matrix, square(power(matrix, (n-1)/2, m),m), m);
  }
  else{
    return square(power(matrix, n/2, m), m);
  }
}


int fib(int n, int m){
  int fib;
  long long * matrix = new long long[4];
  matrix[0]=1;
  matrix[1]=1;
  matrix[2]=1;
  matrix[3]=0;
  matrix=power(matrix, n, m);
  fib=matrix[1];
  return fib;
}

int main(){
  int start[4]={1,1,1,0};
  int tests, n, m;

  scanf("%i", &tests);
  for(int i=0; i<tests; i++){
  scanf("%i %i", &n, &m);
  printf("%i\n", fib(n,m));
  }

  return 0;
}
