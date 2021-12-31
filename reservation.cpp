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
#include "welcome.h"
#include "room.h"
#include "reservation.h"
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
			Welcome();
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
	FILE *f_reservation, *f_room;
	reservation reservationdata;
	room roomdata;
	int roomcode,check,checkroom, more;
	time_t t;
	struct tm now;
	
	t = time(NULL);
	now = *localtime(&t);
	
	system("cls");
	f_reservation = fopen("Reservation.DAT", "ab+");

	if (!f_reservation)
	{
		printf("File tidak dapat dibuat!\r\n");
	}
	
	do {
		printf("\nReservation Code	: ");
		fflush(stdin);
		scanf("%d", &reservationdata.code);
		
		check = CheckReservationCode(reservationdata, reservationdata.code);
		if(check != 0)
		{
			system("cls");
			printf("ERROR : Reservation code has been used, please enter another code!!!\n");
			printf("Press Any Key to continue . . .");
			getch();
			
			system("cls");
			ReservationCreate();
		}
		
		printf("Fullname		: ");
		fflush(stdin);
		gets(reservationdata.fullname);
		
		printf("Email			: ");
		fflush(stdin);
		gets(reservationdata.email);
		
		printf("Gender (Male/Female)	: ");
		fflush(stdin);
		gets(reservationdata.gender);
		
		printf("Age			: ");
		fflush(stdin);
		scanf("%d", &reservationdata.age);
				
		printf("\nRoom code		: ");
		fflush(stdin);
		scanf("\t%d", &roomcode);
		
		checkroom = CheckRoomCode(roomdata, roomcode);
		if(checkroom != 0)
		{
			reservationdata.rentroomdata.code = roomcode;
			f_room = fopen("Room.DAT","rb");
			while(fread(&roomdata, sizeof(roomdata),1, f_room)){
				if(roomcode == roomdata.code){
					strcpy(reservationdata.rentroomdata.name,roomdata.name);
					reservationdata.rentroomdata.price = roomdata.price;
				}
			}
			fclose(f_room);
		} else {
			
		}
		
		printf("Type of the room	: %s",reservationdata.rentroomdata.name);
		printf("\n");
		printf("The price of the room	: %li",reservationdata.rentroomdata.price);
		printf("Quantity		:");
		fflush(stdin);
		scanf("%d", &reservationdata.rentroomdata.quantity);
		
		reservationdata.total = reservationdata.rentroomdata.price * reservationdata.rentroomdata.quantity;
		printf("\n");
		printf("Total			: Rp.%li",reservationdata.total);
		
		if(reservationdata.total >= 3000000)
		{
			reservationdata.discount = 0.3 * reservationdata.total;
		} else {
			reservationdata.discount = 0;
		}
		printf("\n");
		printf("\n");
		printf("Discount 30%		: Rp. %00.02f\n", reservationdata.discount);
	  	reservationdata.grandtotal = reservationdata.total - reservationdata.discount;
	  	printf("Grand Total      	: Rp. %li\n", reservationdata.grandtotal);
		

		reservationdata.datedata.day = now.tm_mday;
		reservationdata.datedata.month = now.tm_mon + 1;
		reservationdata.datedata.year = now.tm_year + 1900;
		fwrite(&reservationdata, sizeof(reservationdata), 1, f_reservation);
		printf("\r\nPinjam buku lagi? (Y/T)?");
		fflush(stdin);
		more = getche();
	}
	while (more == 'Y' || more == 'y');
	fclose(f_reservation);
	
	printf("\r\nData Saved\r\n");
	ReservationMenu();
}

void ReservationData()
{
	FILE *f_reservation;
	reservation reservationdata;
	
	f_reservation = fopen("Reservation.DAT", "rt");
	system("cls");
    if (!f_reservation) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		ReservationMenu();
    } 

    printf("|===================================================================================|\n");
    printf("|                                 Reservation Data                                  |\n");
    printf("|===================================================================================|\n");
    printf("| ID     Guest Name               Type            Total         Price               |\n");
    printf("|===================================================================================|\n");
	
	while ((fread(&reservationdata, sizeof(reservationdata), JUM_BLOK, f_reservation)) == JUM_BLOK)
	{
		printf("  %-7d %-20s %d %-15s %-12li %-20li\n", reservationdata.code, reservationdata.fullname, reservationdata.rentroomdata.code, reservationdata.rentroomdata.name, reservationdata.rentroomdata.price, reservationdata.grandtotal);
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

void ReservationUpdate()
{
	
}

int CheckReservationCode(reservation reservationdata, int id)
{
	int i = 1;
	FILE *f_reservation;
	
	if(i == 1){
		f_reservation = fopen("Reservation.DAT","rb");
		while(fread(&reservationdata, sizeof(reservationdata), 1, f_reservation))
		{
			if( id == reservationdata.code)
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
			AlertDeleteOneReservData();
			break;
		case 2:
			AlertDeleteAllReservData();
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
void AlertDeleteOneReservData()
{
	reservation reservationdata;
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
		DeleteOneReservData(reservationdata, code);
		
		printf("Data successfully deleted!!!\n");
		printf("Press Any Key to continue . . .");
		getch();
		
		system("cls");
		ReservationDelete();
	}
	
	system("cls");
	ReservationDelete();
}

void DeleteOneReservData(reservation reservationdata, int id)
{
	FILE *f_reservation, *f_temReserv;
	int code, check;
	
	check = CheckReservationCode(reservationdata, id);
		
	if(check != 0)
	{
		f_reservation = fopen("Reservation.DAT", "rb");
		f_temReserv = fopen("TempReserv.DAT", "wb");
		
		while (fread(&reservationdata, sizeof(reservationdata), 1, f_reservation))
		{
			code = reservationdata.code;
			if (code != id){
				fwrite(&reservationdata, sizeof(reservationdata), 1, f_temReserv);
			}
		}
			
		fclose(f_reservation);
		fclose(f_temReserv);
			
		remove("Reservation.DAT");
    	rename("empReserv.DATT", "Room.DAT");
	} else{
		system("cls");
		printf("ERROR : Room data with code %d not found!!!\n", id);
		printf("Press Any Key to continue . . .");
		getch();
			
		system("cls");
		ReservationCreate();
	}
}

void AlertDeleteAllReservData()
{
	char Answer;
	
	printf("Are you sure? (Y/N)");
	Answer = getche();
	
	if (Answer == 'Y' || Answer == 'y')
	{
		system("cls");
		DeleteAllReservData();
	}
	system("cls");
	ReservationDelete();
}

void DeleteAllReservData()
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
