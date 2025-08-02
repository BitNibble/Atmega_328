/*************************************************************************
	ATCOMMANDS
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: ALL
Date:     24042023
*************************************************************************/
/****** Comment:
	Stable
*************************************************************************/
/*** File Library ***/
#include "atcommands.h"
//#include <util/delay.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
//#include <stdarg.h>
//#include <math.h>

/*** File Variable ***/
char HC42ATstr[32];
char ESP8266str[32];

/*** Procedure & Function ***/
char* hc42at_cmd(uint16_t num){
	switch(num)
	{
		case 1: // zs-040: works.
			strcpy(HC42ATstr, "AT\r\n");
		break;
		case 2: // zs-040: works.
			strcpy(HC42ATstr, "AT+VERSION\r\n");
		break;
		case 3: // zs-040 works
			strcpy(HC42ATstr, "AT+NAME=HC42\r\n");
		break;
		case 4:
			strcpy(HC42ATstr, "AT+RFPM=4\r\n"); // 4dBm (4, 3, 0, -4, -8, -12, -16, -20, -40)
		break;
		case 5:
			strcpy(HC42ATstr, "AT+UART=9600\r\n"); // ( 1200,2400,4800,9600,19200,38400, 57600,115200,230400 )
		break;
		case 6:
			strcpy(HC42ATstr, "AT+UART=38400\r\n"); // ( 1200,2400,4800,9600,19200,38400, 57600,115200,230400 )
		break;
		case 7:
			strcpy(HC42ATstr, "AT+PM\r\n");
		break;
		case 8:
			strcpy(HC42ATstr, "AT+PM=0\r\n"); // power consumption 0 or 1.
		break;
		case 9: // zs-040 works
			strcpy(HC42ATstr, "AT+SLEEP\r\n"); // when PM=1.
		break;
		case 10:
			strcpy(HC42ATstr, "AT+PD\r\n"); // shutdown command
		break;
		case 11:
			strcpy(HC42ATstr, "AT+LEDnM\r\n"); // (1-off, 2-depends power consumption, 3-on)
		break;
		case 12:
			strcpy(HC42ATstr, "AT+LEDnM=2\r\n"); // research choices ? (1-off, 2-depends power consumption, 3-on)
		break;
		case 13: // zs-040 works
			strcpy(HC42ATstr, "AT+DEFAULT\r\n"); // 4dbm, 9600bps (115200bps), 200ms, PM=0, Onboard LED 2:1, External indicator led1: 2
		break;
		case 14: // zs-040 works
			strcpy(HC42ATstr, "AT+ROLE\r\n"); // S or P, M or C
		break;
		case 15:
			strcpy(HC42ATstr, "AT+ROLE=S\r\n"); // S or P, M or C (slave or master)
		break;
		case 16: // zs-040 works
			strcpy(HC42ATstr, "AT+RESET\r\n");
		break;
		case 17:
			strcpy(HC42ATstr, "AT+IBEN\r\n"); // 0?OFF)
		break;
		case 18:
			strcpy(HC42ATstr, "AT+IBEN=0\r\n"); // 0?OFF) 1 (on)
		break;
		case 19:
			strcpy(HC42ATstr, "AT+IBUUID\r\n"); // inquire.
		break;
		case 20:
			strcpy(HC42ATstr, "AT+IBUUID=FDA50693-A4E2-4FB1-AFCF-C6EB07647825\r\n"); // example: FDA50693-A4E2-4FB1-AFCF-C6EB07647825
		break;
		case 21:
			strcpy(HC42ATstr, "AT+IBRSSI\r\n"); // 0xC3
		break;
		case 22:
			strcpy(HC42ATstr, "AT+IBRSSI=0xC3\r\n"); // 0xC3
		break;
		case 23:
			strcpy(HC42ATstr, "AT+IBMAJ\r\n"); // 0x27C6
		break;
		case 24:
			strcpy(HC42ATstr, "AT+IBMAJ=0x27C6\r\n"); // 0x27C6 (default)
		break;
		case 25:
			strcpy(HC42ATstr, "AT+IBMIN\r\n"); // 0x8B06
		break;
		case 26:
			strcpy(HC42ATstr, "AT+IBMIN=1234\r\n"); // 0x8B06 (default)
		break;
		case 27:
			strcpy(HC42ATstr, "AT+AINT\r\n"); // 200ms
		break;
		case 28:
			strcpy(HC42ATstr, "AT+AINT=200\r\n"); // 20ms-10000ms
		break;
		case 29:
			strcpy(HC42ATstr, "AT+HELP\r\n"); // Lists commands
		break;
		/******/
		default:
			strcpy(HC42ATstr, "AT\r\n");
		break;
	};
	return HC42ATstr;
}

char* esp8266_cmd(uint16_t num)
{
	switch(num)
	{
		case 1:
			strcpy(ESP8266str, "AT\r\n");
		break;
		
		
		
		case 99:
			strcpy(ESP8266str, "AT+RST\r\n");
		break;
		default:
			strcpy(ESP8266str, "AT\r\n");
		break;
	};
	
	/***
	Firmware version AT+GMR AT+GMR 0018000902 OK
	
	List Access Points AT+CWLAP AT+CWLAP +CWLAP:(4,"RochefortSurLac",-
	38,"70:62:b8:6f:6d:58",1)
	+CWLAP:(4,"LiliPad2.4",-83,"f8:7b:8c:1e:7c:6d",1)
	OK
	
	Join Access Point AT+CWJAP?
	AT+CWJAP="SSID","Password"
	Query AT+CWJAP? +CWJAP:"RochefortSurLac" OK
	
	Quit Access Point AT+CWQAP=?
	AT+CWQAP
	Query
	OK
	
	Get IP Address AT+CIFSR AT+CIFSR 192.168.0.105
	OK
	
	Set Parameters of
	Access Point
	AT+ CWSAP?
	AT+ CWSAP= <ssid>,<pwd>,<chl>, <ecn>
	Query
	ssid, pwd
	chl = channel, ecn = encryption
	
	WiFi Mode AT+CWMODE?
	AT+CWMODE=1
	AT+CWMODE=2
	AT+CWMODE=3
	Query
	STA
	AP
	BOTH
	
	Set up TCP or UDP
	connection
	AT+CIPSTART=?
	(CIPMUX=0) AT+CIPSTART =
	<type>,<addr>,<port>
	(CIPMUX=1) AT+CIPSTART=
	<id><type>,<addr>, <port>
	Query
	id = 0-4, type = TCP/UDP, addr = IP address, port= port
	
	TCP/UDP
	Connections
	AT+ CIPMUX?
	AT+ CIPMUX=0
	AT+ CIPMUX=1
	Query
	Single
	Multiple
	
	Check join devices' IP AT+CWLIF
	
	TCP/IP Connection
	Status
	AT+CIPSTATUS AT+CIPSTATUS? no this fun
	
	Send TCP/IP data (CIPMUX=0) AT+CIPSEND=<length>;
	(CIPMUX=1) AT+CIPSEND= <id>,<length>
	
	Close TCP / UDP
	connection
	AT+CIPCLOSE=<id> or AT+CIPCLOSE
	
	Set as server AT+ CIPSERVER= <mode>[,<port>] mode 0 to close server mode; mode 1 to open; port = port
	
	Set the server
	timeout
	AT+CIPSTO?
	AT+CIPSTO=<time>
	Query
	<time>0~28800 in seconds
	
	Baud Rate* AT+CIOBAUD?
	Supported: 9600, 19200, 38400, 74880,
	115200, 230400, 460800, 921600
	Query AT+CIOBAUD? +CIOBAUD:9600 OK
	
	Check IP address AT+CIFSR AT+CIFSR 192.168.0.106
	OK
	
	Firmware Upgrade
	(from Cloud)
	AT+CIUPDATE 1. +CIPUPDATE:1 found server
	2. +CIPUPDATE:2 connect server
	3. +CIPUPDATE:3 got edition
	4. +CIPUPDATE:4 start update
	
	Received data +IPD (CIPMUX=0): + IPD, <len>:
	(CIPMUX=1): + IPD, <id>, <len>: <data>
	
	Watchdog Enable* AT+CSYSWDTENABLE Watchdog, auto restart when program errors occur: enable
	
	Watchdog Disable* AT+CSYSWDTDISABLE Watchdog, auto restart when program errors occur: disable
	***/
	
	return NULL;
}

/***File Interrupt***/

/*** EOF ***/

