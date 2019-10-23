#include "tContainer.h"
#include <list>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
try
{
    list<int*> mlist;
    tContainer_t<int, list > _container(mlist);
    cout <<_container.Isempty()<< endl <<_container.GetNumberOfElement()<< endl;
    int i = 10;
    _container.insert(&i);
    cout <<_container.Isempty()<< endl <<_container.GetNumberOfElement()<< endl;

    int i1 = 11;
    _container.insert(&i1);
    cout <<_container.Isempty()<< endl <<_container.GetNumberOfElement()<< endl;
    cout << *_container.FirstElement()<< endl;
    cout <<*_container.LastElement() << endl;
    cout << "***************************************************"<<endl;
    _container.Remove(10);
    cout <<_container.Isempty()<< endl <<_container.GetNumberOfElement()<< endl;
    cout << *_container.FirstElement()<< endl;
    cout <<*_container.LastElement() << endl;
    cout << "***************************************************"<<endl;
    int b = 17;
    _container.insert(&b);
    cout << *_container[0] << endl;

    cout << *_container.Find(12)<< endl;
    cout << "***************************************************"<<endl;
    _container.RemoveAll();
    cout <<_container.Isempty()<< endl <<_container.GetNumberOfElement()<< endl;
    cout << "***************************************************"<<endl;
}
catch(string str)
{
    cout << str;
}
    
    return 0;
}