#include <stdio.h>

int ch1[10];
int ch2[10];
int par[10];

void dlr(int n);
void ldr(int n);
void lrd(int n);
void find(int n);

int main(void)
{
	int V, E;

	freopen("Text.txt", "r", stdin);
	scanf("%d %d", &V, &E);
	for (int i = 0; i < E; i++)
	{
		int n1, n2;
		scanf("%d %d", &n1, &n2);
		// 부모를 인덱스로 자식번호 저장
		if (ch1[n1] == 0)
			ch1[n1] = n2;
		else
			ch2[n1] = n2;
		// 자식을 인덱스로 부모번호 저장
		par[n2] = n1;
	}
	//dlr(3);
	
	find(5);
}
// 조상찾기
void find(int n) 
{
	while (par[n] != 0)
	{
		n = par[n];
		printf("%d ", n);
	}
}

void dlr(int n)
{
	if (n != 0)
	{
		printf("%d ", n);
		dlr(ch1[n]);
		dlr(ch2[n]);
	}
}
void ldr(int n)
{
	if (n != 0)
	{		
		ldr(ch1[n]);
		printf("%d ", n);
		ldr(ch2[n]);
	}
}
void lrd(int n)
{
	if (n != 0)
	{
		lrd(ch1[n]);
		lrd(ch2[n]);
		printf("%d ", n);
	}
}
