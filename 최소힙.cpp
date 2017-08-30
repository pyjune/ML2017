/*입력
6
7 2 5 3 4 6
*/

#include <stdio.h>

void enQ(int data);
int deQ(void);

int last;
int Q[10];

int main(void)
{
	int N;
	freopen("Text.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		int data;
		scanf("%d", &data);
		enQ(data);
	}
	while (last != 0)
	{
		printf("%d ", deQ());
	}

	return 0;
}
void enQ(int data)
{
	int c = ++last;
	int p = c / 2;
	Q[c] = data;
	while (c>1 && (Q[c] < Q[p])) // 부모가 존재하고 자식의 데이터가 더 작으면
	{
		int tmp = Q[c];
		Q[c] = Q[p];
		Q[p] = tmp;

		c = p;
		p = c / 2;
	}
}

int deQ(void)
{
	int r = Q[1];
	Q[1] = Q[last];
	last--;
	int p = 1;
	while (p<last)
	{
		int ch1 = p * 2;
		int ch2 = p * 2 + 1;
		if (ch2 <= last) // 오른쪽 자식이 존재하면..
		{
			int c = Q[ch1] < Q[ch2] ? ch1 : ch2;
			if (Q[c] < Q[p])
			{
				int tmp = Q[c];
				Q[c] = Q[p];
				Q[p] = tmp;

				p = c;
			}
			else
				break;
		}
		else if (ch1 <= last) // 왼쪽자식만 있는 경우
		{
			if (Q[ch1] < Q[p])
			{
				int tmp = Q[ch1];
				Q[ch1] = Q[p];
				Q[p] = tmp;

				p = ch1;
			}
			else
				break;
		}
		else // 리프 노드인 경우
		{
			break;
		}
			
	}
	return r;
}
