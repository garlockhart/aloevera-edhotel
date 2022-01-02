/*
File Name		: concierge.cpp
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 01/01/2022
*/

/* ========== Header File ========== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "auth.h"
#include "user.h"
#include "concierge.h"
#include "welcome.h"
#include "reservation.h"
#include "report.h"
/* ======= End of Header File ====== */

int ConciergeMenu()
{
	time_t t;
	int menu, more;
	struct tm now;
	
	t = time(NULL);
	now = *localtime(&t);
	
	printf("Date : %s, %s %d, %d", DAY[now.tm_wday], MONTH[now.tm_mon], now.tm_mday, now.tm_year + 1900);
	printf("\n\n");
	
	printf("|==================================================|\n");
	printf("|            WELCOME TO ALOEVERA EDHOTEL           |\n");
	printf("|==================================================|\n");
	printf("|1. Reservation                                    |\n");
	printf("|2. Logout                                         |\n");
	printf("|==================================================|\n");
	printf("|      Copyright 2021 - Develop by Nedersoft       |\n");
	printf("|==================================================|\n");
    
    printf("\n\n");
    
    printf("Select Menu : ");
	scanf("%d", &menu);
	system("cls");
	
	switch (menu){
		case 1:
			ReservationMenu();
			break;		
		case 2:
			Logout();
			break;
	 	default:
	 		printf("ERROR : Sorry I don't know the answer to this one!!!\n");
	 		printf("Press Any Key to continue . . .");
	 		getche();
	 		
	 		system("cls");
			ConciergeMenu();
			break;
	}
}
