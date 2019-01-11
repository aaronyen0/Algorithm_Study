/**
 * 給你一個陣列
 * 列出所有的非空子集合
 */
 
void Comb_Test() {
	int arr[] = { 1, 2, 3, 4 };

	for (int i = 0; i < 4; ++i) {
		printf("%d\n", arr[i]);
		for (int j = i + 1; j < 4; ++j) {
			printf("%d %d\n", arr[i], arr[j]);
			for (int k = j + 1; k < 4; ++k) {
				printf("%d %d %d\n", arr[i], arr[j], arr[k]);
				for (int l = k + 1; l < 4; ++l) {
					printf("%d %d %d %d\n", arr[i], arr[j], arr[k], arr[l]);
				}
			}
		}
	}
}


void PrintArr(int *arr, int len) {
	for (int i = 0; i < len; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

/**
 * version1
 * 改成遞迴版之後，對陣列的每個idx都可以決定選或不選
 * 核心思想為，arr[idx]到底選或不選，不論哪種情境都各自進到下一層做一樣的選擇
 */
void Combinations(int arr[], int size, int idx, int *selectArr, int selectNum) {
	if (idx == size) {
		return;
	}
	//不選
	Combinations(arr, size, idx + 1, selectArr, selectNum);

	//選
	selectArr[selectNum++] = arr[idx];
	PrintArr(selectArr, selectNum);
	Combinations(arr, size, idx + 1, selectArr, selectNum);
}

/**
 * version2
 * 這個版本以seletcNum為考量
 * selectArr的第幾個數字，決定放入某個值
 * 但是這個值只能是arr中 index >= idx的某個數字
 * 也就是當我們選了某個 arr[i]放入 selectArr[selectNum]後
 * 下一層的所有人都不能再把 indx <= i的值納入選擇
 */
void Combinations2(int arr[], int size, int idx, int *selectArr, int selectNum) {
	if (idx >= size) {
		return;
	}
	
	for (int i = idx; i < size; ++i) {
		selectArr[selectNum] = arr[i];
		PrintArr(selectArr, selectNum + 1);
		Combinations2(arr, size, i + 1, selectArr, selectNum + 1);
		//注意下一層起可選範圍從i+1開始
	}
}
