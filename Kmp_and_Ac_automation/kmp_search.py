def gen_partial(pattern: str):
    """
    Generate a partial list that records a position which share the same prefix-pattern.
    partial('aaabaaab') = [0, 1, 2, 0, 0, 1, 2, 3]

    Args:
        pattern (str): given pattern
    Returns:
        partial (list): the pre_positions of each element 
    """
    n = len(pattern)
    if n == 0:
        return []
    
    j = 0
    partial = [0]
    for i in range(1, n):
        while j  > 0 and pattern[i] != pattern[j]:
            j = partial[j-1]

        if pattern[i] == pattern[j]:
            j += 1
        partial.append(j)

    return partial


def kmp_search(target: str, pattern: str):
    """
    KMP Search
    Find all positions in the target which are the same as the given pattern.

    Note:
        - res = [-1] implies that the given pattern is an empty string: ""
        - If you want to find the no-intersection cases, reset j = 0 
            while matching the pattern 

    Args:
        - target (str): the given target
        - pattern (str): the given pattern
    Returns:
        - res (list): all positions in the target that 
                            are the same as the given pattern
    """
    partial = gen_partial(pattern)
    if not partial:
        return [-1]

    n = len(partial)
    res = []
    j = 0
    for i, w in enumerate(target):
        while j > 0 and w != pattern[j]:
            j = partial[j-1]

        if pattern[j] == w:
            j += 1

        if j == n:
            res.append(i - n + 1) 
            j = partial[j-1]
    
    return res


# Reserve for testing
# if __name__ == "__main__":
#     pattern = 'aa'
#     target = 'aadaadaaaaddaad'
#     res = kmp_search(target, pattern)
#     print(res)
