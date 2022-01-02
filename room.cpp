/*
File Name		: room.cpp
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 08/12/2001
*/

/* ========== Header File ========== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "administrator.h"
#include "room.h"
/* ======= End of Header File ====== */

int RoomMenu()
{
	int menu;
	
	printf("|==================================|\n");
	printf("|             Room Menu            |\n");
	printf("|==================================|\n");
	printf("|1. Create                         |\n");
	printf("|2. Read                           |\n");
	printf("|3. Update                         |\n");
	printf("|4. Delete                         |\n");
	printf("|5. Back                           |\n");
	printf("|==================================|\n");
    
    printf("\n\n");
    printf("Select Menu : ");
	scanf("%d", &menu);
	system("cls");
	
    switch (menu) { 
        case 1:
			RoomCreate();
			break;
		case 2:
			RoomRead();
			break;
		case 3:
			RoomUpdate();
			break; 
		case 4:
			RoomDelete();
			break;
	 	case 5:
			AdministratorMenu();
			break;
	 	default:
	 		printf("ERROR : Sorry I don't know the answer to this one!!!");
	 		getch();
	 		
	 		system("cls");
			RoomMenu();
			break;
    }
}

void RoomCreate()
{
	char more;
	int check;
	room roomdata;
    FILE *f_room;
	
	f_room = fopen("Room.DAT", "ab+");

    if (!f_room) 
    { 
        printf ("ERROR : Sorry the file is unavailable!!!\n");
		printf("Press Any Key to continue . . ."); 
		
		getch();
			
		system("cls");
		RoomMenu(); 
    }
    
    do {
    	system("cls");
    	printf("|=====================================|\n");
		printf("|              Create Room            |\n");
		printf("|=====================================|\n");
	
		printf("Code : ");
		fflush(stdin);
		scanf("%d", &roomdata.code);
		
		check = CheckRoomCode(roomdata, roomdata.code);
		
		if(check != 0)
		{
			system("cls");
			printf("ERROR : Room code has been used, please enter another code!!!\n");
			printf("Press Any Key to continue . . .");
			getch();
			
			system("cls");
			RoomCreate();
		}
		
		printf("Name : ");
		fflush(stdin);
		gets(roomdata.name);
		
		printf("Type (Single/Double/Triple) : ");
		fflush(stdin);
		gets(roomdata.type);
		
		printf("Total : ");
		fflush(stdin);
		scanf("%d", &roomdata.total);
		
		printf("Price : ");
		fflush(stdin);
		scanf("%li", &roomdata.price);
		
		fwrite(&roomdata, sizeof(roomdata), 1, f_room);
		
		printf("\n");
		printf("Do you want to create more data? (Y/N) ");
		fflush(stdin);
		
		more = getche();
	} while (more == 'Y' || more == 'y');
	
	fclose(f_room);
	
	system("cls");
	printf("The data is already stored in the file!!!\n");
	printf("Press Any Key to continue . . .");
	getche();
	
	system("cls");
	RoomMenu();
}

void CountRoomData()
{
	FILE *f_room;
	char line[255];
	int count = 0;
	
	f_room = fopen("Room.DAT", "rt");
	
    if (!f_room) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		RoomMenu();
    } 
	
	while(fgets(line, 255, f_room))
    {
    	count++;
	}
	
	printf("The amount of data available is %d", count);
    printf("\n\n");
    
    fclose(f_room);
}

void RoomData()
{
	FILE *f_room;
	room roomdata;
    
    CountRoomData();

    printf("|==================================================|\n");
    printf("|                     Room Data                    |\n");
    printf("|==================================================|\n");
    printf("| ID      Name      Type     Total       Price     |\n");
    printf("|==================================================|\n");
    
    f_room = fopen("Room.DAT", "rt");
	
    if (!f_room) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		RoomMenu();
    } 
	
	while ((fread(&roomdata, sizeof(roomdata), JUM_BLOK, f_room)) == JUM_BLOK)
	{
		printf("  %-5d %-10s %-10s %-10d %-10li\n", roomdata.code, roomdata.name, roomdata.type, roomdata.total, roomdata.price);
	}
	
	printf("\n\n\n");
	
	fclose(f_room);
}

void RoomRead() 
{
	RoomData();
	
    printf("Press Any Key to continue . . .");
    getche();
    
    system("cls");
    RoomMenu();
} 

void RoomUpdate()
{
	int code;
	room roomdata, temproomdata;
	FILE *f_room, *f_temproom;
	
	fflush(stdin);
	printf("Enter the Room Code to be updated : ");
	scanf("%d", &code);
	
	printf("Name : ");
	fflush(stdin);
	gets(temproomdata.name);
		
	printf("Type (Single/Double/Triple) : ");
	fflush(stdin);
	gets(temproomdata.type);
		
	printf("Total : ");
	fflush(stdin);
	scanf("%d", &temproomdata.total);
		
	printf("Price : ");
	fflush(stdin);
	scanf("%li", &temproomdata.price);

	printf("\n");
	fflush(stdin);
	
	f_room = fopen("Room.DAT", "rb");
	f_temproom = fopen("TempRoom.DAT", "wb");
	
	if (!f_room) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		RoomMenu();
    } 
    
    if (!f_temproom) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		RoomMenu();
    }
	
	while (fread(&roomdata, sizeof(roomdata),1, f_room))
	{
		if(code == roomdata.code){
			temproomdata.code = roomdata.code;
			fwrite(&temproomdata, sizeof(temproomdata),1,f_temproom);
		}  else {
			fwrite(&roomdata, sizeof(roomdata),1,f_temproom);
		}
	}
	
	fclose(f_room);
	fclose(f_temproom);

	remove("Room.DAT");
	rename("TempRoom.DAT", "Room.DAT");
	
	system("cls");
	printf("Data successfully updated!!!\n");
	printf("Press Any Key to continue . . .");
	getch();
	
	system("cls");
	RoomMenu();
}

int CheckRoomCode(room roomdata, int id)
{
	int i = 1;
	FILE *f_room;
	
	if(i == 1){
		f_room = fopen("Room.DAT","rb");
		while(fread(&roomdata, sizeof(roomdata), 1, f_room))
		{
			if(id == roomdata.code)
			{
				fclose(f_room);
				return 1;
			}
		}
	} else{
		i = 0;
		fclose(f_room);
		return 0;
	}
}

void RoomDelete()
{
	int menudelete;
	
	RoomData();
	
	printf("|==================================|\n");
	printf("|            Room Delete           |\n");
	printf("|==================================|\n");
	printf("|1. One Record                     |\n");
	printf("|2. All                            |\n");
	printf("|3. Back                           |\n");
	printf("|==================================|\n");
	
    printf("\n");
    printf("Select Menu : ");
	scanf("%d", &menudelete);
	system("cls");
	
    switch (menudelete) { 
        case 1:
			AlertDeleteOneRoomData();
			break;
		case 2:
			AlertDeleteAllRoomData();
			break;
		case 3:
			RoomMenu();
			break;
	 	default:
	 		printf("ERROR : Sorry I don't know the answer to this one!!!\n");
	 		printf("Press Any Key to continue . . .");
			getch();
			
			system("cls");
			RoomDelete();
			break;
    }
}

void AlertDeleteOneRoomData()
{
	room roomdata;
	char answer;
	int code;
	
	printf("\n");
	printf("Enter the Room Code to be deleted : ");
	scanf("%d", &code);
	fflush(stdin);
	
	printf("\n");
	printf("Are you sure? (Y/N)");
	answer = getche();
	
	if (answer == 'Y' || answer == 'y')
	{
		system("cls");
		DeleteOneRoomData(roomdata, code);
		
		printf("Data successfully deleted!!!\n");
		printf("Press Any Key to continue . . .");
		getch();
		
		system("cls");
		RoomDelete();
	}
	
	system("cls");
	RoomDelete();
}

void DeleteOneRoomData(room roomdata, int id)
{
	FILE *f_room, *f_temproom;
	int code, check;
	
	check = CheckRoomCode(roomdata, id);
		
	if(check != 0)
	{
		f_room = fopen("Room.DAT", "rb");
		f_temproom = fopen("TempRoom.DAT", "wb");
		
		while (fread(&roomdata, sizeof(roomdata), 1, f_room))
		{
			code = roomdata.code;
			if (code != id){
				fwrite(&roomdata, sizeof(roomdata), 1, f_temproom);
			}
		}
			
		fclose(f_room);
		fclose(f_temproom);
			
		remove("Room.DAT");
    	rename("TempRoom.DAT", "Room.DAT");
	} else{
		system("cls");
		printf("ERROR : Room data with code %d not found!!!\n", id);
		printf("Press Any Key to continue . . .");
		getch();
			
		system("cls");
		RoomCreate();
	}
}

void AlertDeleteAllRoomData()
{
	char Answer;
	
	printf("Are you sure? (Y/N)");
	Answer = getche();
	
	if (Answer == 'Y' || Answer == 'y')
	{
		system("cls");
		DeleteAllRoomData();
	}
	system("cls");
	RoomDelete();
}

void DeleteAllRoomData()
{
	FILE *RoomData;

	RoomData = fopen("Room.DAT","wb");
	fclose(RoomData);
	
	printf("All data was deleted!!!\n");
	printf("Press Any Key to continue . . .");
	getch();
			
	system("cls");
	RoomDelete();
}
