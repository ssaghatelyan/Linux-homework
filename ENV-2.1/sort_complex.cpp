#include "sort_complex.h"

void bubbleSortByAbs(std::vector<Complex>& arr){
	int n = arr.size();
	for(int i=0;i<n;i++){
		for(int j=0;j<n-i-1;j++){
			if(arr[j].abs() > arr[j+1].abs()){
				Complex temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

