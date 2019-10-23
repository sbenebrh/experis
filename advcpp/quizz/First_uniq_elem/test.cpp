#include<map>
#include<vector>
#include<iterator>
#include<algorithm>
#include<iostream>

template<typename T>
class Inserter
{
std::map<T, int>& elements;
public:
    Inserter(std::map<T, int>& elem)
    :elements(elem)
    {

    }
    void operator()(T& obj)
    {
        elements[obj] += 1;
    }
};

template<typename T>
class predfunc
{
	std::map<T, int>& m;
public:
    predfunc(std::map<T, int>& itmap)
    : m(itmap)
    {
        
    }

    bool operator()(const T& obj) 
    {
        return (m.find(obj) ->second == 1);
    }
};



template<typename T, typename Iter >
const Iter& First_Unique_Elem(Iter beg, Iter end)
{
    std::map<T,int> allElements;
    std::for_each(beg, end, Inserter<T>(allElements));
    return  std::find_if(beg, end, predfunc<T>(allElements));    
}




class Cat{
public:
friend bool operator<(const Cat& a, const Cat& b);
	Cat(size_t id) { ++n;m_id = id;}
	Cat(Cat const& cat) {++n;++c; m_id = cat.m_id; }
	Cat& operator=(Cat const& cat) {++g;  m_id = cat.m_id; return *this;}
    bool operator==(const Cat& cat){ return m_id == cat.m_id;}
    friend std::ostream& operator<<(std::ostream& os, const Cat& cat);
    
	~Cat() {--n;}

	static int n;
	static int c;
    static int g;
//	static int v[];
    size_t m_id;
};
int Cat::g = 0;
int Cat::n = 0;
int Cat::c = 0;

bool operator<(const Cat& a, const Cat& b)
{
    return a.m_id < b.m_id;
}

std::ostream& operator<<(std::ostream& os, const Cat& cat)
{
    os<<cat.m_id;
    return os;
}

int main()
{
    const int N = 100;
    std::vector<Cat> myvec;
    for(int i = 0, id = 0; i < N; ++i)
    {
        myvec.insert(myvec.end(), Cat(id));
        if(id == 20)
        {
            id = 0;
        } 
    }

    if(First_Unique_Elem<Cat>(myvec.begin(), myvec.end()) == myvec.end())
    {
        std::cout<< "not found" << std::endl;
    }
    else 
    {
        std::cout<< "found" <<std::endl;
    }
}