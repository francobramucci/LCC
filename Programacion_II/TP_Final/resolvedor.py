import subprocess

INF = 9999

def solve(i: int, j: int, cont:int, memo: tuple(list[list[int]], bool)):
    if( i < 0 or i > n or j < 0 or j > m):
        return INF
    if(memo[i][j] != -1):
        return memo[i][j]
    memo[i][j] = min(solve(i+1, j, memo), solve(i-1, j, memo), solve(i, j+1, memo), solve(i, j-1, memo))
