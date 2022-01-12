/*
File Name		: report.h
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 08/12/2001
*/

#ifndef report_H
#define report_H

/* Menu Report Reservation */
void ReportMenu();

/* Filter Data Report Reservation by Day */
void ReservationReportDay();

/* Filter Data Report Reservation by Month */
void ReservationReportMonth();

/* Filter Data Report Reservation by Year */
void ReservationReportYear();

/* Show All Data Report Reservation */
void ReportShowAll();

/* Check Data Reservation by Date */
int CheckReservationDate(Reservation ReservationData, int Day, int Month, int Year);

#endif
