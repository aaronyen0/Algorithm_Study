//unbounded knapsack problem (UKP) 
//有N件物品和一个容量为K的背包。第i件物品的價值是V[i]，重量是W[i]。求解将哪些物品(可一種物品放多次)装入背包可使价值总和最大。

//這是經點DP題目之一
//跟其他的DP題目很像，「每次都只考慮1種物件是否納入集合中」，且可以重覆放同一種物件

#define MAX(a,b) ((a)>(b)?(a):(b))

const int gK = 10;
const int gN = 5;
int gValue[gN] = {8, 10, 4, 5, 5};
int gWeight[gN] = {6, 4, 2, 4, 3};

void BagProblem(){
	//將陣列+1需然浪費多餘的空間，但是可以省去很多邊借的判斷式
	int DP[gN + 1][gK + 1] = {0};

	//DP[i][j]儲存前i種物品的「非負(>=0)數量集合」中，在重量為j的情況下，最大價值	
	for(int i = 0; i < gN; ++i){
		for(int j = 1; j <= gK; ++j){
			if(j >= gWeight[i]){
				DP[i + 1][j] = MAX3(DP[i][j - gWeight[i]] + gValue[i], DP[i + 1][j - gWeight[i]] + gValue[i],DP[i][j]);
			}else{
				DP[i + 1][j] = DP[i][j];
			}
		}
	}

	for(int i = 0; i <= gN; ++i){
		printf("DP[%2d]: ", i);
		for(int j = 0; j <= gK; ++j){
			printf("%2d, ", DP[i][j]);
		}
		printf("\n");
	}
}

