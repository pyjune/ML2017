import java.io.FileInputStream;
import java.util.Scanner;

public class Solution {
	static int [] p;
	static int N;
	static int M;
	public static void main(String[] args)throws Exception {
		// TODO Auto-generated method stub
		System.setIn(new FileInputStream("input.txt"));
		Scanner sc = new Scanner(System.in);
		
		int T = sc.nextInt();
		for(int tc = 1; tc<= T ; tc++)
		{
			N = sc.nextInt();
			M = sc.nextInt();
			p = new int[N+1];
			for(int i = 1; i<=N; i++) 
				p[i] = i; // 대표 초기화. 각자 대표.
			for(int i =0; i<M; i++)
			{
				int n1 = sc.nextInt();
				int n2 = sc.nextInt();
				p[rep(n2)] = rep(n1);
			}
			int cnt = 0;
			for(int i = 1; i<=N; i++)
				if(p[i]==i)
					cnt++;
			System.out.println("#"+tc+" "+cnt);
		}
	}
	public static int rep(int n)
	{
		while(p[n]!=n)
		{
			n = p[n];
		}
		return n;
	}
}
