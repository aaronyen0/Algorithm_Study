/**
 * https://zh.wikipedia.org/wiki/%E8%90%8A%E6%96%87%E6%96%AF%E5%9D%A6%E8%B7%9D%E9%9B%A2
 * 萊文斯坦距離，又稱Levenshtein距離
 * 兩個字串之間，由一個轉成另一個所需的最少編輯操作次數
 * 共有三種允許的操作:
 *    1. sitten （k→s）替換
 *    2. sittin （e→i）插入
 *    3. sitting （→g）刪除
 */

int Min3(int a, int b, int c){
    if(a < b){
        if(a < c){
            return a;
        }else{
            return b;
        }
    }
    if(b < c){
        return b;
    }
    return c;
}

int minDistance(char* word1, char* word2){
    int n = 0, m = 0;
    int** dp;
    while(word1[n++]);
    while(word2[m++]);
    dp = (int**)malloc(sizeof(int*) * (n + 1));
    for(int i = 0; i <= n; ++i){
        dp[i] = (int*)malloc(sizeof(int) * (m + 1));
        dp[i][0] = i;
    }
    for(int j = 0; j <= m; ++j){
        dp[0][j] = j;
    }
    
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            if(word1[i - 1] == word2[j - 1]){
                dp[i][j] = Min3(dp[i][j - 1] + 1, dp[i - 1][j] + 1, dp[i - 1][j - 1] + 1);
            }else{
                dp[i][j] = Min3(dp[i][j - 1] + 1, dp[i - 1][j] + 1, dp[i - 1][j - 1]);
            }
        }    
    }
    return dp[n][m];
}
