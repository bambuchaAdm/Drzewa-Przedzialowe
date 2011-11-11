#include <iostream>
#include <cmath>

using namespace std;

const int N = 1<<3; // 8 - ale żeby było pewne że ma postać 2^n
int tab[2*N];

/*
 * Funkcja wypisująca drzewo w postaci trójkąta
 */
void show(int n = 1)
{
	if(n > 2*N - 1)
		return;
	show(2*n);
	cout <<string( (size_t) (floor( log2(n) ) ), '\t' ) << tab[n] <<endl;
	show(2*n + 1);
}

//Powiększamy punkt a o wartość v
void insert(int a, int v)
{
	int va = a + N;
	tab[va]+=v;
	va/=2
	//Dopuki va nie jest korzeniem
	while(va>1)
	{
		tab[va]+=v; //zwiększ przedział bazowy
		va/=2;// Idź w górę
	}
}

//Zapytanie o sumę na przedziale (a,b)
int query(int a,int b)
{
	//Offsety w tablicy dla liści drzewa odpowiadającym a i b
	int va = a + N;
	int vb = b + N;
	//Zmienne przechowujące sumy
	int sumA = tab[va];
	int sumB = 0;
	if(va != vb) //Sprawdzenie czy nie mamy przedziału (a,a)
		sumB = tab[vb];
	//Dopuki a i b się nie spotkają
	while(va != vb)
	{
		// Jeżeli wchodzimy od lewej strony to a+1 też jest przedziałem
		// bazowym 
		if(va % 2)
			sumA += tab[va+1]; // więć go powiększamy
		//Podobnie gdy b wchodzi z lewej stronny 
		if(! vb % 2)
			sumB += tab[vb-1]; // to też go zwiększamy
		//Idziemy w górę.
		va/=2;
		vb/=2;
	}
	//Zwrucenie sumy od obu końców
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








