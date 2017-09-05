#include <stdio.h>

int mst[1001];

int V, E;

int last = 0;
int Q[1000000][3];
int t[3];

void enQ(int n1, int n2, int w);
void deQ(void);
int kruskal(void);
int rep(int n);

int main(void)
{
	freopen("Text.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d %d", &V, &E);

		last = 0;
		for (int i = 0; i < E; i++)
		{
			int n1, n2, w;
			scanf("%d %d %d", &n1, &n2, &w);
			enQ(n1, n2, w);
		}

		printf("#%d %d\n", tc, kruskal());
	}
}

int kruskal(void)
{
	int cnt = 0;
	int sum = 0;
	for (int i = 0; i <= V; i++)
		mst[i] = i;
	while (cnt < V)
	{
		deQ();
		int r0 = rep(t[0]);
		int r1 = rep(t[1]);
		if (r0 != r1)
		{
			sum += t[2];
			cnt++;
			mst[r1] = r0;
		}
	}
	return sum;
}

int rep(int n)
{
	while (n != mst[n])
	{
		n = mst[n];
	}
	return n;
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

