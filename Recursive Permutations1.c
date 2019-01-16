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


/**
 * version3
 * 不使用遞迴做出所有排列
 * 自定義stack堆疊取代遞迴的堆疊
 * stack[i]代表當進入下個迴圈時，陣列的第i個位子，從陣列的第i + stack[i]的位置選值
 * 注意每進一層迴圈，stack[i]能選的的上限就少1
 * 因此必須滿足 i + stack[i] < arrSize
 * 當時上式不滿足時，代表遞迴要退回前一格，退回去的同時，要將計數器規0，並記得將交換過的值換回來
 *
 * 覺得寫得有點亂，但是堆疊的概念本身沒問題，可再想想如何設計得更簡潔
 */
void Permutations3_NonRecursive(int *arr, const int arrSize) {
	int *stack = (int*)calloc(arrSize, sizeof(int));
	int offset = 0;

	while (true) {
		if (offset == arrSize) {
			for (int i = 0; i < arrSize; ++i) {
				printf("%d ", arr[i]);
			}
			printf("\n");
			--offset;
			continue;
		}
		/*
		printf("offset = %d, stack = ", offset);
		for (int i = 0; i < arrSize; ++i) {
			printf("%d ", stack[i]);
		}
		printf("\n");
		*/
		if (stack[offset] + offset == arrSize) {
			if (offset == 0) {
				break;
			}
			stack[offset--] = 0;
			swap(&arr[offset], &arr[offset + stack[offset] - 1]); //換回來
			continue;
		}
		swap(&arr[offset], &arr[offset + stack[offset]]); //交換
		stack[offset++]++;
	}
	free(stack);
}
