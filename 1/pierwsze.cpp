#include <iostream>
#include <cmath>

using namespace std;

const int N = 8;
int tab[2*N];

void show(int n = 1)
{
	if(n > 2*N - 1)
		return;
	show(2*n);
	cout <<string( (int) (floor( log2(n) ) ), '\t' ) << tab[n] <<endl;
	show(2*n + 1);
}

void insert(int a, int inc)
{
	int va = a + N;
	tab[va]+=inc;
	while(va)
	{
		va/=2;
		tab[va]+=inc;
	}
}

int query(int a,int b)
{
	int va = a + N;
	int vb = b + N;
	int sumA = tab[va];
	int sumB = 0;
	if(va != vb)
		sumB = tab[vb];
	while(va != vb)
	{
		if(va % 2)
			sumA += tab[va+1];
		if(! vb % 2)
			sumB += tab[vb-1];
		va/=2;
		vb/=2;
	}
	return sumA + sumB;
}


int main()
{
	show();
	insert(2,10);
	show();
	insert(5,7);
	show();
	cout<<query(1,4)<<endl;
}








