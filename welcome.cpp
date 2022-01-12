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
#include "reservation.h"
#include "report.h"
/* ======= End of Header File ====== */

int Welcome()
{
	time_t t;
	int Menu, Answer;
	struct tm now;
	
	t = time(NULL);
	now = *localtime(&t);
	
	printf("Date : %s, %s %d, %d", DAY[now.tm_wday], MONTH[now.tm_mon], now.tm_mday, now.tm_year + 1900);
	printf("\n\n");
	
	printf("|==================================================|\n");
	printf("|            WELCOME TO ALOEVERA EDHOTEL           |\n");
	printf("|==================================================|\n");
	printf("|1. Login                                          |\n");
	printf("|2. About                                          |\n");
	printf("|3. FAQ                                            |\n");
	printf("|4. Exit                                           |\n");
	printf("|==================================================|\n");
	printf("|      Copyright 2021 - Develop by Nedersoft       |\n");
	printf("|==================================================|\n");
    
    printf("\n\n");
    
    printf("Select Menu : ");
	scanf("%d", &Menu);
	system("cls");
	
	switch (Menu){
		case 1:
			/* Call Modul Login */
			Login();
			break;
		case 2:
			/* Call Modul About */
			About();
			break;
		case 3:
			/* Call Modul FAQ */
			FAQ();
			break; 
		case 4:
			printf("Are you sure? (Y/N)"); 
        	Answer = getche();
        	system("cls");
         
	        if (Answer == 'Y' || Answer == 'y'){
	        	system("cls");
	        	exit(1);
			}
			
			break;
	 	default:
	 		printf("ERROR : Sorry I don't know the answer to this one!!!\n");
	 		printf("Press Any Key to continue . . .");
	 		getche();
	 		
	 		system("cls");
	 		
	 		/* Call Modul Welcome */
			Welcome();
			break;
	}
}
