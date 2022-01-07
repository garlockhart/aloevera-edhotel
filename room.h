/*
File Name		: room.h
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 08/12/2001
*/

#ifndef room_H
#define room_H

#define JUM_BLOK 1

typedef struct {
    int code; 
    char name[20]; 
    char type[15];
    unsigned int total;
    unsigned long int price;
}room;  

int MenuRoom();
void CreateRoom();
void CountRoom();
void ShowRoom();
void ReadRoom();
void UpdateRoom();
int CheckRoomCode(room roomdata, int id);
void DeleteRoom();
void AlertDeleteOneRecordRoom();
void DeleteOneRecordRoom(room roomdata, int id);
void AlertDeleteAllRoom();
void DeleteAllRoom();

#endif
