/*
File Name		: reservation.cpp
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 08/12/2001
*/

/* ========== Header File ========== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include "concierge.h"
#include "room.h"
#include "reservation.h"
#include "compare.h"
/* ======= End of Header File ====== */

int ReservationMenu()
{
	int menu;
	system("cls");
	printf("|==================================|\n");
	printf("|         Reservation Menu         |\n");
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
			ReservationCreate();
			break;
		case 2:
			ReservationRead();
			break;
		case 3:
			ReservationUpdate();
			break;
	 	case 4:
			ReservationDelete();
			break;
		case 5:
			ConciergeMenu();
			break;
	 	default:
	 		printf("ERROR : Sorry I don't know the answer to this one!!!");
	 		getch();
	 		
	 		system("cls");
			ReservationMenu();
			break;
    }
}

void ReservationCreate()
{
	FILE *f_reservation, *f_room, *f_temproom;
	Reservation ReservationData;
	room roomdata, temproomdata;
	int roomcode, checkreservation, checkroom, more;
	time_t t;
	struct tm now;
	
	t = time(NULL);
	now = *localtime(&t);
	
	system("cls");
	f_reservation = fopen("Reservation.DAT", "ab+");

	if (!f_reservation)
	{
		printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		ReservationMenu();
	}
	
	do {
		printf("Reservation Code	: ");
		fflush(stdin);
		scanf("%d", &ReservationData.ReservationCode);
		
		checkreservation = CheckReservationCode(ReservationData, ReservationData.ReservationCode);
		if(checkreservation != 0)
		{
			system("cls");
			printf("ERROR : Reservation Code has been used, please enter another code!!!\n");
			printf("Press Any Key to continue . . .");
			getch();
			
			system("cls");
			ReservationCreate();
		}
		
		printf("Nasional Identity Number		: ");
		fflush(stdin);
		gets(ReservationData.NIN);
		
		printf("Full Name		: ");
		fflush(stdin);
		scanf("%[^\n]",&ReservationData.FullName); 
		
		printf("Email			: ");
		fflush(stdin);
		gets(ReservationData.Email);
		
		printf("Gender (Male/Female)	: ");
		fflush(stdin);
		gets(ReservationData.Gender);
		
		printf("Age			: ");
		fflush(stdin);
		scanf("%d", &ReservationData.Age);
				
		printf("Room code		: ");
		fflush(stdin);
		scanf("%d", &roomcode);
		
		printf("Number of rooms booked	: ");
		fflush(stdin);
		scanf("%d", &ReservationData.RentRoomData.Quantity);
		
		checkroom = CheckRoomCode(roomdata, roomcode);
		if(checkroom != 0)
		{
			ReservationData.RentRoomData.Code = roomcode;
			f_room = fopen("Room.DAT","rb");
			f_temproom = fopen("TempRoom.DAT", "wb");
			while(fread(&roomdata, sizeof(roomdata),1, f_room)){
				if(roomcode == roomdata.code){
					strcpy(ReservationData.RentRoomData.Name,roomdata.name);
					ReservationData.RentRoomData.Price = roomdata.price;
					
					temproomdata.code = roomdata.code;
					strcpy(temproomdata.name,roomdata.name);
					strcpy(temproomdata.type,roomdata.type);
					
					if(ReservationData.RentRoomData.Quantity > roomdata.total){
						system("cls");
						printf("ERROR : The number of rooms available is only %d rooms.!!!\n", roomdata.total);
						printf("Press Any Key to continue . . .");
						getch();
						
						system("cls");
						ReservationCreate();
					}
					
					temproomdata.total = roomdata.total - ReservationData.RentRoomData.Quantity;
					temproomdata.price = roomdata.price;
					fwrite(&temproomdata, sizeof(temproomdata),1,f_temproom);
				} else {
					fwrite(&roomdata, sizeof(roomdata),1,f_temproom);
				}
			}
			
			fclose(f_room);
			fclose(f_temproom);
		
			remove("Room.DAT");
			rename("TempRoom.DAT", "Room.DAT");
		} else {
			
		}
		
		printf("Type of the room	: %s \n", ReservationData.RentRoomData.Name);
		printf("The price of the room	: %li \n", ReservationData.RentRoomData.Price);
		
		printf("Check In Day		: ");
		fflush(stdin);
		scanf("%d", &ReservationData.CheckInDate.Day);
		
		printf("Check In Month		: ");
		fflush(stdin);
		scanf("%d", &ReservationData.CheckInDate.Month);
		
		printf("Check In Year		: ");
		fflush(stdin);
		scanf("%d", &ReservationData.CheckInDate.Year);
		
		printf("Check Out Day		: ");
		fflush(stdin);
		scanf("%d", &ReservationData.CheckOutDate.Day);
		
		printf("Check Out Month		: ");
		fflush(stdin);
		scanf("%d", &ReservationData.CheckOutDate.Month);
		
		printf("Check Out Year		: ");
		fflush(stdin);
		scanf("%d", &ReservationData.CheckOutDate.Year);
		
		ReservationData.LongStay = ReservationData.CheckOutDate.Day - ReservationData.CheckInDate.Day;
		printf("\n\n");
	  	printf("Long Stay      	: %i\n", ReservationData.LongStay);
		
		ReservationData.Total = ReservationData.RentRoomData.Price * ReservationData.RentRoomData.Quantity * ReservationData.LongStay;
		printf("\n");
		printf("Total			: Rp.%li",ReservationData.Total);
		
		if(ReservationData.Total >= 7500000)
		{
			ReservationData.Discount = 0.1 * ReservationData.Total;
			printf("\n");
			printf("Discount 10%		: Rp. %d\n", ReservationData.Discount);
		} else {
			ReservationData.Discount = 0;
		}

		printf("\n\n");
	  	ReservationData.GrandTotal = ReservationData.Total - ReservationData.Discount;
	  	printf("Grand Total      	: Rp. %li\n", ReservationData.GrandTotal);
		

		ReservationData.ReservationDate.Day = now.tm_mday;
		ReservationData.ReservationDate.Month = now.tm_mon + 1;
		ReservationData.ReservationDate.Year = now.tm_year + 1900;
		
		strcpy(ReservationData.Status,"Reservation");
		
		fwrite(&ReservationData, sizeof(ReservationData), 1, f_reservation);
		
		printf("Do you want to create more data? (Y/N) ");
		
		fflush(stdin);
		more = getche();
	} while (more == 'Y' || more == 'y');
	
	fclose(f_reservation);
	
	system("cls");
	printf("The data is already stored in the file!!!\n");
	printf("Press Any Key to continue . . .");
	getche();
	
	system("cls");
	ReservationMenu();
}

void CountReservationData()
{
	FILE *f_reservation;
	char line[255];
	int count = 0;
	
	f_reservation = fopen("Reservation.DAT", "rt");
	
    if (!f_reservation) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		ReservationMenu();
    } 
	
	while(fgets(line, 255, f_reservation))
    {
    	count++;
	}
	
	printf("The amount of data available is %d", count);
    printf("\n\n");
    
    fclose(f_reservation);
}

void ReservationData()
{
	FILE *f_reservation;
	Reservation ReservationData;
	
	CountReservationData();
    
    printf("|===================================================================================|\n");
    printf("|                                 Reservation Data                                  |\n");
    printf("|===================================================================================|\n");
    printf("| ID     Guest Name               Type            Total         Price               |\n");
    printf("|===================================================================================|\n");
    
    f_reservation = fopen("Reservation.DAT", "rt");
	
    if (!f_reservation) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		ReservationMenu();
    } 
	
	while ((fread(&ReservationData, sizeof(ReservationData), JUM_BLOK, f_reservation)) == JUM_BLOK)
	{
		printf("  %-7d %-20s %d %-15s %-12li %-20li\n", ReservationData.ReservationCode, ReservationData.FullName, ReservationData.RentRoomData.Code, ReservationData.RentRoomData.Name, ReservationData.RentRoomData.Price, ReservationData.GrandTotal);
	}
	
	printf("\n\n\n");
	
	fclose(f_reservation);	
}

void ReservationRead(){
	
	ReservationData();
		
    printf("Press Any Key to continue . . .");
    getche();
    
    system("cls");
    ReservationMenu();
}

int CheckReservationCode(Reservation ReservationData, int id)
{
	int i = 1;
	FILE *f_reservation;
	
	if(i == 1){
		f_reservation = fopen("Reservation.DAT","rb");
		while(fread(&ReservationData, sizeof(ReservationData), 1, f_reservation))
		{
			if( id == ReservationData.ReservationCode)
			{
				fclose(f_reservation);
				return 1;
			}
		}
	} else{
		i = 0;
		fclose(f_reservation);
		return 0;
	}
}

void ReservationUpdate()
{
	int MenuUpdate;
	system("cls");
	ReservationData();
	
	printf("|==================================|\n");
	printf("|        Reservation Update        |\n");
	printf("|==================================|\n");
	printf("|1. Update Status                  |\n");
	printf("|2. Back                           |\n");
	printf("|==================================|\n");
	
    printf("\n");
    printf("Select Menu : ");
	scanf("%d", &MenuUpdate);
	system("cls");
	
    switch (MenuUpdate) { 
        case 1:
			UpdateReservationStatus();
			break;
		case 2:
			ReservationMenu();
			break;
	 	default:
	 		printf("ERROR : Sorry I don't know the answer to this one!!!\n");
	 		printf("Press Any Key to continue . . .");
			getch();
			
			system("cls");
			ReservationUpdate();
			break;
    }
}

void UpdateReservationStatus()
{
	int Code, Compare;
	char Status[15], StatusCheckOut[15];
	room roomdata, temproomdata;
	Reservation ReservationData, TempReservationData;
	FILE *f_reservation, *f_room, *f_tempreservation, *f_temproom;
	
	printf("Enter the Reservation Code to be updated : ");
	fflush(stdin);
	scanf("%d", &Code);
	
	printf("Status (Reservation/Check In/Check Out) : ");
	fflush(stdin);
	scanf("%[^\n]",&Status); 
	
	f_reservation = fopen("Reservation.DAT", "rb");
	f_room = fopen("Room.DAT", "rb");
	f_tempreservation = fopen("TempReservation.DAT", "wb");
	f_temproom = fopen("TempRoom.DAT", "wb");
	
	if (!f_reservation) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		ReservationUpdate();
    } 
    
    if (!f_room) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		ReservationUpdate();
    } 
    
    if (!f_temproom) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		ReservationUpdate();
    }
    
    if (!f_tempreservation) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		ReservationUpdate();
    }
    
    while (fread(&ReservationData, sizeof(ReservationData),1, f_reservation))
	{
		if(Code == ReservationData.ReservationCode){
			TempReservationData.ReservationCode = ReservationData.ReservationCode;
			strcpy(TempReservationData.FullName,ReservationData.FullName);
			strcpy(TempReservationData.Email,ReservationData.Email);
			strcpy(TempReservationData.Email,ReservationData.Email);
			TempReservationData.Age = ReservationData.Age;
			TempReservationData.RentRoomData.Code = ReservationData.RentRoomData.Code;
			strcpy(TempReservationData.RentRoomData.Name,ReservationData.RentRoomData.Name);
			TempReservationData.RentRoomData.Quantity = ReservationData.RentRoomData.Quantity;
			TempReservationData.RentRoomData.Price = ReservationData.RentRoomData.Price;
			TempReservationData.LongStay = ReservationData.LongStay;
			TempReservationData.CheckInDate.Day = ReservationData.CheckInDate.Day;
			TempReservationData.CheckInDate.Month = ReservationData.CheckInDate.Month;
			TempReservationData.CheckInDate.Year = ReservationData.CheckInDate.Year;
			TempReservationData.CheckOutDate.Day = ReservationData.CheckOutDate.Day;
			TempReservationData.CheckOutDate.Month = ReservationData.CheckOutDate.Month;
			TempReservationData.CheckOutDate.Year = ReservationData.CheckOutDate.Year;
			TempReservationData.Total = ReservationData.Total;
			TempReservationData.Discount = ReservationData.Discount;
			TempReservationData.GrandTotal = ReservationData.GrandTotal;
			TempReservationData.ReservationDate.Day = ReservationData.ReservationDate.Day;
			TempReservationData.ReservationDate.Month = ReservationData.ReservationDate.Month;
			TempReservationData.ReservationDate.Year = ReservationData.ReservationDate.Year;
			strcpy(TempReservationData.Status,Status);
	
			fwrite(&TempReservationData, sizeof(TempReservationData), 1, f_tempreservation);
		}  else {
			fwrite(&ReservationData, sizeof(ReservationData), 1, f_tempreservation);
		}
	}
	
	while (fread(&roomdata, sizeof(roomdata), 1, f_room))
	{
		if(TempReservationData.RentRoomData.Code == roomdata.code){
			temproomdata.code = roomdata.code;
			strcpy(temproomdata.name,roomdata.name);
			strcpy(temproomdata.type,roomdata.type);
					
			strcpy(StatusCheckOut, "Check Out");

			Compare = StringCompare(Status,StatusCheckOut);
			if (Compare == 0){
				temproomdata.total = roomdata.total + TempReservationData.RentRoomData.Quantity;
			} else {
				temproomdata.total = roomdata.total;
			}
					
			temproomdata.price = roomdata.price;
			fwrite(&temproomdata, sizeof(temproomdata), 1, f_temproom);
		}  else {
			fwrite(&roomdata, sizeof(roomdata), 1, f_temproom);
		}
	}
	
	fclose(f_reservation);
	fclose(f_room);
	fclose(f_tempreservation);
	fclose(f_temproom);

	remove("Reservation.DAT");
	remove("Room.DAT");
	rename("TempReservation.DAT", "Reservation.DAT");
	rename("TempRoom.DAT", "Room.DAT");
	
	system("cls");
	printf("Data successfully updated!!!\n");
	printf("Press Any Key to continue . . .");
	getch();
	
	system("cls");
	ReservationUpdate();
}

void ReservationDelete()
{
	int menudelete;
	system("cls");
	ReservationData();
	
	printf("|==================================|\n");
	printf("|        Reservation Delete        |\n");
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
			AlertDeleteOneReservationData();
			break;
		case 2:
			AlertDeleteAllReservationData();
			break;
		case 3:
			ReservationMenu();
			break;
	 	default:
	 		printf("ERROR : Sorry I don't know the answer to this one!!!\n");
	 		printf("Press Any Key to continue . . .");
			getch();
			
			system("cls");
			ReservationDelete();
			break;
    }
}
void AlertDeleteOneReservationData()
{
	Reservation ReservationData;
	char Answer;
	int Code;
	
	printf("\n");
	printf("Enter the Reservation Code to be deleted : ");
	scanf("%d", &Code);
	fflush(stdin);
	
	printf("\n");
	printf("Are you sure? (Y/N)");
	Answer = getche();
	
	if (Answer == 'Y' || Answer == 'y')
	{
		system("cls");
		DeleteOneReservationData(ReservationData, Code);
		
		printf("Data successfully deleted!!!\n");
		printf("Press Any Key to continue . . .");
		getch();
		
		system("cls");
		ReservationDelete();
	}
	
	system("cls");
	ReservationDelete();
}

void DeleteOneReservationData(Reservation ReservationData, int ID)
{
	FILE *f_reservation, *f_tempreservation;
	int Code, Check;
	
	Check = CheckReservationCode(ReservationData, ID);
		
	if(Check != 0)
	{
		f_reservation = fopen("Reservation.DAT", "rb");
		f_tempreservation = fopen("TempReservation.DAT", "wb");
		
		while (fread(&ReservationData, sizeof(ReservationData), 1, f_reservation))
		{
			Code = ReservationData.ReservationCode;
			if (Code != ID){
				fwrite(&ReservationData, sizeof(ReservationData), 1, f_tempreservation);
			}
		}
			
		fclose(f_reservation);
		fclose(f_tempreservation);
			
		remove("Reservation.DAT");
    	rename("TempReservation.DAT", "Reservation.DAT");
	} else{
		system("cls");
		printf("ERROR : Reservation data with code %d not found!!!\n", ID);
		printf("Press Any Key to continue . . .");
		getch();
			
		system("cls");
		ReservationCreate();
	}
}

void AlertDeleteAllReservationData()
{
	char Answer;
	
	printf("Are you sure? (Y/N)");
	Answer = getche();
	
	if (Answer == 'Y' || Answer == 'y')
	{
		system("cls");
		DeleteAllReservationData();
	}
	system("cls");
	ReservationDelete();
}

void DeleteAllReservationData()
{
	FILE *f_reservation;

	f_reservation = fopen("Reservation.DAT","wb");
	fclose(f_reservation);
	
	printf("All data was deleted!!!\n");
	printf("Press Any Key to continue . . .");
	getch();
			
	system("cls");
	ReservationDelete();
}
