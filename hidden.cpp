/*
File Name		: hidden.cpp
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 07/01/2022
*/

/* ========== Header File ========== */
#include <stdio.h>
#include <conio.h>
#include "hidden.h"
/* ======= End of Header File ====== */

void HiddenPassword(char Text[50]){
	int i = 0;
	char Keyword;
	
	while(1)
	{
		Keyword = getch();
		
		if(Keyword == ENTER){
			Text[i] = '\0';
			break;
		} else if(Keyword == BACKSPACE){
			if(i > 0){
				i--;
				printf("\b \b");
			}
		} else if(Keyword == TAB || Keyword == SPACE){
			continue;
		} else{
			Text[i++] = Keyword;
			printf("* \b");
		}
	}
}
