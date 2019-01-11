
//0-1 knapsack problem
#define MAX(a,b) ((a)>(b)?(a):(b))

const int gK = 10;
const int gN = 5;
int gValue[gN] = {8, 10, 4, 5, 5};
int gWeight[gN] = {6, 4, 2, 4, 3};

//根UKP不同處在max取值方式，由於DP[i-1][*]中的任意集合都不包含物件i
//因此DP[i][*]可透過比較DP[i-1][*-weight[i]]再加上一次物件i測試是否能夠得到更佳解

void Bag01Problem(){
	int DP[gN + 1][gK + 1] = {0};

	for(int i = 0; i < gN; ++i){
		for(int j = 1; j <= gK; ++j){
			if(j >= gWeight[i]){
				DP[i + 1][j] = MAX(DP[i][j - gWeight[i]] + gValue[i], DP[i][j]);
			}else{
				DP[i + 1][j] = DP[i][j];
			}
		}
	}

	for(int i = 0; i < gN + 1; ++i){
		printf("DP[%2d]: ", i);
		for(int j = 0; j < gK + 1; ++j){
			printf("%2d, ", DP[i][j]);
		}
		printf("\n");
	}

}
