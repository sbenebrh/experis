#include <iostream>

#include "memPage_t.h"
#include "memManager_t.h"
#include "memPool_t.h"
using namespace std;

int foo(MemManager_t& _memManager)
{
    int buff = 10 ;
    int buff1;
    int read; 
    _memManager.write(&buff, 4);
    buff++;
    _memManager.write(&buff, 4);
    buff++;
    _memManager.write(&buff, 4);
    read = _memManager.read(0, &buff1, 4);
    cout << buff1<< endl;
    return read;
}
int foo2(MemManager_t& _memManager)
{
    int read = 0;
    char buff[25] = "hello world!!!!!";
    char buff2[25];
    _memManager.write(buff, 13);
    read = _memManager.read(0,buff2, 13);
    buff2[13] ='\0';
    cout << buff2 << endl;
    return read;

}
void MM_test(MemManager_t* _pmemManager);
void PrintMenu();

int main()
{
    int choice = -1;
    MemManager_t* mm;
    while (choice != 0)
    {
        PrintMenu();
        cin >> choice;
        switch(choice)
        {
            case 0:
                choice = 0;
                break;
            
            case 1:
                mm = new MemPool_t;
                MM_test(mm);
                break;
            case 2:
                mm = new MemPage_t;
                MM_test(mm);
                break;
                default :
                choice = 0;
        }
    }
    return 0;
}
void PrintMenu()
{
    cout << "welcome to the memory manager"<< endl;
    cout <<"******************************"<<endl;
    cout << "1: for memory pool"<<endl;
    cout << "2: for memory page" <<endl;
    cout << "0: for exit"<< endl;
    cout <<"******************************"<<endl;
    cout <<"******************************"<<endl;
}

void MM_test(MemManager_t* _pmemManager)
{
    int choice  = -1;
    while(choice != 0)
    {
        cout <<"******************************"<<endl;
        cout << "1:Is empty "<<endl;
        cout << "2: get Position" << endl;
        cout << "3: get Size"   <<endl;
        cout << "4: read int " << endl;
        cout << "5: read double " << endl;
        cout << "6: read string " << endl;
        cout << "7: write int " << endl;
        cout << "8: write double" << endl;
        cout << "9: write string" << endl;
        cout << "10: Set position" << endl;
        cout << "11: set Page Size for pool" << endl;
        cout << "0: exit to the main menu" << endl; 
        cout <<"******************************"<<endl;

        cin >> choice;

        switch (choice)
        {
            case 0:
            {
                choice = 0;
                break;
            }
               
            case 1:
            {
                cout << (_pmemManager -> IsEmpty() ? "empty": " not empty")<< endl;
                break;
            }

            case 2:
            {
                cout << "the position is : " << _pmemManager -> GetPositon() << endl;
                break;
            }

            case 3:
            {
                cout << "the size is: " << _pmemManager -> GetSize() << endl;
                break;
            }
            case 4:
            {
                int buff = 0;
                cout << "succeed to read :" <<_pmemManager -> read(&buff, sizeof(int))<<" bytes"<< endl;
                cout << "the result is : " << buff << endl;
                break;   
            }

             case 5:
            {
                double buff = 0;
                cout << "succeed to read :" <<_pmemManager -> read(&buff, sizeof(double))<<" bytes"<< endl;
                cout << "the result is : " << buff << endl;
                break;  
            }

            case 6:
            {
                cout << "how many bytes you want to read ?" << endl;
                size_t bytes = 0;
                cin >> bytes;
                char * buff = new char[bytes + 1];
                
                cout << "succeed to read :" <<_pmemManager -> read(&buff, bytes + 1)<<" bytes"<< endl;
                cout << "the result is : " << buff << endl;
                delete[] buff;
                break;  
            }

            case 7: 
            {
                int buff;
                cout << "with number do you want to write"<< endl;
                cin >> buff;
                cout << "succees to write :" << _pmemManager -> write(&buff, sizeof(int)) << endl;
                break;
            }

            case 8: 
            {
                double buff;
                cout << "with number do you want to write"<< endl;
                cin >> buff;
                cout << "succees to write :" << _pmemManager -> write(&buff, sizeof(double)) << endl;
                break;
            }
            
            case 9:
            {
                cout << "how many bytes you want to read ?" << endl;
                size_t bytes = 0;
                cin >> bytes  ;
                cout << " what do you want to write" << endl;
                char * buff = new char[bytes+1];
                cin >> buff;
                cout << "succees to write :" << _pmemManager -> write(&buff, bytes + 1) << endl;
                delete[] buff;
                break;
            }

            case 10:
            {
                int position = 0;
                cout << "what is the new position ?" << endl;
                cin >> position;
                _pmemManager -> SetPosition(position);
                break;
            }

            case 11:
            {
                int size;
                cout << " what is the new Size" << endl;
                cin >> size;
                cout << " the old size was : " << MemPool_t::SetPageSize(size);
                break;
            }

            default:
            { 
                choice = 0;
                break;
            }    
        }
    }

}