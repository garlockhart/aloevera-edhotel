/*
File Name		: reservation.h
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 08/12/2001
*/

#ifndef reservation_H
#define reservation_H

typedef struct {
	int code;
	char name[20];
	int quantity;
	long int price;
}rentroom;

typedef struct{
	int day;
	int month;
	int year;
}date;

typedef struct {
	int code;
	long int nationalidentitynumber;
	char fullname[40];
	char email[60];
	char gender[10];
	int age;
	rentroom rentroomdata;
	date datedata;
	long int total;
	float discount;
	long int grandtotal;
}reservation; 

int ReservationMenu();
void ReservationCreate();
void ReservationData();
void ReservationRead();
void ReservationUpdate();
int CheckReservationCode(reservation reservationdata, int id);
void ReservationDelete();
void AlertDeleteOneReservData();
void DeleteOneReservData(reservation reservationdata, int id);
void AlertDeleteAllReservData();
void DeleteAllReservData();

#endif
