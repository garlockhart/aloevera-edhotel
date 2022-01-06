/*
File Name		: reservation.h
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 08/12/2001
*/

#ifndef reservation_H
#define reservation_H

typedef struct {
	int Code;
	char Name[20];
	int Quantity;
	long int Price;
}RentRoom;

typedef struct{
	int Day;
	int Month;
	int Year;
}Date;

typedef struct {
	int ReservationCode;
	char NIN[16];
	char FullName[40];
	char Email[60];
	char Gender[10];
	int Age;
	RentRoom RentRoomData;
	int LongStay;
	Date CheckInDate;
	Date CheckOutDate;
	long int Total;
	int Discount;
	long int GrandTotal;
	Date ReservationDate;
	char Status[15];
}Reservation; 

int ReservationMenu();
void ReservationCreate();
void CountReservationData();
void ReservationData();
void ReservationRead();
int CheckReservationCode(Reservation ReservationData, int ID);
void ReservationUpdate();
void UpdateReservationStatus();
void ReservationDelete();
void AlertDeleteOneReservationData();
void DeleteOneReservationData(Reservation ReservationData, int ID);
void AlertDeleteAllReservationData();
void DeleteAllReservationData();

#endif
