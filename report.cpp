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
#include "reservation.h"
#include "welcome.h"
#include "room.h"
#include "report.h"
/* ======= End of Header File ====== */

void ReportMenu(){
	int menu;
	system("cls");
	printf("|==================================|\n");
	printf("|            Report Menu           |\n");
	printf("|==================================|\n");
	printf("|1. Show by Day                    |\n");
	printf("|2. Show by Month                  |\n");
	printf("|3. Show by Year                   |\n");
	printf("|4. Show All                       |\n");
	printf("|5. Back                           |\n");
	printf("|==================================|\n");
	
	printf("\n\n");
	printf("Select Menu : ");
	scanf("%d",&menu);
	
	switch(menu){
		case 1 :
			ReservationReport_Day();
			break;
		case 2 :
			ReservationReport_Month();
			break;
		case 3 :
			ReservationReport_Year();
			break;
		case 4 :
			ReportShowAll();
			break;
		case 5 :
			system("cls");
			Welcome();
			break;
		default :
			printf("ERROR : Sorry I don't know the answer to this one!!!");
	 		getch();
	 		
	 		system("cls");
			ReportMenu();
			break;
	}
	
}

void ReservationReport_Day(){
	
	int day, month, year;
	FILE *f_reservation;
	Reservation ReservationData;
	int check;
	system("cls");
	
	printf("Insert Date :");
	fflush(stdin);
	scanf("%d", &day);
	
	printf("Insert Month :");
	fflush(stdin);
	scanf("%d", &month);
	
	printf("Insert Year :");
	fflush(stdin);
	scanf("%d", &year);
	
	f_reservation = fopen("Reservation.DAT","rb");
	check = CheckReservationDate(ReservationData, day, month, year);
	if(check != 0)
		{
			while(fread(&ReservationData, sizeof(ReservationData),1, f_reservation))
			{
				if(day == ReservationData.ReservationDate.Day && month == ReservationData.ReservationDate.Month && year == ReservationData.ReservationDate.Year)
				{
					printf("\n\n");
					printf("Report data on %d / %d / %d",ReservationData.ReservationDate.Day, ReservationData.ReservationDate.Month, ReservationData.ReservationDate.Year);
					printf("\n");
					printf("|===================================================================================|\n");
    				printf("|                                 Reservation Data                                  |\n");
   					printf("|===================================================================================|\n");
    				printf("| ID     Guest Name               Type            Total         Price               |\n");
    				printf("|===================================================================================|\n");
					printf("  %-7d %-20s %d %-15s %-12li %-20li\n", ReservationData.ReservationCode, ReservationData.FullName, ReservationData.RentRoomData.Code, ReservationData.RentRoomData.Name, ReservationData.RentRoomData.Price, ReservationData.GrandTotal);
					printf("\n\n\n");
					printf("Press Any Key to continue . . .");
					getch();
		
					system("cls");
					fclose(f_reservation);
					ReportMenu();
				}
			}
		
		}
	else{
		printf("No data for this time period");
		system("cls");
		fclose(f_reservation);
		ReportMenu();
		}
}


void ReservationReport_Month(){
	
	int day, month, year;
	FILE *f_reservation;
	Reservation ReservationData;
	int check;
	
	system("cls");
	printf("Insert Month :");
	fflush(stdin);
	scanf("%d", &month);
	
	printf("Insert Year :");
	fflush(stdin);
	scanf("%d", &year);
	
	f_reservation = fopen("Reservation.DAT","rb");
	check = CheckReservationDate(ReservationData, day, month, year);
	if(check != 0)
		{
			while(fread(&ReservationData, sizeof(ReservationData),1, f_reservation))
			{
				if(month == ReservationData.ReservationDate.Month && year == ReservationData.ReservationDate.Year)
				{
					printf("\n\n");					
					printf("Report data on %d / %d",ReservationData.ReservationDate.Month, ReservationData.ReservationDate.Year);
					printf("\n");
					printf("|===================================================================================|\n");
    				printf("|                                 Reservation Data                                  |\n");
   					printf("|===================================================================================|\n");
    				printf("| ID     Guest Name               Type            Total         Price               |\n");
    				printf("|===================================================================================|\n");
					printf("  %-7d %-20s %d %-15s %-12li %-20li\n", ReservationData.ReservationCode, ReservationData.FullName, ReservationData.RentRoomData.Code, ReservationData.RentRoomData.Name, ReservationData.RentRoomData.Price, ReservationData.GrandTotal);
					printf("\n\n\n");
					printf("Press Any Key to continue . . .");
					getch();
		
					system("cls");
					fclose(f_reservation);
					ReportMenu();
				}
			}
		
		}
	else{
		printf("No data for this time period");
		system("cls");
		fclose(f_reservation);
		ReportMenu();
		}
}

void ReservationReport_Year(){
	
	int day, month, year;
	FILE *f_reservation;
	Reservation ReservationData;
	int check;
	
	system("cls");
	printf("Insert Year :");
	fflush(stdin);
	scanf("%d", &year);
	
	f_reservation = fopen("Reservation.DAT","rb");
	check = CheckReservationDate(ReservationData, day, month, year);
	if(check != 0)
		{
			while(fread(&ReservationData, sizeof(ReservationData),1, f_reservation))
			{
				if(year == ReservationData.ReservationDate.Year)
				{
					printf("\n\n");
					printf("Report data on %d",ReservationData.ReservationDate.Year);
					printf("\n");
					printf("|===================================================================================|\n");
    				printf("|                                 Reservation Data                                  |\n");
   					printf("|===================================================================================|\n");
    				printf("| ID     Guest Name               Type            Total         Price               |\n");
    				printf("|===================================================================================|\n");
					printf("  %-7d %-20s %d %-15s %-12li %-20li\n", ReservationData.ReservationCode, ReservationData.FullName, ReservationData.RentRoomData.Code, ReservationData.RentRoomData.Name, ReservationData.RentRoomData.Price, ReservationData.GrandTotal);
					printf("\n\n\n");
					printf("Press Any Key to continue . . .");
					getch();
		
					system("cls");
					fclose(f_reservation);
					ReportMenu();
				}
			}
		
		}
	else{
		printf("No data for this time period");
		system("cls");
		fclose(f_reservation);
		ReportMenu();
		}
}


int CheckReservationDate(Reservation ReservationData, int day, int month, int year)
{
	int i = 1;
	FILE *f_reservation;
	
	if(i == 1){
		f_reservation = fopen("Reservation.DAT","rb");
		while(fread(&ReservationData, sizeof(ReservationData), 1, f_reservation))
		{
			if( day == ReservationData.ReservationDate.Day || month == ReservationData.ReservationDate.Month || year == ReservationData.ReservationDate.Year)
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

void ReportShowAll(){
	system("cls");
	printf("\t\t\t\tAll Reservation Data");
	printf("\n\n");
	ReservationData();
		
    printf("Press Any Key to continue . . .");
    getche();
    
    system("cls");
    ReportMenu();
}
