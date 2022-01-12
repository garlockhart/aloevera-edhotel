/*
File Name		: report.cpp
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
#include "administrator.h"
#include "room.h"
#include "report.h"
/* ======= End of Header File ====== */

void ReportMenu()
{
	int Menu;
	
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
	scanf("%d", &Menu);
	
	switch(Menu){
		case 1 :
			/* Call Modul Filter Data Report Reservation by Day */
			ReservationReportDay();
			break;
		case 2 :
			/* Call Modul Filter Data Report Reservation by Month */
			ReservationReportMonth();
			break;
		case 3 :
			/* Call Modul Filter Data Report Reservation by Year */
			ReservationReportYear();
			break;
		case 4 :
			/* Call Modul Show All Data Reservation */
			ReportShowAll();
			break;
		case 5 :
			system("cls");
			
			/* Call Modul Menu Administrator */
			AdministratorMenu();
			break;
		default :
			printf("ERROR : Sorry I don't know the answer to this one!!!");
	 		getch();
	 		
	 		system("cls");
	 		
	 		/* Call Modul Menu Report */
			ReportMenu();
			break;
	}
}

void ReservationReportDay()
{
	FILE *f_reservation;
	Reservation ReservationData;
	int Check, Day, Month, Year;
	system("cls");
	
	
	printf("Insert Date (*Ex : 1 - 31) :");
	fflush(stdin);
	scanf("%d", &Day);
	
	printf("Insert Month (*Ex : 1 - 12) :");
	fflush(stdin);
	scanf("%d", &Month);
	
	printf("Insert Year (*Ex : 2022) :");
	fflush(stdin);
	scanf("%d", &Year);
	
	/* Open File */
	f_reservation = fopen("Reservation.DAT","rb");
	
	/* Erro Handle About Open File */
	if (!f_reservation)
	{
		printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		
		/* Call Modul Menu Report */
		ReportMenu();
	}
	
	Check = CheckReservationDate(ReservationData, Day, Month, Year);
	if(Check != 0){
		while(fread(&ReservationData, sizeof(ReservationData),1, f_reservation))
		{
			if(Day == ReservationData.ReservationDate.Day && Month == ReservationData.ReservationDate.Month && Year == ReservationData.ReservationDate.Year)
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
				
				/* Close File */
				fclose(f_reservation);
				
				/* Call Modul Menu Report */
				ReportMenu();
			}
		}
		
	} else{
		printf("ERROR : No data for this time period");
		system("cls");
		
		/* Close File */
		fclose(f_reservation);
		
		/* Call Modul Menu Report */
		ReportMenu();
	}
}


void ReservationReportMonth()
{
	FILE *f_reservation;
	Reservation ReservationData;
	int Check, Day, Month, Year;
	
	system("cls");
	printf("Insert Month (*Ex : 1 - 12):");
	fflush(stdin);
	scanf("%d", &Month);
	
	printf("Insert Year (*Ex : 2022):");
	fflush(stdin);
	scanf("%d", &Year);
	
	/* Open File */
	f_reservation = fopen("Reservation.DAT","rb");
	
	/* Error Handle About Open File */
	if (!f_reservation)
	{
		printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		
		/* Call Modul Menu Report */
		ReportMenu();
	}
	
	Check = CheckReservationDate(ReservationData, Day, Month, Year);
	
	if(Check != 0){
		while(fread(&ReservationData, sizeof(ReservationData),1, f_reservation))
		{
			if(Month == ReservationData.ReservationDate.Month && Year == ReservationData.ReservationDate.Year){
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
				
				/* Close File */
				fclose(f_reservation);
				
				/* Call Modul Menu Report */
				ReportMenu();
			}
		}
	} else{
		printf("ERROR : No data for this time period");
		system("cls");
		
		/* Close File */
		fclose(f_reservation);
		
		/* Call Modul Menu Report */
		ReportMenu();
	}
}

void ReservationReportYear()
{	
	FILE *f_reservation;
	Reservation ReservationData;
	int Check, Day, Month, Year;
	
	system("cls");
	printf("Insert Year (*Ex : 2022):");
	fflush(stdin);
	scanf("%d", &Year);
	
	/* Open File */
	f_reservation = fopen("Reservation.DAT","rb");
	
	/* Error Handle About Open File */
	if (!f_reservation)
	{
		printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		
		/* Call Modul Menu Report */
		ReportMenu();
	}
	
	Check = CheckReservationDate(ReservationData, Day, Month, Year);
	
	if(Check != 0){
		while(fread(&ReservationData, sizeof(ReservationData),1, f_reservation))
		{
			if(Year == ReservationData.ReservationDate.Year){
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
				
				/* Close File */
				fclose(f_reservation);
				
				/* Call Modul Menu Report */
				ReportMenu();
			}
		}
	} else{
		printf("ERROR : No data for this time period");
		system("cls");
		
		/* Close File */
		fclose(f_reservation);
		
		/* Call Modul Menu Report */
		ReportMenu();
	}
}

void ReportShowAll()
{
	system("cls");
	
	/* Call Modul Show Data Reservation */
	ReservationData();
		
    printf("Press Any Key to continue . . .");
    getche();
    
    system("cls");
    
    /* Call Modul Menu Report */
    ReportMenu();
}

int CheckReservationDate(Reservation ReservationData, int Day, int Month, int Year)
{
	FILE *f_reservation;
	
	/* Open File */
	f_reservation = fopen("Reservation.DAT","rb");
		
	while(fread(&ReservationData, sizeof(ReservationData), 1, f_reservation))
	{
		if(Day == ReservationData.ReservationDate.Day || Month == ReservationData.ReservationDate.Month || Year == ReservationData.ReservationDate.Year)
		{
			/* Close File */
			fclose(f_reservation);
			return 1;
		}
	}
}
