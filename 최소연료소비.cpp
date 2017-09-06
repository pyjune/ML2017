#include <stdio.h>

#define INF 0x7fffffff

int N;
int map[1000][1000]; // 높이 정보
int d[1000][1000]; // 누적 연료 소비량
int u[1000][1000]; // 경유지로 고려 여부 기록
void dij(void);
// for bfs
int qr[10000000];
int qc[10000000];
void bfs(void);
// for dfs2
int last = 0;
int Q[1000000][3];
int t[3];
void dij2(void);
void enQ(int n1, int n2, int w);
void deQ(void);

int main(void)
{
	freopen("Text.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &map[i][j]);
				d[i][j] = INF;
				u[i][j] = 0;
			}
		}
		//dij();
		bfs();
		//dij2();
		printf("#%d %d\n", tc, d[N - 1][N - 1]);
	}
}

// 단순반복 dijkstra : Time out...
void dij(void)
{
	int dr[] = { 0, 1, 0, -1 };
	int dc[] = { 1, 0, -1, 0 };
	int cnt = 0;
	int tr = 0;
	int tc = 0;

	d[0][0] = 0;

	while (cnt<N*N)
	{
		// d[][]가 최소인 r, c 검색...
		int min = INF;
		for (int i = 0; i<N; i++)
		{
			for (int j = 0; j<N; j++)
			{
				if (u[i][j] == 0 && d[i][j]<min)// 경유지가 아니면서 최소인 곳
				{
					min = d[i][j];
					tr = i;
					tc = j;
				}
			}
		}
		// (tr, tc)의 인접에 대해 기존 비용과 (tr, tc)를 거쳐 가는 비용 비교
		u[tr][tc] = 1; // 경유지로 고려했음을 표시
		for (int i = 0; i<4; i++)
		{
			int nr = tr + dr[i];
			int nc = tc + dc[i];
			if ((nr >= 0) && (nr<N) && (nc >= 0) && (nc<N)) // 유효한 범위이고
			{
				if (u[nr][nc] == 0) // 아직 경유지로 고려되지 않았으면
				{
					int diff = 0;
					if (map[nr][nc]>map[tr][tc]) // 높이 차에 의한 연료 소비
						diff = map[nr][nc] - map[tr][tc];

					int tmp = d[tr][tc] + 1 + diff; // tr,tc를 거쳐 nr,nc로 가는 비용 
					d[nr][nc] = (d[nr][nc]>tmp) ? tmp : d[nr][nc];
				}
			}
		}
		cnt++;
	}
}

void bfs(void)
{
	int dr[] = { 0, 1, 0, -1 };
	int dc[] = { 1, 0, -1, 0 };

	// queue
	int front = -1;
	int rear = -1;


	rear++;
	qr[rear] = 0; // 시작점 enqueue
	qc[rear] = 0;
	d[0][0] = 0;
	while (front != rear)
	{
		// dequeue
		front++;
		int tr = qr[front];
		int tc = qc[front];
		for (int i = 0; i<4; i++)
		{
			int nr = tr + dr[i];
			int nc = tc + dc[i];
			if ((nr >= 0) && (nr<N) && (nc >= 0) && (nc<N)) // 유효한 범위면
			{
				int diff = 0;
				if (map[nr][nc]>map[tr][tc]) // 높이 차에 의한 연료 소비
					diff = map[nr][nc] - map[tr][tc];

				int tmp = d[tr][tc] + 1 + diff; // tr,tc를 거쳐 nr,nc로 가는 비용 
				if (d[nr][nc]>tmp)
				{
					d[nr][nc] = tmp;
					rear++;
					qr[rear] = nr;
					qc[rear] = nc;

				}
			}
		}
	}

}

// 우선순위큐..
void dij2(void)
{
	int dr[] = { 0, 1, 0, -1 };
	int dc[] = { 1, 0, -1, 0 };
	int cnt = 0;
	int tr = 0;
	int tc = 0;

	u[0][0] = 1;
	d[0][0] = 0;

	last = 0;
	enQ(0, 0, 0);

	while (last > 0)
	{
		// d[][]가 최소인 r, c 검색...
		deQ();

		tr = t[0];
		tc = t[1];
		// (tr, tc)의 인접에 대해 기존 비용과 (tr, tc)를 거쳐 가는 비용 비교
		u[tr][tc] = 1; // 경유지로 고려했음을 표시
		for (int i = 0; i<4; i++)
		{
			int nr = tr + dr[i];
			int nc = tc + dc[i];
			if ((nr >= 0) && (nr<N) && (nc >= 0) && (nc<N)) // 유효한 범위이고
			{
				if (u[nr][nc] == 0) // 아직 경유지로 고려되지 않았으면
				{
					int diff = 0;
					if (map[nr][nc]>map[tr][tc]) // 높이 차에 의한 연료 소비
						diff = map[nr][nc] - map[tr][tc];

					int tmp = d[tr][tc] + 1 + diff; // tr,tc를 거쳐 nr,nc로 가는 비용
					if (tmp < d[nr][nc])
					{
						d[nr][nc] = tmp; // 갱신
						enQ(nr, nc, tmp);
					}

				}
			}
		}
	}
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
