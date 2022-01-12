/*
File Name		: reservation.h
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 08/12/2001
*/

#ifndef reservation_H
#define reservation_H

/* Struct Rent Room */
typedef struct {
	int Code;
	char Name[20];
	int Quantity;
	long int Price;
}RentRoom;

/* Struct Date */
typedef struct{
	int Day;
	int Month;
	int Year;
}Date;

/* Struct Reservation */
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

/* Menu Reservation */
int ReservationMenu();

/* Create Data Reservation */
void ReservationCreate();

/* Count Data Reservation */
void CountReservationData();

/* Show Data Reservation */
void ReservationData();

/* Read Data Reservation */
void ReservationRead();

/* Check Data Reservation by Code */
int CheckReservationCode(Reservation ReservationData, int ID);

/* Update Data Reservation */
void ReservationUpdate();
void UpdateReservationStatus();

/* Delete Data Reservation */
void ReservationDelete();
void AlertDeleteOneReservationData();
void DeleteOneReservationData(Reservation ReservationData, int ID);
void AlertDeleteAllReservationData();
void DeleteAllReservationData();

#endif
