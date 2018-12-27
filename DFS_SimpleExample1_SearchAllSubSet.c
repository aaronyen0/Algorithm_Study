//這是一個陽春的DFS架構
//可以掃過arr中的所有非空子集合(不用連續)
//for迴圈的概念為從前一個集合中，選擇加入一個新元素進入集合
//值得注意的是，idx用來限制能選擇的左邊界，也就是只能往後選擇
//需細細體會

//遞迴順序如下，版面有限只展示包含{1}的所有子集合
//
// 1 → 2 → 3 → 4
// ↓ ↘   ↘ 
// 4   3    4
//       ↘ 
//         4

//時間複雜度為 O(2^n)，空間複雜度也是，n在20以上大概就是天文數字了
//類似0,1背包問題，要掃過所有選一次或不選的題目可以採用此方法
//甚至是0,∞背包問題都可以用類似的解法，此時就毋須限定idx了，但是要確保有限制式讓所有遞迴都不會陷入無窮迴圈

int gSize = 4;
int gArr[] = { 1,2,3,4};

void dfs(int sum, int arr[], int idx, int maxSize) {
	if (idx >= maxSize) {
		return;
	}
	for (int i = idx; i < maxSize; ++i) {
		printf("sum = %d\n", sum + arr[i]);
		dfs(sum + arr[i], arr, i + 1, maxSize);
	}
}

int main()
{
	int sum = 0;
	dfs(sum, gArr, 0, gSize);
}
