#include <iostream>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>

typedef unsigned long long ull;

template <typename num_type>
struct PlusMaxNode
{
    num_type result;
    num_type base;

    void update(const PlusMaxNode & left, const PlusMaxNode & right)
    {
	result = base +  left.result + right.result;
    }
    
    void insert(num_type value)
    {
	base += value;
	result += value;
    }
    
    int query(num_type result)
    {
	return std::max(this->result,result);
    }
};

template<
    typename node_type,
    ull K,
    typename range_index = ull>
struct Tree
{
    typedef typename __gnu_pbds::cc_hash_table<range_index,node_type> table;

    table tree;

    static const range_index ROOT = 1;
    static const range_index N = 1LL<<K;

    struct Index
    {
	table & tree;
	range_index index;

	Index& operator=(const Index& a)
	{
	    tree = a.tree;
	    return *this;
	}

	Index(table & t,range_index position) : tree(t), index(position+N)
	{}

	Index(Index * a,range_index index) : tree(a->tree), index(index)
	{}
	
	operator bool() const
	{
	    return index;
	}

	operator node_type&() const
	{
	    return tree[index];
	}

	Index brother()
	{
	    if(isLeft())
		return Index(this, index + 1);
	    return Index(this,index-1);
	}

	Index father()
	{
	    return Index(this, index / 2);
	}

	Index left()
	{
	    return Index(this, index * 2);
	}

	Index right()
	{
	    return Index(this, index*2 + 1);
	}

	bool isLeft()
	{
	    return (index%2) == 0;
	}

	bool isRight()
	{
	    return ! isRight();
	}

	bool operator!=(Index& b)
	{
	    return index != b.index;
	}

	void show()
	{
	    std::cout<<index<<std::endl;
	}

	void update()
	{
	    tree[index].update(left(),right());
	}

	int query(int result)
	{
	    return tree[index].query(result);
	}

	void insert(int value)
	{
	    tree[index].query(value);
	}
    };

    void show(range_index index = ROOT)
    {
	if(index > 2*N-1)
	    return;
	show(index*2+1);
	std::cout <<std::string((int)(floor(log2(index))),'\t')
		  <<"["<<index<<"]=( "
		  <<tree[index].result <<' '
		  <<tree[index].base<<" )"<<std::endl;
	show(index*2);
    }

    void insert(range_index positionA, range_index positionB ,int value=1)
    {
	Index a(tree,positionA);
	Index b(tree,positionB);

	a.insert(value);
	if(a != b)
	    b.insert(value);
	while(a.father() != b.father())
	{
	    if(a.isLeft())
		a.brother().insert(value);
	    if(b.isRight())
		b.brother().insert(value);
	    a = a.father();
	    b = b.father();
	    a.update();
	    b.update();
	}
	while(a = a.father())
	    a.update();
    }

    int query(range_index positionA, range_index positionB)
    {
	Index a(tree,positionA);
	Index b(tree,positionB);

	int result = a.query(0);
	if(a != b)
	    result = b.query(result);

	while(a.father() != b.father())
	{
	    if(a.isLeft())
		result = a.query(result);
	    if(b.isRight())
		result = b.query(result);
	    a = a.father();
	    b = b.father();
	}
	while(a = a.father())
	    result = a.query(result);
	return result;
    }
};

