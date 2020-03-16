//Maria Wyrzykowska
//313924
//KPOK
#include <stdio.h>
int main(){
  int a, b;
  scanf ("%i",&a);
  scanf ("%i",&b);
  if(a==0)
  {
    a++;
  }
  for(int i=a; i<=b; i++)
  {
    if( 2020%i==0 ){
      printf("%i ", i);
    }
  }
  return 0;
}
