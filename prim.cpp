#include <stdio.h>

int adj[10][10];
int mst[10];

int V, E;
int prim(void);

// for prim2()
int last = 0;
int Q[10][3];
int t[3];
int prim2(int n);
void enQ(int n1, int n2, int w);
void deQ(void);

int main(void)
{
	freopen("Text.txt", "r", stdin);
	scanf("%d %d", &V, &E);

	for (int i = 0; i < E; i++)
	{
		int n1, n2, w;
		scanf("%d %d %d", &n1, &n2, &w);
		adj[n1][n2] = w;
		adj[n2][n1] = w; // 무향그래프
	}
	printf("%d\n", prim2(1));
}

int prim(void)
{
	int sum = 0;
	int cnt = 1; // mst에 포함된 노드 수
	mst[1] = 1; // 1번 노드부터 시작
	while (cnt < V)
	{
		int min = 0x7fffffff;
		int minV = 0;
		for (int i = 1; i <= V; i++)
		{
			if (mst[i] == 1) // MST에 포함된 모든 노드에 대해..
			{
				for (int j = 1; j <= V; j++)
				{
					if (adj[i][j] != 0 && mst[j] == 0) // 인접이면서 MST에 포함되지 않으면
					{
						if (min > adj[i][j])
						{
							min = adj[i][j];
							minV = j;	// 비용이 최소인 노드
						}
					}
				}
			}
		}
		mst[minV] = 1;
		sum += min; // MST에 포함된 간선의 비용을 더함
		cnt++;
	}
	return sum;
}
int prim2(int n)
{
	int cost = 0;
	int cnt = 1;
	// 시작 노드의 모든 인접 노드를 enQ()
	for (int i = 1; i <= V; i++)
	{
		if (adj[n][i] != 0)
		{
			enQ(n, i, adj[n][i]);
		}
	}
	mst[n] = 1; // 시작 노드를 mst에 포함

	while (cnt<V)
	{
		deQ();
		if (mst[t[1]] == 0) // (t[1] 노드가 mst에 포함되어 있지 않으면)
		{
			mst[t[1]] = 1;
			cnt++;
			cost += adj[t[0]][t[1]];
			for (int i = 1; i <= V; i++)
			{
				if (adj[t[1]][i] != 0 && mst[i] == 0)
				{
					enQ(t[1], i, adj[t[1]][i]);
				}
			}
		}
	}
	return cost;
}
void enQ(int n1, int n2, int w)
{
	int c = ++last;
	int p = c / 2;
	//Q[c] = n;
	Q[last][0] = n1;
	Q[last][1] = n2;
	Q[last][2] = w;
	while (Q[p][2] > Q[c][2] && c>1)
	{
		int tmp = Q[p][0];
		Q[p][0] = Q[c][0];
		Q[c][0] = tmp;
		tmp = Q[p][1];
		Q[p][1] = Q[c][1];
		Q[c][1] = tmp;
		tmp = Q[p][2];
		Q[p][2] = Q[c][2];
		Q[c][2] = tmp;
		c = p;
		p = p / 2;
	}
}

void deQ(void)
{
	t[0] = Q[1][0];
	t[1] = Q[1][1];
	t[2] = Q[1][2];

	Q[1][0] = Q[last][0];
	Q[1][1] = Q[last][1];
	Q[1][2] = Q[last][2];
	last--;
	int p = 1;
	while (p < last)
	{
		int c1 = p * 2;
		int c2 = p * 2 + 1;
		if (c2 <= last)
		{
			int c = Q[c1][2] < Q[c2][2] ? c1 : c2;
			if (Q[c][2] < Q[p][2])
			{
				int tmp = Q[p][0];
				Q[p][0] = Q[c][0];
				Q[c][0] = tmp;
				tmp = Q[p][1];
				Q[p][1] = Q[c][1];
				Q[c][1] = tmp;
				tmp = Q[p][2];
				Q[p][2] = Q[c][2];
				Q[c][2] = tmp;
				p = c;
			}
			else
				break;
		}
		else if (c1 <= last)
		{
			if (Q[c1][2] < Q[p][2])
			{
				int tmp = Q[p][0];
				Q[p][0] = Q[c1][0];
				Q[c1][0] = tmp;
				tmp = Q[p][1];
				Q[p][1] = Q[c1][1];
				Q[c1][1] = tmp;
				tmp = Q[p][2];
				Q[p][2] = Q[c1][2];
				Q[c1][2] = tmp;
				p = c1;
			}
			else
				break;
		}
		else
			break;
	}
}

