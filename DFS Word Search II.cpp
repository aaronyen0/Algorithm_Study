//別人寫的，有空再回來看

struct node {
        int size, index;
        node *next[26];
        node() {
            reset();
        }
        inline void reset() {
            size = 0;
            index = -1;
        }
} nodes[53700], *root = nodes, *trace[50];

int ns = 1;

class Solution {
public:
    unsigned n, m;
    vector<vector<char>> board;
    vector<string> words;
    vector<string> res;
    
    inline void insert(const char *c, int ind) {
        node *p = root;
        int h = 0;
        while (*c) {
            if (!p->next[*c-97]) p->next[*c-97] = nodes + ns ++;
            p->size ++;
            trace[h++] = p;
            p = p->next[*c-97];
            c++;
        }
        p->size++;
        trace[h++] = p;
        if (p->index != -1) {
            for (int i=0;i<h;i++)
                trace[i]->size --;
        }
        p->index = ind;
    }
    
    inline void add(int index) {
        res.push_back(words[index]);
        node *p = root;
        root->size --;
        for (auto c : words[index]) {
            p = p->next[c-97];
            p->size --;
        }
        p->index = -1;
    }
    
    void dfs(int x,int y, node *p) {
        if (!p || p->size==0) return;
        if (p->index != -1) add(p->index);
        
        char tmp = board[x][y];
        board[x][y] = '6';
        if (x>0 && board[x-1][y]!='6' && p->next[board[x-1][y]-97]) dfs(x-1, y ,p->next[board[x-1][y]-97]);
        if (y>0 && board[x][y-1]!='6' && p->next[board[x][y-1]-97]) dfs(x, y-1 ,p->next[board[x][y-1]-97]);
        if (y<m-1 && board[x][y+1]!='6' && p->next[board[x][y+1]-97]) dfs(x, y+1 ,p->next[board[x][y+1]-97]);
        if (x<n-1 && board[x+1][y]!='6' && p->next[board[x+1][y]-97]) dfs(x+1, y ,p->next[board[x+1][y]-97]);
        
        board[x][y] = tmp;
    }
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if (words.size() == 0) return res;
        memset(root->next, 0, sizeof(root->next));
        this -> board = board;
        this -> words = words;
        for (int i = 0;i<words.size();i++) insert(words[i].c_str(),i);
        n = board.size();
        m = board[0].size();
        for (int i=0;i<n && root->size;i++)
            for (int j=0;j<m && root->size;j++)
            {
                dfs(i, j, root->next[board[i][j]-97]);
            }
        return res;
    }
};
