#include <stdio.h>

int m[101][101];
int d[101][101];


void find(void);

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
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= M; j++)
			{
				scanf("%d", &m[i][j]);
				d[i][j] = 0;
			}
		}
		
		find();

		printf("#%d %d\n", tc, d[N][M]);
	}
}


void find(void)
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (i == 1)
			{
				d[i][j] = d[i][j - 1] + m[i][j];
			}
			else if (j == 1)
			{
				d[i][j] = d[i - 1][j] + m[i][j];
			}
			else
				d[i][j] = ((d[i][j - 1] < d[i - 1][j]) ? d[i][j - 1] : d[i - 1][j]) + m[i][j];
		}
	}
}
