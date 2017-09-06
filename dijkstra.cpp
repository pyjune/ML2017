#include <stdio.h>


#define INF 0x7fffffff
int d[11];
int u[11];
int adj[11][11];
int V, E;

void dij(void);

int main(void)
{
	freopen("Text.txt", "r", stdin);
	scanf("%d %d", &V, &E);

	for (int i = 1; i <= V; i++)
	{
		for (int j = 1; j <= V; j++)
		{
			if (i == j)
				adj[i][j] = 0;
			else
				adj[i][j] = INF;
		}
	}

	for (int i = 0; i < E; i++)
	{
		int n1, n2, w;
		scanf("%d %d %d", &n1, &n2, &w);
		adj[n1][n2] = w;
	}
	dij();
	printf("%d\n", d[V]);
}

void dij(void)
{
	int cnt = 1;
	u[1] = 1;
	for (int i = 1; i <= V; i++)
		d[i] = adj[1][i];
	while (cnt < V)
	{
		// u[t]==0이고 d[t]가 최소인 t 찾기
		int t = 0;
		int min = INF;
		for (int i = 1; i <= V; i++)
		{
			if (u[i] == 0 && d[i] < min)
			{
				min = d[i];
				t = i;
			}
		}
		u[t] = 1;
		// t를 경유지로. t와 인접인 모든 i에 대해...
		for (int i = 1; i <= V; i++)
		{
			if (adj[t][i] != 0 && adj[t][i] != INF)
			{
				d[i] = d[i] < (d[t] + adj[t][i]) ? d[i] : (d[t] + adj[t][i]);
			}
		}
		cnt++;
	}
}
