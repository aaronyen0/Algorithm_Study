def LCS(seq1, seq2):
    """
    1.forward: find the longest subsequence length
    2.backward: finde the longest subsequence
    
    Return:
        LCS(string list)
    """
    lengths = [[0 for j in range(len(seq2)+1)] for i in range(len(seq1)+1)]
    # row 0 and column 0 are initialized to 0 already
    for i in range(len(seq1)):
        for j in range(len(seq2)):
            if seq1[i] == seq2[j]:
                lengths[i+1][j+1] = lengths[i][j] + 1
            else:
                lengths[i+1][j+1] = max(lengths[i+1][j], lengths[i][j+1])

    # read the substring out from the matrix
    result = []
    lenOfSeq1, lenOfSeq2 = len(seq1), len(seq2)
    while lenOfSeq1!=0 and lenOfSeq2 != 0:
        if lengths[lenOfSeq1][lenOfSeq2] == lengths[lenOfSeq1-1][lenOfSeq2]:
            lenOfSeq1 -= 1
        elif lengths[lenOfSeq1][lenOfSeq2] == lengths[lenOfSeq1][lenOfSeq2-1]:
            lenOfSeq2 -= 1
        else:
            assert seq1[lenOfSeq1-1] == seq2[lenOfSeq2-1]
            result.insert(0,seq1[lenOfSeq1-1])
            lenOfSeq1 -= 1
            lenOfSeq2 -= 1
    return result
