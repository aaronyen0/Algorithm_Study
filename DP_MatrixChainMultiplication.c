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
