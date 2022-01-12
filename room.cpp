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
        	/* Call Modul Create Data Room */
			CreateRoom();
			break;
		case 2:
			/* Call Modul Read Data Room */
			ReadRoom();
			break;
		case 3:
			/* Call Modul Update Data Room */
			UpdateRoom();
			break;
		case 4:
			/* Call Modul Delete Data Room */
			DeleteRoom();
			break;
	 	case 5:
	 		/* Call Modul Menu Administrator */
			AdministratorMenu();
			break;
	 	default:
	 		printf("ERROR : Sorry I don't know the answer to this one!!!");
	 		getch();
	 		
	 		system("cls");
	 		
	 		/* Call Modul Menu Room */
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
	
	/* Open File */
	f_room = fopen("Room.DAT", "ab+");
	
	/* Error Handle About Open File */
    if (!f_room) 
    { 
        printf ("ERROR : Sorry the file is unavailable!!!\n");
		printf("Press Any Key to continue . . ."); 
		
		getch();
			
		system("cls");
		
		/* Call Modul Menu Data Room */
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
			
			/* Call Modul Create Data Room */
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
			
			/* Call Modul Create Data Room */
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
	
	/* Close File */
	fclose(f_room);
	
	system("cls");
	printf("The data is already stored in the file!!!\n");
	printf("Press Any Key to continue . . .");
	getche();
	
	system("cls");
	
	/* Call Modul Menu Room */
	MenuRoom();
}

void CountRoom()
{
	FILE *f_room;
	char line[255];
	int count = 0;
	
	/* Open File */
	f_room = fopen("Room.DAT", "rt");
	
	/* Error Handle About Open File */
    if (!f_room) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		
		/* Call Modul Menu Room */
		MenuRoom();
    }
	
	while(fgets(line, 255, f_room))
    {
    	count++;
	}
	
	printf("The amount of data available is %d", count);
    printf("\n\n");
    
    /* Close File */
    fclose(f_room);
}

void ShowRoom()
{
	FILE *f_room;
	room roomdata;
    
    /* Call Modul Count Data Room */
    CountRoom();

    printf("|==================================================|\n");
    printf("|                     Room Data                    |\n");
    printf("|==================================================|\n");
    printf("| ID      Name      Type     Total       Price     |\n");
    printf("|==================================================|\n");
    
    /* Open File */
    f_room = fopen("Room.DAT", "rt");
	
	/* Error Handle About Open File */
    if (!f_room) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		
		/* Call Modul Menu Room */
		MenuRoom();
    } 
	
	while ((fread(&roomdata, sizeof(roomdata), JUM_BLOK, f_room)) == JUM_BLOK)
	{
		printf("  %-5d %-10s %-10s %-10d %-10li\n", roomdata.code, roomdata.name, roomdata.type, roomdata.total, roomdata.price);
	}
	
	printf("\n\n\n");
	
	/* Close File */
	fclose(f_room);
}

void ReadRoom() 
{
	/* Call Modul Show Data Room */
	ShowRoom();
	
    printf("Press Any Key to continue . . .");
    getche();
    
    system("cls");
    
    /* Call Modul Menu Room */
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
		
		/* Call Modul Update Data Room */
		UpdateRoom();
	}
		
	printf("Price : ");
	fflush(stdin);
	scanf("%li", &temproomdata.price);

	printf("\n");
	fflush(stdin);
	
	/* Open File */
	f_room = fopen("Room.DAT", "rb");
	f_temproom = fopen("TempRoom.DAT", "wb");
	
	/* Error Handle About Open File */
	if (!f_room) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		
		/* Call Modul Menu Room */
		MenuRoom();
    } 
    
    /* Error Handle About Open File */
    if (!f_temproom) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		
		/* Call Modul Menu Room */
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
	
	/* Close File */
	fclose(f_room);
	fclose(f_temproom);
	
	/* Remove File */
	remove("Room.DAT");
	
	/* Rename File */
	rename("TempRoom.DAT", "Room.DAT");
	
	system("cls");
	printf("Data successfully updated!!!\n");
	printf("Press Any Key to continue . . .");
	getch();
	
	system("cls");
	
	/* Call Modul Menu Room */
	MenuRoom();
}

int CheckRoomCode(room roomdata, int id)
{
	FILE *f_room;
	
	/* Open File */
	f_room = fopen("Room.DAT","rb");
	
	while(fread(&roomdata, sizeof(roomdata), 1, f_room))
	{
		if(id == roomdata.code)
		{
			/* Close File */
			fclose(f_room);
			return 1;
		}
	}
}

void DeleteRoom()
{
	int menudelete;
	
	/* Call Modul Show Data Room */
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
        	/* Call Modul Alert Delete One Record Data Room */
			AlertDeleteOneRecordRoom();
			break;
		case 2:
			/* Call Modul Alert Delete All Data Room */
			AlertDeleteAllRoom();
			break;
		case 3:
			/* Call Modul Menu Room */
			MenuRoom();
			break;
	 	default:
	 		printf("ERROR : Sorry I don't know the answer to this one!!!\n");
	 		printf("Press Any Key to continue . . .");
			getch();
			
			system("cls");
			
			/* Call Modul Delete Data Room */
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
		
		/* Call Modul Delete One Rocord Data Room */
		DeleteOneRecordRoom(roomdata, code);
		
		printf("Data successfully deleted!!!\n");
		printf("Press Any Key to continue . . .");
		getch();
		
		system("cls");
		
		/* Call Modul Delete Data Room */
		DeleteRoom();
	}
	
	system("cls");
	
	/* Call Modul Delete Data Room */
	DeleteRoom();
}

void DeleteOneRecordRoom(room roomdata, int id)
{
	FILE *f_room, *f_temproom;
	int code, check;
	
	check = CheckRoomCode(roomdata, id);
		
	if(check != 0)
	{
		/* Open File */
		f_room = fopen("Room.DAT", "rb");
		f_temproom = fopen("TempRoom.DAT", "wb");
		
		while (fread(&roomdata, sizeof(roomdata), 1, f_room))
		{
			code = roomdata.code;
			if (code != id){
				fwrite(&roomdata, sizeof(roomdata), 1, f_temproom);
			}
		}
			
		/* Close File */
		fclose(f_room);
		fclose(f_temproom);
		
		/* Remove File */
		remove("Room.DAT");
		
		/* Rename File */
    	rename("TempRoom.DAT", "Room.DAT");
	} else{
		system("cls");
		printf("ERROR : Room data with code %d not found!!!\n", id);
		printf("Press Any Key to continue . . .");
		getch();
			
		system("cls");
		
		/* Call Modul Delete Data Room */
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
	
	/* Call Modul Delete Data Room */
	DeleteRoom();
}

void DeleteAllRoom()
{
	FILE *RoomData;
	
	/* Open File */
	RoomData = fopen("Room.DAT","wb");
	
	/* Close File */
	fclose(RoomData);
	
	printf("All data was deleted!!!\n");
	printf("Press Any Key to continue . . .");
	getch();
			
	system("cls");
	
	/* Call Modul Delete Data Room */
	DeleteRoom();
}
