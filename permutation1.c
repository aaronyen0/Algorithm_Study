/**
 *給一個數字陣列
 *將每個排列方式列出來
 */

void Swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 *version1
 *output需要外部給記憶體，專門用來放當輪的選擇
 *若idx頂到底了，就印出這一輪的結果
 *在寫的途中想到，既然要交換，應該重新設計交換方法，用原始陣列就能做到同樣的事情
 */ 
void Permutations1(int *arr, int arrSize, int* output, int idx) {
	if (idx == arrSize) {
		for (int i = 0; i < arrSize; ++i) {
			printf("%d ", output[i]);
		}
		printf("\n");
		return;
	}
	for (int i = 0; i < arrSize - idx; ++i) {
		output[idx] = arr[i];
		Swap(&arr[i], &arr[arrSize - idx - 1]);
		Permutations1(arr, arrSize, output, idx + 1);
		swap(&arr[i], &arr[arrSize - idx - 1]);
	}
}

