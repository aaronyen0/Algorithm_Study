//最近漸漸對DP有些感覺
//DP的核心觀念在記錄重複運算過的問題
//假設今天有四個矩陣 ABCD，運算順序A(BCD)、(AB)(CD)、(ABC)(D)都可以得到一樣的結果，因此我們可以挑出運算次數誰小
//對(BCD)來說，非單一元素集合可以有{BC、CD、BCD}；對(CD)來說，非單一元素集合可以有{CD}，這時若曾經有人算出最小的CD，就可以拿來用

//程式中的dp[i][j]、i <= j，定義為從矩陣i算到矩陣j最小的乘積和
//另外我們又想的到，對任意矩陣乘積，例如：ABCD，其不包含自身之任意非空集合大小必定都小於4
//若我們能取得集合大小為1~3的所有可能，便能得到集合大小為4的所有拆解情況

/*
//例：若設*為將來要計算的部分、-為多餘的記憶體
//Row[] = {4,5,3};
//Col[] = {5,3,6};
//記算順序如下，自己到自己運算量為0，
0   *   *
-   0   *
-   -   0

//兩兩
0  60   *
-   0   *
-   -   0

0  60   *
-   0  90
-   -   0

//三個
0  60 132
-   0  90
-   -   0
*/

const int N = 5;
int gRow[] = {4,5,3,6,8};
int gCol[] = {5,3,6,8,2};

//這版本是未曾看過他人程式碼下寫的，覺的冗餘的部分挺多的，不過基本架構和流程已經有了
void test1(){
	int dp[N][N] = {0};
	int yOffset = 1;
	int i = 0, j = yOffset++;
	int y, x, min, tmp;

	while(1){
		if(j >= N){
			break;
		}
		min = INT_MAX;
		for(x = i, y = i + 1; x < j; ++x, ++y){
			tmp = dp[i][x] + dp[y][j] + gRow[i]*gCol[x]*gCol[j];
			if(tmp < min){
				min = tmp;
			}
		}
		dp[i++][j++] = min;
		if(j >= N){
			i = 0;
			j = yOffset++;
		}

		for(int k = 0; k < N; ++k){
			for(int q = 0; q < N; ++q){
				printf("%4d ", dp[k][q]);
			}
			printf("\n");
		}
		printf("\n\n");
	}
}


//這版本有先看過別人的寫法
//變數命名比較直觀，不用特別設計就能很直覺的寫出來
void test2(){
	int dp[N][N] = {0};
	int i, j, l, tmp;
	
	//l：長度為多少的矩陣一組
	//i：row、j：column
	//x：切割在第x個矩陣之後	
	for(l = 2; l <= N; ++l){
		for(int i = 0; i <= N - l; ++i){
			j = i + l - 1;
			dp[i][j] = INT_MAX;
			for(int x = i; x < i + l; ++x){
				tmp = dp[i][x] + dp[x + 1][j] + gRow[i]*gCol[j]*gCol[x];
				if(tmp < dp[i][j]){
					dp[i][j] = tmp;
				}
			}

			for(int k = 0; k < N; ++k){
				for(int q = 0; q < N; ++q){
					printf("%4d ", dp[k][q]);
				}
				printf("\n");
			}
			printf("\n\n");
		}
	}


	for(int k = 0; k < N; ++k){
		for(int q = 0; q < N; ++q){
			printf("%4d ", dp[k][q]);
		}
		printf("\n");
	}
	printf("\n\n");
	
}
