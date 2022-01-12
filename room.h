/*
File Name		: room.h
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 08/12/2001
*/

#ifndef room_H
#define room_H

#define JUM_BLOK 1

/* Struct Room */
typedef struct {
    int code; 
    char name[20]; 
    char type[15];
    unsigned int total;
    unsigned long int price;
}room;  

/* Menu Room */
int MenuRoom();

/* Create Data Room */
void CreateRoom();

/* Count Data Room */
void CountRoom();

/* Show Data Room */
void ShowRoom();

/* Read Data Room */
void ReadRoom();

/* Update Data Room */
void UpdateRoom();

/* Check Data Room by Code */
int CheckRoomCode(room roomdata, int id);

/* Delete Data Room */
void DeleteRoom();
void AlertDeleteOneRecordRoom();
void DeleteOneRecordRoom(room roomdata, int id);
void AlertDeleteAllRoom();
void DeleteAllRoom();

#endif
