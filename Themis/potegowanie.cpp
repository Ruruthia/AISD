#include<stdio.h>

long long power(long long a, long long b, int m){
  if(b==0){
    return 1;
  }
  else if(b%2){
    return ((a*power(a, (b-1)/2, m)%m)*power(a, (b-1)/2, m)%m);
  }
  else{
    return(power(a, b/2, m)%m*power(a, b/2, m)%m)%m;
  }
}


int main(){
  int tests;
  int a, b, m;
  scanf("%i", &tests);
  for(int i=0; i<tests; i++){
    scanf("%i %i %i", &a, &b, &m);
    printf("%lld \n", power(a,b,m));
  }
  return 0;
}
