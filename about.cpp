/*
File Name		: about.cpp
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 08/12/2001
*/

/* ========== Header File ========== */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "welcome.h"
/* ======= End of Header File ====== */

int About(){
	printf("   ==================== WELCOME TO ALOEVERA EDHOTEL ====================\n");
	printf("   |\t\t\t\t\t\t\t\t\t|");
	printf("\n   |\t\t\t>>>Apa itu Aloevera Edhotel<<<\t\t\t|\n");
	printf("   |\t\t\t\t\t\t\t\t\t|");
	printf("\n   |\t   Aloevera Edhotel merupakan sistem reservasi hotel yang \t|\n");
	printf("   |\tbertujuan untuk mempermudah pemesanan kamar hotel agar lebih\t|\n");
	printf("   |\tterstruktur. Sistem ini dibuat dengan bahasa pemprograman C.\t|\n");
	printf("   |\t\t\t\t\t\t\t\t\t|");
	printf("\n   |\t\t\t   \t >>>VISI<<<   \t  \t\t\t|\n");
	printf("   |\tLorem ipsum dolor sit amet, consectetur adipiscing elit, \t|\n");
	printf("   | sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. |");
	printf("\n   |\t\t\t   \t >>>MISI<<<   \t  \t\t\t|\n");
	printf("   |\tLorem ipsum dolor sit amet, consectetur adipiscing elit, \t|\n");
	printf("   | sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. |\n");
	printf("   |\t\t\t\t\t\t\t\t\t|");
	printf("\n");	
	printf("   |\t    	  Copyright 2021 - Develop by Nedersoft      	 \t|");
	printf("\n   |\t\t\t    By Kelompok B4 PTIK    \t\t\t|");
	printf("\n   |\t\t\t\tGarly Nugraha\t\t\t\t|");
	printf("\n   |\t\t\t   Nazwa Fitriyani Zahra\t\t\t|\n");
	printf("   |\t\t\t\t\t\t\t\t\t|");
	printf("\n\n");
	printf("Press Any Key to continue . . .");
	getche();
	
	system("cls");
	Welcome();
}

