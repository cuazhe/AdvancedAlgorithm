class Solution:
    def longestPrefix(self, s: str) -> str:
        n = len(s)
        cur = -float('inf')
        res = ""
        for i in range(1, n):
            if s[:i] == s[-i:]:
                cur = max(cur, i)
                res = s[:i]
        return res
