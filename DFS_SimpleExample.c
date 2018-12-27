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
