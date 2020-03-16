#include<stdio.h>
#define N 1000005

int binarySearchCount(int arr[], int n, int key)
{
  if(key>arr[n-1]){
    return 0;
  }

  if(key<=arr[0]){
    return n;
  }

    int left = 0, right = n;
    int mid;
    while (left < right) {

        mid = (right + left)/2;
        if (arr[mid] == key) {
            while (mid - 1 > -1 && arr[mid -1] == key)
                mid--;
            return n-mid;
        }

        else if (arr[mid] > key)
            right = mid;

        else
            left = mid + 1;
    }

    while (mid > -1 && arr[mid] > key)
        mid--;

    return n-(mid + 1);
}

int main(){
  int lenght;
  int nums[N];
  scanf ("%i",&lenght);
  for(int i = 0; i < lenght; i++){
    scanf("%i", &nums[i]);
  }
  int tests, test;
  scanf("%i", &tests);
  for(int i=0; i<tests; i++){
    scanf("%i", &test);
    printf("%i ", binarySearchCount(nums, lenght, test));
  }
  return 0;
}
