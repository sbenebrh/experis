#include"function.h"

int main()
{
	AD * controler =NULL;
	enum status stat;
	int menuChoice = 1;
	int flag = 0;
	meeting_t * meeting = NULL;
	int size,incrementBlocks;
	float begining, end;
	int room,index;
	printf("%s\n","MENU" );
	printf("%s\n","-----------------------" );

		while(menuChoice)
	{	

		printf("--press 1 for create new daily calendar \n"
			"--press 2 for destroy calendar \n"	
			"--press 3 to add meeting\n"
			"--press 4 for remove meeting \n"
			"--press 5 for find meeting \n"
			"--press 6 for printing calendar\n"
			"--press 0 to exit\n");
		scanf("%d", &menuChoice);
		switch(menuChoice)
		{
			case 0:
				ADDestroy(controler);
				return 0;
			case 1:
				if(!flag)
				{
					printf("%s\n","enter number of initial meeting" );
					scanf("%d",&size);
					printf("%s\n","enter number of increment slot" );
					scanf("%d",&incrementBlocks);

					controler = ADCreate(size, incrementBlocks);

					flag = 1;
				}
				else
				{
					printf("%s\n","error you have to delete calendar first\n" );
				}
				break;

			case 2:
				ADDestroy(controler);
				flag = 0;
				break;
			case 3:
				if(flag)
				{
					printf("%s\n", "enter the begining of the meeting");
					scanf("%f", &begining);
					printf("%s\n", "enter the end of the meeting");
					scanf("%f", &end);
					printf("%s\n", "enter the room of the meeting");
					scanf("%d", &room);
					meeting = createMeeting(begining,end,room);
					if(! meeting)
					{
						printf("%s\n","error creating meeting" );
						ADDestroy(controler);
						return -1;
					}
					stat = InsertMeeting(controler, meeting);
					if(stat != WELL)
					{
						printf("error insert meeting in the calendar \n");
						break;
					}
				}
				else
					printf("%s\n","no calendar" );
				break;
			case 4:
				if(flag)
				{
					printf("%s\n","enter the begining time of meeting you whant to remove: \n" );
					scanf("%f", &begining);
					index = FindMeeting(controler,begining,&meeting);
					if(meeting)
					{
						stat = RemoveMeeting(controler, &meeting, begining);
						printf("%.2f\t%.2f\t%d\n",meeting ->begin, meeting ->end, meeting -> room );
					}
				}
				else
					printf("%s\n","no calendar" );
				break;
			case 5 :
				printf("%s\n","enter the begining time of meeting you whant to find: \n" );
				scanf("%f", &begining);
				index = FindMeeting(controler,begining,&meeting);
				if(index >= 0)
				{
					printf("%.2f\t%.2f\t%d\n",meeting -> begin, meeting -> end, meeting -> room );
				}
				else
					printf("%s\n","not such a meeting\n" );
				break;
			case 6:
				if(flag)
				{
					stat = ADPrint(controler);
					if(stat != WELL)
						printf("%s\n","error print function\n" );
				}
				else
					printf("%s\n","no calendar\n" );
				break;
			default:
				return 0;




		}
	}	
	return 0;
}