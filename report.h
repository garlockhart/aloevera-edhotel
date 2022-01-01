/*
File Name		: report.h
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 08/12/2001
*/

#ifndef report_H
#define report_H

void ReportMenu();
void ReservationReportDay();
void ReservationReportMonth();
void ReservationReportYear();
void ReportShowAll();
int CheckReservationDate(Reservation ReservationData, int Day, int Month, int Year);

#endif
