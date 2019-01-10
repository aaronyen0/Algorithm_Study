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
 *改成遞迴版之後，對陣列的每個index都可以決定選或不選
 *不論選或不選，各自進到下一層做一樣的事情
 */
void Combinations(int arr[], int size, int idx, int *selectArr, int selectNum) {
	if (idx == size) {
		return;
	}
	//不選
	Combinations(arr, size, idx + 1, selectArr, selectNum);

	//選
	selectArr[selectNum++] = arr[idx];
	PrintArr(selectArr, selectNum); //若在這一層有選的話，代表多出一種集合，將之印出來
	Combinations(arr, size, idx + 1, selectArr, selectNum);
}
