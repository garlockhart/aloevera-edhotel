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
    int total;
    long int price;
}room;  

int RoomMenu();
void RoomCreate();
void RoomData();
void RoomRead();
void RoomUpdate();
int CheckRoomCode(room roomdata, int id);
void RoomDelete();
void AlertDeleteOneRoomData();
void DeleteOneRoomData(room roomdata, int id);
void AlertDeleteAllRoomData();
void DeleteAllRoomData();

#endif
