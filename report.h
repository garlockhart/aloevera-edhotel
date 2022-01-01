/*
File Name		: report.h
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 08/12/2001
*/

#ifndef report_H
#define report_H

void ReportMenu();
void ReservationReport_Day();
void ReservationReport_Month();
void ReservationReport_Year();
void ReportShowAll();
int CheckReservationDate(Reservation ReservationData, int day, int month, int year);

#endif
