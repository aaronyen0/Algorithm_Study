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


/**
 * version2
 * 程式碼更簡潔，甚至不用buffer
 * 核心概念為
 * 將選到的值放到最前面來，這樣還有一個好處idx設計上更簡單
 * 其他人從下一個idx開始選擇
 *
 * 寫到這邊發現version1其實也不用buffer
 * 前一版若不是print output而是ptint arr，應該也是得到所有排列
 */ 
void Permutations2(int *arr, int arrSize, int idx) {
	if (idx == arrSize) {
		for (int i = 0; i < arrSize; ++i) {
			printf("%d ", arr[i]);
		}
		printf("\n");
		return;
	}
	for (int i = idx; i < arrSize ; ++i) {
		Swap(&arr[idx], &arr[i]);
		Permutations2(arr, arrSize, idx + 1);
		swap(&arr[idx], &arr[i]);
	}
}
