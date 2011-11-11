#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

struct node
{
	int wklad;      //Tyle wchodzi od przedziału do odpowiedzi
	int odpowiedz;  //Tyle wynosi odpowiedz dla tego przedziału bazowego

	friend ostream & operator<<(ostream & out, const node & o)
	{
		return out<<”wklad = “<<o.wklad<<”,odpowiedz = “<<o.odpowiedz;
	}
};

//N defniuje rozpiętość drzewa (1,N)
//dla prostoty implementacji N = 2^k , gdzie k jest całkowieta 
const int N = 1<<3; // 8
node tab[2*N];

void show(int n = 1)
{
	if(n > 2*N - 1)
		return;
	show(2*n);
	cout <<string( (size_t) floor( log2(n) ) , '\t' )<< tab[n] <<endl;
	show(2*n + 1);
}

//Funckja aktualizuje wartości wierzchołek o numerze offset
void update(int offset)
{
	tab[offset].odpowiedz = tab[offset].wklad + max(tab[2*offset].odpowiedz , tab[2*offset+1].odpowiedz);
}

//Funckja wstawiająca
void insert(int a,int b, int v)
{
    //Inf
	int va = a + N;
	int vb = b + N;

    //Dodanie dla va
	tab[va].odpowiedz = tab[va].wklad += v;
    if(va != vb)    //Sprawdznie czy czasem nie mamy przedziału (a,a)
        tab[vb].odpowiedz = tab[vb].wklad += v;
	va/=2; vb/=2;
    //Dopuki się nie spotkamy
	while(va != vb)
	{
        //Jeżeli wchodzimu do ojca od lewej stronny
        //To po prawej stronnie mamy przedział bazowy
        //Który jest przedziałem bazowym
		if(va % 2)
		{
            tab[va-1].wklad += v;
			update(av-1);   //Zaktualizuj brata 
            update(2*va);   //Zaktualizuj ojca ( bo brat się zmienił ) 
		}
        //Jeżeli wchodzimy do ojca od prawej stronny
        //Podobnie jak powyżej.
		if(! vb % 2)
		{
			tab[vb+1].wklad += v;
			update(vb+1);
            update(2*vb);
		}
        //Idziemy w górę
		va/=2;
		vb/=2;
	}
}


int query(int a,int b)
{
    //Jak zawsze offsety
	int va = a + N;
	int vb = b + N;
    //I wartości z gałęzi
	int maxA = tab[va].odpowiedz;
	int maxB = tab[vb].odpowiedz;
	va/=2; vb/=2;
	while(va != vb)
	{
		if(va % 2)
            maxA = max(maxA,tab[va-1].odpowiedz);
        //Maxem dla dodrzewa jeżeli a wchodzi do ojca po lewej stronie
        //Jest albo to co wyszło z a, albo odpowiedz z jego przedziału bazowego
		if(! vb % 2)
            maxB = max(maxB,tab[vb-1].odpowiedz);
        //Identycznie dla B
        //Idziemy w górę
		va/=2;
		vb/=2;
	}
    //Odpowiedzią, jest maksimum z dwóch stronn.
	return max(maxA,maxB);
}

int main(int argc,char**argv)
{
    
}

