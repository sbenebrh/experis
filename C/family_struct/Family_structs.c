#include <stdio.h>
typedef int (*PersonProfession)(char*) ;


struct person {
	char*	 name;
	int	 age;
	PersonProfession	func;
};


struct familyTree {
   	 int nMembers;
   	 struct person p[2];
   	 struct familyTree* 	next;
   	 
};

typedef struct person Person_t;
typedef struct familyTree FamilyTree_t;

int Refua(char* name)   { printf("I'm a doctor\n");		return 0; }
int Handasa(char* name) { printf("I'm an engineer\n");  return 0; }
FamilyTree_t Halakhmi = { 2, "Ilan", 28, Handasa,"Gilad", 26,Refua, 0, };
FamilyTree_t Buchler  = { 2, "Rita", 38,Refua, "Brian",30, Handasa, 0,  };

void DoIt(FamilyTree_t* ftPtr, char* name, int _index) {
	ftPtr->p[_index].func(name);
}

int main() {
	DoIt(&Halakhmi , "Gilad", 1);
	DoIt(&Buchler  , "Rita", 0);
	return 1;
}