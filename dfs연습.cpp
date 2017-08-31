#include <stdio.h>

void dfs(int n);
void dfs2(int n, int k);
void dfs3(int n, int k, int c);
void dfs4(int n, int k, int c);

int adj[11][11];
int visited[11];
int V, E;
int cnt; // dfs2
int trace[11]; // dfs3
int min; // dfs4

int main(void)
{

	freopen("Text.txt", "r", stdin);
	scanf("%d %d", &V, &E);

	for (int i = 0; i < E; i++)
	{
		int n1, n2;
		scanf("%d %d", &n1, &n2);
		adj[n1][n2] = 1;
		//adj[n2][n1] = 1; // 무향인 경우 추가..
	}
	dfs(1);
	dfs2(1, 4);
	printf("%d\n", cnt);
	dfs3(1, 4, 0);
	min = 0x7fffffff;
	dfs4(1, 4, 0);
	printf("%d\n", min);
}

void dfs(int n)
{
	visited[n] = 1;
	printf("%d ", n);
	for (int i = 1; i <= V; i++)
	{
		if (adj[n][i] == 1 && visited[i] == 0) // 인접이면서 방문하지 않은 곳이면
		{
			dfs(i);
		}
	}
}
void dfs2(int n, int k)
{
	if (n == k)
	{
		cnt++;
		//printf("%d\n", n);
	}
	else
	{
		visited[n] = 1;
		//printf("%d ", n);
		for (int i = 1; i <= V; i++)
		{
			if (adj[n][i] == 1 && visited[i] == 0) // 인접이면서 방문하지 않은 곳이면
			{
				dfs2(i, k);
			}
		}
		visited[n] = 0;
	}
}
void dfs3(int n, int k, int c)
{
	if (n == k)
	{
		cnt++;
		trace[c] = n;
		for (int i = 0; i <= c; i++)
			printf("%d ", trace[i]);
		printf("\n");
	}
	else
	{
		visited[n] = 1;
		trace[c] = n;
		//printf("%d ", n);
		for (int i = 1; i <= V; i++)
		{
			if (adj[n][i] == 1 && visited[i] == 0) // 인접이면서 방문하지 않은 곳이면
			{
				dfs3(i, k, c+1);
			}
		}
		visited[n] = 0;
	}
}

void dfs4(int n, int k, int c)
{
	if (n == k)
	{
		if (min > c)
			min = c;
	}
	else
	{
		visited[n] = 1;
		for (int i = 1; i <= V; i++)
		{
			if (adj[n][i] == 1 && visited[i] == 0) // 인접이면서 방문하지 않은 곳이면
			{
				dfs4(i, k, c + 1);
			}
		}
		visited[n] = 0;
	}
}
