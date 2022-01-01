/*
File Name		: compare.cpp
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 01/01/2022
*/

#include <stdio.h> 

int StringCompare(char *a,char *b)  
{  
    int flag = 0;  
    while(*a != '\0' && *b != '\0') 
    {  
        if(*a != *b)  
        {  
            flag = 1;  
        }  
        a++;  
        b++;  
    }  

    if(flag == 0) {
        return 0;  
    } 
    else {
        return 1;  
    }
} 
