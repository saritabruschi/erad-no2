#include <stdio.h>
#include <stdlib.h>

#define KB (1024)
#define MB (1024 * KB)
#define LARGEST_CACHE_SZ (4 * MB)

#define VECTOR_SIZE 1000

static unsigned char dummyBuffer[LARGEST_CACHE_SZ];

void cleanCache() {
  unsigned long long i;
  for (i = 0; i < LARGEST_CACHE_SZ; i++)
    dummyBuffer[i] += 1;
}

void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void SpentTime() {
  int i;
  for (i=0;i<=0XFFFF;i++);
}


void selectionSort(int *v, int n) {
  int i, j, min_idx;

  for (i = 0; i < n-1; i++) {
    min_idx = i;
    for (j = i+1; j < n; j++) {
      if (v[j] < v[min_idx]) min_idx = j;
    }

    swap(&v[min_idx], &v[i]);
  }
}

void bubbleSort(int *v, int n) {
  int i, j;

  for (i = 0; i < n-1; i++) {
    for (j = 0; j < n-i-1; j++) {
      if (v[j] > v[j+1]) swap(&v[j], &v[j+1]);
    }
  }
}

void merge(int *v, int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 =  r - m;

  int L[n1], R[n2];

  for (i = 0; i < n1; i++) L[i] = v[l + i];
  for (j = 0; j < n2; j++) R[j] = v[m + 1+ j];

  i = j = 0;
  k = l;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      v[k] = L[i];
      i++;
    } else {
      v[k] = R[j];
      j++;
    }

    k++;
  }

  while (i < n1) {
    v[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    v[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(int *v, int l, int r){
  if (l < r) {
    int m = l+(r-l)/2;

    mergeSort(v, l, m);
    mergeSort(v, m+1, r);

    merge(v, l, m, r);
    SpentTime();
  }
}

int partition(int *arr, int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high- 1; j++) {
    if (arr[j] < pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }

  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}

void quickSort(int *v, int low, int high) {
  if (low < high){
    int pi = partition(v, low, high);

    quickSort(v, low, pi - 1);
    quickSort(v, pi + 1, high);
  }
}

int *copyVector(int* originalVector, int vectorSize){
  int *newVector = (int*)malloc(sizeof(int) * vectorSize);

  for(int i = 0; i < vectorSize; i++){
    newVector[i] = originalVector[i];
  }

  return newVector;
}

int main(void) {
  int *v = (int*)malloc(sizeof(int) * VECTOR_SIZE);
  int n;

  //ler vetor
  for(int i = 0; i < VECTOR_SIZE; i++){
    //scanf("%d", &v[i]);
    v[i] = rand()%100;
    //printf("v[%d]: %d\n",i,v[i]);
  }

  int *copy = copyVector(v, VECTOR_SIZE);
  cleanCache();
  selectionSort(copy, VECTOR_SIZE);
  free(copy);

  copy = copyVector(v, VECTOR_SIZE);
  cleanCache();
  bubbleSort(copy, VECTOR_SIZE);
  free(copy);

  copy = copyVector(v, VECTOR_SIZE);
  cleanCache();
  mergeSort(copy, 0, VECTOR_SIZE-1);
  free(copy);

  copy = copyVector(v, VECTOR_SIZE);
  cleanCache();
  quickSort(copy, 0, VECTOR_SIZE-1);
  free(copy);

  free(v);
  return 0;
}
