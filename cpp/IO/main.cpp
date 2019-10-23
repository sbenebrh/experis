#include "VirtIO_t.h"
#include "AsciiIO_t.h"
#include "BinIO_t.h"

#include <iostream>


using namespace std;

void printMenu();
void writeTest(VirtIO_t& IO);
void ReadTest(VirtIO_t& IO);

void test(VirtIO_t& IO)
{
    int choice = -1;
    char c;
    while(choice != 0)
    {
        printMenu();
        cin >> c;

        switch(c)
        {
            case '<':
                writeTest(IO);
                break;
            
            case '>':
                ReadTest(IO);
                break;
            case 'c':
                try
                {
                   cout <<"pos: " << IO.GetPosition() << endl;
                    
                }
                catch(const string& e)
                {
                    cout << e << endl;
                    return;
                }
                break;
            case 's':
                try
                {
                    int position;
                    cout << "pos: ";
                    cin >> position;
                    IO.SetPosition(position);
                }
                catch(const string& e)
                {
                    cout << e << endl;
                    return;
                }
                break;
            
            case 'l':
                cout << "len: " << IO.GetLength() << endl;
                break;
            default:
                choice = 0;
                break;
        }


    }
    
}


int main()
{
    VirtIO_t* IO = NULL;
    string path, mode;
    char c ;
    cout << "choose file type [a\\b]" << endl;
    cin >> c;
    cout << "please enter a path and mode"<< endl;
    cin >> path >> mode;

    switch(c)
    {
        case 'a':
            IO = new AsciiIO_t(path, mode);
            break;

        case 'b':
            IO = new BinIO_t(path, mode);
            break;

        default :
            return -1;
    }

    test(*IO);
    delete IO;
}
template<class T>
void write(VirtIO_t& IO)
{
    T value;
    cout << "enter value" << endl;
    cin >> value;
    try{
        IO << value << ' ';
    }catch(const string& e)
    {
        cout <<e <<endl;
    }
}

template<class T>
void Read(VirtIO_t& IO)
{
    T value;

    try{
        IO >> value;
        cout << "the value is: " << value << endl; 
    }catch(const string& e)
    {
        cout <<e <<endl;
    }
}
void ReadVoidP(VirtIO_t& IO)
{
    int value;
    BinIO_t* newBinIO = dynamic_cast< BinIO_t*>(&IO);
    if(newBinIO)
    {

        try
        {
            *newBinIO >> &value,sizeof(int) ;
            cout << "the value is " <<value << endl;
        }catch(const string& e)
        {
            cout <<e <<endl;
        }  
    }
}

void ReadTest(VirtIO_t& IO)
{
    char c;
    cout <<"******************************************************************" << endl;
    cout << " (i)nt | (c)har | (s)hort | (l)ong | (f)loat | (d)ouble | (v)oid*" <<endl;
    cin >> c;
    switch(c)
    {
        case 'i':
            Read<int>(IO);
            break;
        case'c':
            Read<char>(IO);
            break;
        case 's':
            Read<short>(IO);
            break;
        case 'l':
            Read<long>(IO);
            break;
        case 'f':
            Read<float>(IO);
            break;
        case 'd':
            Read<double>(IO);
            break;
        case 'v':
            ReadVoidP(IO);
            break;
        default :
            break;
    }
}

void WriteVoidP(VirtIO_t& IO)
{
    int value;
    BinIO_t* newBinIO = dynamic_cast< BinIO_t*>(&IO);
    if(newBinIO)
    {
        cout << "enter a value" << endl;
        cin >> value;
        try
        {
            *newBinIO << &value,sizeof(int) ;
        }catch(const string& e)
        {
            cout <<e <<endl;
        }  
    }
}
void writeTest(VirtIO_t& IO)
{
    char c;
    cout <<"******************************************************************" << endl;
    cout << " (i)nt | (c)har | (s)hort | (l)ong | (f)loat | (d)ouble | (v)oid*" <<endl;
    cin >> c;
    switch(c)
    {
        case 'i':
            write<int>(IO);
            break;
        case'c':
            write<char>(IO);
            break;
        case 's':
            write<short>(IO);
            break;
        case 'l':
            write<long>(IO);
            break;
        case 'f':
            write<float>(IO);
            break;
        case 'd':
            write<double>(IO);
            break;
        case 'v':
            WriteVoidP(IO);
            break;
        default :
            break;
    }
}

void printMenu()
{   cout << "**************************************************" << endl;
    cout << "(<)<| (>)> | (c)urr | (s)eek | (l)ength | (e)xit" << endl;
}

/*
int main()
{
    int a = 10, b = 20;
    char c = 'c';
    int f, e;
    unsigned char d = ' ';
    unsigned short g = 9;
    AsciiIO_t file1("test.txt", "r+");
    BinIO_t file2("test2.txt", "w+");
    file1 << a << d << b << d << c << g << d;
    
    file1.MoveTobegin();
    file1 >> f ;
    cout << f << endl;

    //file2 << a ;
    //file2.MoveTobegin();
    //file2 >> e;

    file2 << &b,sizeof(int);
    file2.MoveTobegin();
    file2 >> &e, sizeof(int);
    
    cout << e << endl;

    
}*/