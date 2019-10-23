#include <iostream>
#include <string>
#include "City.h"
#include "Building.h"
#include "Street.h"

using namespace std;

int main()
{
    Building_t<int> building(123);
    cout << building.GetBuildingID()<<endl;
    Street_t<string, int > street("herzl");
    cout << street.GetStreetID() << endl;
    street.SetStreetID("alon");
    cout << street.GetStreetID() << endl;
    street.AddBuilding2Street(&building);
    cout << street.GetBuilding(123).GetBuildingID() << endl;

    return 0;
}