/*
File Name		: welcome.cpp
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 08/12/2001
*/

/* ========== Header File ========== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "welcome.h"
#include "room.h"
#include "user.h"
#include "auth.h"
#include "about.h"
#include "faq.h"
/* ======= End of Header File ====== */

int Welcome()
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
	printf("|1. Login                                          |\n");
	printf("|2. Room                                           |\n");
	printf("|3. User                                           |\n");
	printf("|4. About                                          |\n");
	printf("|5. FAQ                                            |\n");
	printf("|6. Exit                                           |\n");
	printf("|==================================================|\n");
	printf("|      Copyright 2021 - Develop by Nedersoft       |\n");
	printf("|==================================================|\n");
    
    printf("\n\n");
    
    printf("Select Menu : ");
	scanf("%d", &menu);
	system("cls");
	
	switch (menu){
		case 1:
			Login();
			break;
		case 2:
			RoomMenu();
			break;
		case 3:
			UserMenu();
			break;
		case 4:
			About();
			break;
		case 5:
			FAQ();
			break; 
		case 6:
			printf("Are you sure? (Y/N)"); 
        	more = getche();
        	system("cls");
         
	        if (menu == 'Y' || menu == 'y'){
	        	system("cls");
	        	exit(1);
			}
			
			break;
	 	default:
	 		printf("ERROR : Sorry I don't know the answer to this one!!!\n");
	 		printf("Press Any Key to continue . . .");
	 		getche();
	 		
	 		system("cls");
			Welcome();
			break;
	}
}
