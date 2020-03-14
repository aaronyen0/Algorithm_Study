class TrieNode:
    def __init__(self, val):
        self.val = val
        self.next = dict()
        self.is_end = False


class AcNode(TrieNode):
    """
    If we just want to find the matched-sentences, level is not a necessary attribute.
    But I want to match back to the position in the context, so it is reserve for 
    me to mapping the matched-pattern in the context.
    """
    def __init__(self, val, level):
        super().__init__(val)
        self.level = level
        self.fail = None


class AcAutomation:
    """
    - Generate an ac-automation structure by given sentences.
    - Given each context, find all sub-sentences in the context 
        that appear in the pre-sentences.

    Note:
        - 這是一個用來匹配文章中「句子」的tool，不是找一個string中的sub-string，
            所以不論處理sentence或是context，第一步都是透過split切出文章或句子中的小單詞
            - 一般的str.split()有很多不方便的地方，我依個人需求寫客制化的split取代str.split()

        - 網路上的很多版本都有小bug或不符合個人需求，
            除了有bug的版本外，很多都只匹配不相交的sentence，
            而且若同一條路徑上若有多個end，通常都匹配到第一個就不往下走了。

        - 我的AC自動機會匹配所有的sentence，即使sentence間彼此有交集，
            而且也不會一碰到end就立刻退出，例如:
                sentences = ["a b c", "b c"], context = ["d a b c d e"]
                不論 "a b c" 或 "b c" 都會被我匹配出來，
            如果要修改這個邏輯，請在search_all_sentence()自行修改

        - 新增 search_all_sentence2(): 匹配到就不往下走，從頭繼續匹配

    AC自動機和KMP
        - 相似:
            - 兩者都是匹配不到，就從父結點的fail node繼續匹配 (因為父結點是有匹配到的結點)
            - KMP其實就是只有一條枝幹的AC自動機
            - kmp_generate_partial() = ac_automation_upgrade_fail():
                - 兩者其實都是bfs，只是KMP一個pattern，因此kmp的bfs其實就是沿著pattern掃過一次而以
        - 相異:
            - 由於AC自動機是多個sentences的匹配，可能有某些sentences間又互為sub_sentence，
                如果要找到所有sub_sentences，node每進一格，就必需遍歷一次fail node
            - 遍歷fail node是可以初始化的(用dfs + mem)，並可以在每個節點都紀錄，
                遍歷該結點fail node的結果，用記憶體去減少重複遍歷同樣的fail node的花費
    """
    REMVOE_CHAR_SET = set(" [](){},.?")

    def __init__(self):
        self.root = AcNode('%[ROOT]%', 0)


    def generate_trie(self, sentences: list):
        """
        我的版本不允許root是終點，若sentence_list為空會跳過
        """
        for sentence in sentences:
            sentence_list, _ = self.customized_split(sentence)
            if not sentence_list:
                continue

            node = self.root
            for idx, word in enumerate(sentence_list):
                if word not in node.next:
                    node.next[word] = AcNode(word, idx + 1)
                node = node.next[word]

            node.is_end = True


    def upgrade_fail(self):
        next = [self.root]

        while next:
            parent = next.pop(0)

            for word in parent.next:
                child = parent.next[word]
                if child.level == 1:
                    child.fail = self.root
                else:
                    parent_fail = parent.fail
                    while parent_fail is not None:
                        if child.val in parent_fail.next:
                            child.fail = parent_fail.next[child.val]
                            break
                        parent_fail = parent_fail.fail
                    if parent_fail is None:
                        child.fail = self.root
                next.append(child)


    def search_all_sentence(self, context: str, remove_set=REMVOE_CHAR_SET, is_lower=True):
        context_list, start_end_list = self.customized_split(context, remove_set, is_lower)

        res = []
        node = self.root
        for end_idx, word in enumerate(context_list):
            while node != self.root and word not in node.next:
                node = node.fail

            matched_levels = []
            if word in node.next:
                node = node.next[word]
                matched_levels = self.traversal_fail_end(node)

            for level in matched_levels:
                start_idx = end_idx - level + 1
                start_pos = start_end_list[start_idx][0]
                end_pos = start_end_list[end_idx][1]
                res.append([start_idx, context[start_pos:end_pos]])
            
        return res


    def search_all_sentence2(self, context: str, remove_set=REMVOE_CHAR_SET, is_lower=True):
        context_list, start_end_list = self.customized_split(context, remove_set, is_lower)

        res = []
        node = self.root
        for end_idx, word in enumerate(context_list):
            while node != self.root and word not in node.next:
                node = node.fail

            if word in node.next:
                node = node.next[word]

            if node.is_end:
                start_idx = end_idx - node.level + 1
                start_pos = start_end_list[start_idx][0]
                end_pos = start_end_list[end_idx][1]
                res.append([start_idx, context[start_pos:end_pos]])
                node = self.root
            
        return res


    def traversal_fail_end(self, node: AcNode):
        """
        從某個節點出發，沿著fail node遍歷到根，
        用來抓出有同樣word終點的所有sub-sentences
        """
        res = []
        while node != self.root:
            if node.is_end:
                res.append(node.level)
            node = node.fail
        return res


    @staticmethod
    def customized_split(context, remove_set=REMVOE_CHAR_SET, is_lower=True):
        if is_lower:
            context = context.lower()
        
        context_list = []
        start_end_list = []

        start_idx = -1
        cur_word = ""
        for end_idx, char in enumerate(context):
            if char in remove_set:
                if cur_word != "":
                    context_list.append(cur_word)
                    start_end_list.append([start_idx+1, end_idx])
                    cur_word = ""
                start_idx = end_idx
            else:
                cur_word += char
        if cur_word != "":
            context_list.append(cur_word)
            start_end_list.append([start_idx+1, end_idx])
        
        return context_list, start_end_list


# Reserve for testing
if __name__ == "__main__":
    sentences = [
        'a b a b',
        'b c d e',
        'c d e',
        'a b a b c',
        'e',
        'a d e',
        'i j',
        "a b c",
        "b c"
    ]

    obj = AcAutomation()
    obj.generate_trie(sentences)
    obj.upgrade_fail()

    res1 = obj.search_all_sentence('A B C. d?? a  b c b c', remove_set=set(' .'), is_lower=True)
    print(res1)
    # res2 = obj.search_all_sentence2('a b c d a b c b c')
    # print(res2)

    # print(AcAutomation.customized_split("I  am  from  Taiwan-Taipei.", set(" -.")))
