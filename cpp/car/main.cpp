#include <iostream>
#include "car_t.h"
#include "bus.h"
#include "private_t.h"
using namespace std;

void PrintMenu();

int main()
{
	int option = -1;
	Bus_t br(10 , 12, 480);
	Bus_t b;
	cout<< b << endl; 
	cout<< br << endl;
	Private_t h1;
	Private_t h2(10, 150);
	
	while(option != 0)
	{
		PrintMenu();
		cin >> option;
		
		switch(option)
		{
			case 0:
			{
				option = 0;
				break;
			}
			
			case 1:
			{
				b = br;
				break;
			}
			
			case 2:
			{
				h1 = h2;
				break;
			}
			case 3:
			{
				cout << "the result is: "<< (b < br) << endl;
				break;
			}
			
			case 4:
			{
				cout << "the result is: "<< (h1 < h2) << endl;
				break;
			}
			
			case 5:
			{
				cout << "the result is: "<< (b < h2) << endl;
				break;
			}
			
			case 6:
			{
				cout << "the capacity is : " << b.GetCapacity() << endl;
				break;
			}
			
			case 7:
			{
				cout << "the capacity is : " << h1.GetCapacity()<< endl;
				break;
			}
			
			case 8:
			{
				cout << "the Gear is : " << (b.GetGear() == Car_t::STANDARD ? "standard": "automatic");
				break;
			}
			
			case 9:
			{
				cout << "the capacity is : " << (h1.GetGear() == Car_t::STANDARD ? "standard": "automatic");
				break;
			}
			
			case 10:
			{
				cout << "the name is : " << b.GetName()<< endl;
				break;
			}
			
			case 11:
			{
				cout << "the name is : "<< h1.GetName() << endl;
				break;
			}
			
			case 12:
			{
				cout << "the id is : " << b.GetId() << endl;
				break;
			}
			
			case 13:
			{
				cout << "the id is : " << h1.GetId() << endl;
				break;
			}
			case 14:
			{
				int speed;
				cout << "what is the speed? " << endl; 
				cin >> speed;
				h1.SetSpeed(speed);
				break;
			}
			
			case 15:
			{
				cout << " the speed is : " << h1.GetSpeed() << endl;
				break;
			}
			
			case 16:
			{
				h1.IncSpeed();
				break;
			}
			
			case 17:
			{
			 	h2.DecSpeed();
			 	break;	
			}
			
			case 18:
			{
				cout << "the line is : " << b.GetLine() << endl;
				break;
			}
			
			case 19:
			{
				cout << "number of seats : " << b.GetSeats() << endl;
				break;
			}
			
			case 20:
			{
				 int seats = 0;
				 cout << " please enter the number of seats " << endl;
				 cin >> seats;
				 b.SetSeats(seats);
				 break;
			 }
			
			case 21:
			{
				int line = 0;
				 cout << " please enter the number of line " << endl;
				 b.SetLine(line);
				 break;
			}
			
			default:
			{
				option = 0;
				break;
			}
		}
	}
	return 0;
}

void PrintMenu()
{
	cout << endl << "*****************************************************" << endl;
	cout << "1: use op = between two bus   		" << endl;
	cout << "2: use op = between two private   	" << endl;
	cout << "3: compare 2 bus op<				" << endl;
	cout << "4: compare 2 private op< 			" << endl;
	cout << "5: compare private with bus op< 	" << endl;
	cout << "6: get capacity bus				" << endl;
	cout << "7: get capacity private 			" << endl;
	cout << "8: get gear bus 					" << endl;
	cout << "9: get gear private 				" << endl;
	cout << "10: get name bus					" << endl;
	cout << "11: get namne private				" << endl;
	cout << "12: get id bus						" << endl;
	cout << "13: get id private					" << endl;
	cout << "14: set speed						" << endl;
	cout << "15: get speed 						" << endl;
	cout << "16: increment speed 				" << endl;
	cout << "17: decrement speed 				" << endl;
	cout << "18: get line						" << endl;
	cout << "19: get seats						" << endl;
	cout << "20: set seats 						" << endl;
	cout << "21: set line 						" << endl;
	cout << "*****************************************************" << endl;
}
