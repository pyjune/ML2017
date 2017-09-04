#include <stdio.h>

int m[10][10];

void find(int r, int c, int s);
void find2(void);

int N, M;
int min;

int main(void)
{
	int T;


	freopen("Text.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				scanf("%d", &m[i][j]);
			}
		}
		min = 0x7fffffff;
		find(0, 0, 0);

		if (min == 0x7fffffff)
			min = 0;
		printf("#%d %d\n", tc, min);
	}
}

void find(int r, int c, int s)
{
	int dr[] = { 0, 1 };
	int dc[] = { 1, 0 };
	if (r == N - 1 && c == M - 1)
	{
		if (s + m[N - 1][M - 1] < min)
			min = s + m[N - 1][M - 1];
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			int nr = r + dr[i];
			int nc = c + dc[i];
			if (nr < N && nc < M)
			{
				if (m[nr][nc] != 0)
				{
					find(nr, nc, s + m[r][c]);
				}
			}
		}
	}
}
