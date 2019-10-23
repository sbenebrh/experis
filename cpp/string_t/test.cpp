#include <iostream> // cout

#include"string_t.h"

using namespace std;

#define BUFFER_SIZE 256


void PrintMenu();

int main()
{
	int result = -1;
	String_t s1;
	String_t s2 ;

	char buff[BUFFER_SIZE];
	char letter;
	int index = 0;
	int capacity = 0;
	int start = 0;
	int len = 0;
	bool caseSensFlag = false;

	cout << s1;

	cout << "welcome to the string framework"<< endl;
	while(result != 0)
	{
		PrintMenu();
	
		cin >> result;

		switch (result)
		{
			case 0:
			{
				result = 0;
				break;
			}
			case 1:
			{
				cout << "please enter string\n" ;
				cin >> buff;
				s1.SetString(buff);
				break;
			}

			case 2:
			{
				cout << s1.GetString();
				break;
			}

			case 3:
			{
				s1.Print();
				break;
			}

			case 4:
			{
				cout << s1.Length();
				break;
			}

			case 5:
			{
				cout << "please enter string\n" ;
				cin >> buff;
				s2.SetString(buff);
				cout << "the result is: "<<s1.Compare(s2);
				break;
			}

			case 6:
			{
				cout << "please enter string\n" ;
				cin >> buff;
				s2.SetString(buff);
				s1 = s2;
				cout <<"string s1: "<< endl;
				s1.Print();
				cout << endl;
				cout << "string s2: " << endl;
				s2.Print();
				break;
			}

			case 7:
			{
				cout << s1.UpperCases();
				break;
			}

			case 8:
			{
				cout << s1.LowerCases();
				break;
			}

			case 9:
			{
				cout << "print enter string to prepend"<< endl;
				cin >> buff;
				s2.SetString(buff) ;
				s1.Prepend(s2);
				cout << " the result is :";
				s1.Print();
				break;
			}

			case 10:
			{
				cout << "please enter a string to prepend"<<endl;
				cin >> buff;
				s1.Prepend(buff);
				cout << " the result is :";
				s1.Print();
				break;
			}

			case 11:
			{
				cout << "please enter a string" << endl;
				cin >> buff;
				s2.SetString(buff);
				cout <<"the result is : " ;
				cout<< (s1.Contains(s2));
				break;
			}
			
			case 12:
			{
				cout << "print add string" << endl;
				cin >> buff;
				s2.SetString(buff);
				s1 += s2;
				s1.Print();
				break;
			}

			case 13:
			{
				cout << "print add string" << endl;
				cin >> buff;				
				s1 += buff;
				cout <<"the result is : " ;
				s1.Print();
				break;
			}

			case 14:
			{
				cout << "please enter a string" << endl;
				cin >> buff;
				s2.SetString(buff);
				cout <<"the result is : " ;
				cout<< (s1 < s2);
				break;
			}

			case 15:
			{
				cout << "please enter a string" << endl;
				cin >> buff;
				s2.SetString(buff);
				cout <<"the result is : " ;
				cout<< (s1 <= s2);
				break;
			}
			
			case 16:
			{
				cout << "please enter a string" << endl;
				cin >> buff;
				s2.SetString(buff);
				cout <<"the result is : " ;
				cout<< (s1 > s2);
				break;
			}

			case 17:
			{
				cout << "please enter a string" << endl;
				cin >> buff;
				s2.SetString(buff);
				cout <<"the result is : " ;
				cout<< (s1 >= s2) ;
				break;
			}

			case 18:
			{
				cout << "please enter a string" << endl;
				cin >> buff;
				s2.SetString(buff);
				cout <<"the result is : " ;
				cout<< (s1 == s2) ;
				break;
			}

			case 19:
			{
				cout << "please enter a string" << endl;
				cin >> buff;
				s2.SetString(buff);
				cout <<"the result is : " ;
				cout<< (s1 != s2) ;
				break;
			}

			case 20:
			{
				cout << "please enter letter"<<endl;
				cin >> letter;
				cout <<"please enter index"<< endl;
				cin >> index;
				cout << "before change"<< endl;
				cout << s1 << endl;
				cout <<"after : ";
				s1[index] = letter;
				cout << s1 ;
				break;
			}

			case 21:
			{
				cout <<"please enter index"<< endl;
				cin >> index;
				cout <<"letter : " ;
				letter = s1[index] ;
				cout << letter;
				break;
			}

			case 22:
			{
				cout << " the capacity is : "<< String_t::GetCapacity() << endl;
				break;
			}

			case 23:
			{
				cout << "please enter capacity you want" << endl;
				cin >> capacity;
				cout << " the old capacity was : " << String_t::SetCapacity(capacity);
				break;
			}

			case 24:
			{
				cout << "the case sensitive is : " << String_t::IsCaseSens() << endl;
				break;
			}
			case 25:
			{
				cout << "0 - case insensitive 	" << endl;
				cout << "1 - case sensitive 	" << endl;
				cin >> caseSensFlag;
				cout << "the case sensitive is " << String_t::SetCaseSens(caseSensFlag) << endl;
				break;
			}

			case 26:
			{
				cout<< " enter letter " << endl;
				cin >> letter;
				cout << " the first index of your letter is: " << s1.PosFirstOcc(letter);
				break;
			}

			case 27:
			{
				cout<< " enter letter " << endl;
				cin >> letter;
				cout << " the last index of your letter is: " << s1.PosLastOcc(letter);
				break;
			}

			case 28:
			{
				cout<< " enter start  and length" << endl;
				cin >> start >> len;
				s2 = s1(start, len);
				cout << " the substring is " << s2 ;
				break;
			}
			default:
			{
				return -1;
			}
		}
	}
	return 0;
}
	
void PrintMenu()
{
	cout << endl << "*****************************************************" << endl;
	cout << "1: set string  	" << endl;
	cout << "2: get string 		" << endl;
	cout << "3: print string 	" << endl;
	cout << "4: get length 		" << endl;
	cout << "5: compare string 	" << endl;
	cout << "6: use op =		" << endl;
	cout << "7: upper case 		" << endl;
	cout << "8: lower case 		" << endl;
	cout << "9: prepend string 	" << endl;
	cout << "10: prepend char*	" << endl;
	cout << "11: contain substr	" << endl;
	cout << "12: use op += str	" << endl;
	cout << "13: use op += char*" << endl;
	cout << "14: use op < 		" << endl;
	cout << "15: use op <= 		" << endl;
	cout << "16: use op > 		" << endl;
	cout << "17: use op >= 		" << endl;
	cout << "18: use op == 		" << endl;
	cout << "19: use op != 		" << endl;
	cout << "20: use op []= 	" << endl;
	cout << "21: use op =[] 	" << endl;
	cout << "22: capacity 		" << endl;
	cout << "23: set capacity   " << endl;
	cout << "24: case sensitive " << endl;
	cout << "25: set case sens 	" << endl;
	cout << "26: index first occ" << endl;
	cout << "27: index last occ " << endl;
	cout << "28: use op () 		" << endl;
	cout <<"0: stop 			" << endl;
	cout << "*****************************************************" << endl;
}
