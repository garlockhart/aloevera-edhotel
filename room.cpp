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
#include "validation.h"
/* ======= End of Header File ====== */

int MenuRoom()
{
	int Menu;
	
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
	scanf("%d", &Menu);
	system("cls");
	
    switch (Menu) { 
        case 1:
			CreateRoom();
			break;
		case 2:
			ReadRoom();
			break;
		case 3:
			UpdateRoom();
			break; 
		case 4:
			DeleteRoom();
			break;
	 	case 5:
			AdministratorMenu();
			break;
	 	default:
	 		printf("ERROR : Sorry I don't know the answer to this one!!!");
	 		getch();
	 		
	 		system("cls");
			MenuRoom();
			break;
    }
}

void CreateRoom()
{
	char More;
	int CheckCode, CheckTotalRoom;
	room roomdata;
    FILE *f_room;
	
	f_room = fopen("Room.DAT", "ab+");

    if (!f_room) 
    { 
        printf ("ERROR : Sorry the file is unavailable!!!\n");
		printf("Press Any Key to continue . . ."); 
		
		getch();
			
		system("cls");
		MenuRoom(); 
    }
    
    do {
    	system("cls");
    	printf("|=====================================|\n");
		printf("|              Create Room            |\n");
		printf("|=====================================|\n");
	
		printf("Code : ");
		fflush(stdin);
		scanf("%d", &roomdata.code);
		
		CheckCode = CheckRoomCode(roomdata, roomdata.code);
		
		if(CheckCode != 0)
		{
			system("cls");
			printf("ERROR : Room code has been used, please enter another code!!!\n");
			printf("Press Any Key to continue . . .");
			getch();
			
			system("cls");
			CreateRoom();
		}
		
		printf("Name : ");
		fflush(stdin);
		gets(roomdata.name);
		
		printf("Type (Single/Double/Triple) : ");
		fflush(stdin);
		gets(roomdata.type);
		
		printf("Total Room : ");
		fflush(stdin);
		scanf("%d", &roomdata.total);
		
		CheckTotalRoom = ValidationNumbers(roomdata.total);
		
		if(CheckTotalRoom == 0)
		{
			system("cls");
			printf("ERROR : The total room should not be negative!!!\n");
			printf("Press Any Key to continue . . .");
			getch();
			
			system("cls");
			CreateRoom();
		}
		
		printf("Price : ");
		fflush(stdin);
		scanf("%li", &roomdata.price);
		
		fwrite(&roomdata, sizeof(roomdata), 1, f_room);
		
		printf("\n");
		printf("Do you want to create more data? (Y/N) ");
		fflush(stdin);
		
		More = getche();
	} while (More == 'Y' || More == 'y');
	
	fclose(f_room);
	
	system("cls");
	printf("The data is already stored in the file!!!\n");
	printf("Press Any Key to continue . . .");
	getche();
	
	system("cls");
	MenuRoom();
}

void CountRoom()
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
		MenuRoom();
    } 
	
	while(fgets(line, 255, f_room))
    {
    	count++;
	}
	
	printf("The amount of data available is %d", count);
    printf("\n\n");
    
    fclose(f_room);
}

void ShowRoom()
{
	FILE *f_room;
	room roomdata;
    
    CountRoom();

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
		MenuRoom();
    } 
	
	while ((fread(&roomdata, sizeof(roomdata), JUM_BLOK, f_room)) == JUM_BLOK)
	{
		printf("  %-5d %-10s %-10s %-10d %-10li\n", roomdata.code, roomdata.name, roomdata.type, roomdata.total, roomdata.price);
	}
	
	printf("\n\n\n");
	
	fclose(f_room);
}

void ReadRoom() 
{
	ShowRoom();
	
    printf("Press Any Key to continue . . .");
    getche();
    
    system("cls");
    MenuRoom();
} 

void UpdateRoom()
{
	int code, CheckTotalRoom;
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
		
	printf("Total Room : ");
	fflush(stdin);
	scanf("%d", &temproomdata.total);
	
	CheckTotalRoom = ValidationNumbers(temproomdata.total);
		
	if(CheckTotalRoom == 0)
	{
		system("cls");
		printf("ERROR : The total room should not be negative!!!\n");
		printf("Press Any Key to continue . . .");
		getch();
			
		system("cls");
		UpdateRoom();
	}
		
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
		MenuRoom();
    } 
    
    if (!f_temproom) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		MenuRoom();
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
	MenuRoom();
}

int CheckRoomCode(room roomdata, int id)
{
	FILE *f_room;
	
	f_room = fopen("Room.DAT","rb");
	while(fread(&roomdata, sizeof(roomdata), 1, f_room))
	{
		if(id == roomdata.code)
		{
			fclose(f_room);
			return 1;
		}
	}
}

void DeleteRoom()
{
	int menudelete;
	
	ShowRoom();
	
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
			AlertDeleteOneRecordRoom();
			break;
		case 2:
			AlertDeleteAllRoom();
			break;
		case 3:
			MenuRoom();
			break;
	 	default:
	 		printf("ERROR : Sorry I don't know the answer to this one!!!\n");
	 		printf("Press Any Key to continue . . .");
			getch();
			
			system("cls");
			DeleteRoom();
			break;
    }
}

void AlertDeleteOneRecordRoom()
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
		DeleteOneRecordRoom(roomdata, code);
		
		printf("Data successfully deleted!!!\n");
		printf("Press Any Key to continue . . .");
		getch();
		
		system("cls");
		DeleteRoom();
	}
	
	system("cls");
	DeleteRoom();
}

void DeleteOneRecordRoom(room roomdata, int id)
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
		DeleteRoom();
	}
}

void AlertDeleteAllRoom()
{
	char Answer;
	
	printf("Are you sure? (Y/N)");
	Answer = getche();
	
	if (Answer == 'Y' || Answer == 'y')
	{
		system("cls");
		DeleteAllRoom();
	}
	system("cls");
	DeleteRoom();
}

void DeleteAllRoom()
{
	FILE *RoomData;

	RoomData = fopen("Room.DAT","wb");
	fclose(RoomData);
	
	printf("All data was deleted!!!\n");
	printf("Press Any Key to continue . . .");
	getch();
			
	system("cls");
	DeleteRoom();
}
