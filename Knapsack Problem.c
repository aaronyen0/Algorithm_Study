//有N件物品和一个容量为K的背包。第i件物品的價值是V[i]，重量是W[i]。求解将哪些物品(可一種物品放多次)装入背包可使价值总和最大。

//這是經點DP題目之一
//跟其他的DP題目很像，「每次都只考慮1種物件是否納入集合中」，且可以重覆放同一種物件

#define MAX(a,b) ((a)>(b)?(a):(b))

const int gK = 10;
const int gN = 5;
int gValue[gN] = {8, 10, 4, 5, 5};
int gWeight[gN] = {6, 4, 2, 4, 3};

void BagProblem(){
	int DP[gN][gK + 1] = {0};
  //初始化第一列，只有一個物件被納入考量時
  //其實若不想要這行，宣告成DP[gN + 1][gK + 1]可以省去很多麻煩
  
	for(int j = 1; j <= gK; ++j){
		if(j >= gWeight[0]){
			DP[0][j] = DP[0][j - gWeight[0]] + gValue[0];
		}
	}
	for(int i = 1; i < gN; ++i){
		for(int j = 1; j <= gK; ++j){
			if(j >= gWeight[i]){
				DP[i][j] = MAX(DP[i][j - gWeight[0]] + gValue[i], DP[i -1][j]);
			}else{
				DP[i][j] = DP[i - 1][j];
			}
		}
	}

	for(int i = 0; i < gN; ++i){
		printf("DP[%2d]: ", i);
		for(int j = 0; j < gK + 1; ++j){
			printf("%2d, ", DP[i][j]);
		}
		printf("\n");
	}

}
