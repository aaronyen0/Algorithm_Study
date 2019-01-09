/**
 * 今天想了很久的兩個練習
 * 1.假設有4個數字，如何列出他們的各種排列
 * 2.假設有4個數字，如何列出他們各種非空集合
 */
 

void swapc(char* a, char* b) {
	char tmp = *a;
	*a = *b;
	*b = tmp;
}
int main()
{
	char arr[] = { 'a','b','c','d' };

	//有點糟糕的寫法
	//一目了然，N^4，若當前選的有人選過就pass
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (j == i) {
				continue;
			}
			for (int m = 0; m< 4; ++m) {
				if (m == i || m == j) {
					continue;
				}
				for (int n = 0; n < 4; ++n) {
					if (n == i || n == j || n == m) {
						continue;
					}
					printf("%c %c %c %c\n", arr[i], arr[j], arr[m], arr[n]);
				}
			}
		}
	}
	printf("\n\n\n");
	
	/**
	 *根據前一版想到的改善寫法
	 *構想是：
	 *明明知道某個數字已經被選過了，讓別人選不到他就好了
	 *想到的方法是，將那個數字丟到陣列最末端
	 *其他人就毋須對前面的每個人做檢查，從陣列前方開始選就行了
	 *這個寫法之後會寫成DFS的版本
	 */
	char a, b, c, d, tmp;
	for (int i = 0; i < 4; ++i) {
		a = arr[i];
		swapc(&arr[i], &arr[3]); //選了某個數字，所以將他換到最後面
		for (int j = 0; j < 3; ++j) {
			b = arr[j];
			swapc(&arr[j], &arr[2]);
			for (int m = 0; m < 2; ++m) {
				c = arr[m];
				swapc(&arr[m], &arr[1]);
				for (int n = 0; n < 1; ++n) {
					printf("%c %c %c %c\n", a, b, c, arr[0]);
				}
				swapc(&arr[m], &arr[1]);
			}
			swapc(&arr[j], &arr[2]);
		}
		swapc(&arr[i], &arr[3]);//迴圈進下一輪前，將數字換回來
	}
	printf("\n\n\n");
	
	/**
	 * [組合問題]
	 * 設計想法，到底選還是不選
	 * 這個位置不選的話，當然也不能讓進下一圈的人選
	 * 因此下一個迴圈的初始值為 i + 1
	 */
	for (int i = 0; i < 4; ++i) {
		a = arr[i];
		printf("%c\n", a);
		for (int j = i + 1; j < 4; ++j) {
			b = arr[j];
			printf("%c %c\n", a, b);
			for (int m = j + 1; m < 4; ++m) {
				c = arr[m];
				printf("%c %c %c\n", a, b, c);
				for (int n = m + 1; n < 4; ++n) {
					d = arr[n];
					printf("%c %c %c %c\n", a, b, c, d);
				}
			}
		}
	}
}
