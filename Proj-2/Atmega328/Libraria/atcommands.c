/*************************************************************************
	ATCOMMANDS
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: ALL
Date: 01122022
Comment:
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

/*** File Constant & Macro ***/

/*** File Variable ***/

/*** File Header ***/

/*** Procedure & Function ***/
char* BT05ATcmd(uint16_t num){
	char* ATstr = NULL;
	switch(num)
	{
		case 1:
			ATstr = "AT\r\n";
		break;
		case 2:
			ATstr = "AT+VERSION\r\n";
		break;
		case 3:
			ATstr = "AT+NAME\r\n"; // Param ? module Bluetooth name Default: MLT-BT05 longest ? 18 byte
		break;
		case 4:
			ATstr = "AT+PIN\r\n"; // Param ? 6 byte bit pairing password default “? 123456”
		break;
		case 5: // Very usefull
			ATstr = "AT+GETSTAT\r\n"; // Param ? 0-1 , 0——not connected, 1——connected
		break;
		case 10:
			ATstr = "AT+ROLE\r\n"; // Param ?? 0-4 ?0 ——slave mode?, 1 ——master mode?, 2 ——sensor mode, 3 ——iBeacon mode, 4 ——WeChat mode, default ? 0
		break;
		case 101:
			ATstr = "AT+ROLE0\r\n"; // 0 ——slave mode
		break;
		case 102:
			ATstr = "AT+ROLE1\r\n"; // 1 ——master mode
		break;
		case 103:
			ATstr = "AT+ROLE2\r\n"; // 2 ——sensor mode
		break;
		case 104:
			ATstr = "AT+ROLE3\r\n"; // 3 ——iBeacon mode
		break;
		case 105:
			ATstr = "AT+ROLE4\r\n"; // 4 ——WeChat mode
		case 11:
			ATstr = "AT+LADDR\r\n";
		break;
		case 12:
			ATstr = "AT+ADVI\r\n"; // 0 ——100ms,1 ——500ms,2 ——7500ms,3 ——1000ms,4 ——2000ms,5 ——4000ms,6 ——8000ms
		break;
		case 121:
			ATstr = "AT+ADVI0\r\n"; // 0 ——100ms
		break;
		case 122:
			ATstr = "AT+ADVI1\r\n"; // 1 ——500ms
		break;
		case 123:
			ATstr = "AT+ADVI2\r\n"; // 2 ——7500ms
		break;
		case 124:
			ATstr = "AT+ADVI3\r\n"; // 3 ——1000ms
		break;
		case 125:
			ATstr = "AT+ADVI4\r\n"; // 4 ——2000ms
		break;
		case 126:
			ATstr = "AT+ADVI5\r\n"; // 5 ——4000ms
		break;
		case 127:
			ATstr = "AT+ADVI6\r\n"; // 6 ——8000ms
		break;
		case 13:
			ATstr = "AT+TYPE\r\n"; // 0——no password,1——password pairing,2——password pairing and binding, default ? 0
		break;
		case 131:
			ATstr = "AT+TYPE0\r\n"; // 0——no password
		break;
		case 132:
			ATstr = "AT+TYPE1\r\n"; // 1——password pairing
		break;
		case 133:
			ATstr = "AT+TYPE2\r\n"; // 2——password pairing and binding
		break;
		case 14:
			ATstr = "AT+BAUD\r\n"; // 0 ——115200,1 ——57600,2 ——38400,3 ——19200,4 —— 9600, default ? 0
		break;
		case 141: // zs-040: works. 1200 hidden
			//ATstr = "AT+BAUD1\r\n";
		break;
		case 142: // zs-040: works. 2400 hidden
			//ATstr = "AT+BAUD2\r\n";
		break;
		case 143: // zs-040: works. 4800 hidden
			//ATstr = "AT+BAUD3\r\n";
		break;
		case 144: // zs-040: works. 9600 hidden
			//ATstr = "AT+BAUD4\r\n";
		break;
		case 145: // zs-040: works. 19200 hidden
			//ATstr = "AT+BAUD5\r\n";
		break;
		case 146: // zs-040: works. 38400 hidden
			ATstr = "AT+BAUD6\r\n";
		break;
		case 147: // zs-040: works. 57600 hidden
			//ATstr = "AT+BAUD7\r\n";
		break;
		case 148: // zs-040: works. 115200 hidden
			//ATstr = "AT+BAUD8\r\n";
		break;
		case 15:
			ATstr = "AT+UUID\r\n"; // Param: 0x0001~0xFFFE, default ? 0xFFE0
		break;
		case 16:
			ATstr = "AT+CHAR\r\n"; // Param:0x0001~0xFFFE, default ? 0xFFE1
		break;
		case 17:
			ATstr = "AT+IBSUUID\r\n"; // Param ?FDA50693A4E24FB1AFCFC6EB07647825
		break;
		case 18:
			ATstr = "AT+MAJOR\r\n"; // Param : 0x0001~0xFFFE, default ? 0x0007
		break;
		case 19:
			ATstr = "AT+MINOR\r\n"; // Param: 0x0001~0xFFFE, default ? 0x000A
		break;
		case 20:
			ATstr = "AT+SLEEP\r\n"; // when PM=1.
		break;
		case 21:
			ATstr = "AT+INQ\r\n"; // Param ? 1-0, 1: start scanning, 0: stop scanning
		break;
		case 211:
			ATstr = "AT+INQ0\r\n"; // 0: stop scanning
		break;
		case 212:
			ATstr = "AT+INQ1\r\n"; // 1: start scanning
		break;
		case 22:
			//ATstr = "AT+CONN<Param>\r\n"; // Param ? 0-7
		break;
		case 23:
			//ATstr = "AT+RSLV< Param >\r\n"; // Param ? ( 0-7 )
		break;
		case 24:
			ATstr = "AT+BAND\r\n"; // Param ? MAC address
		break;
		case 25:
			ATstr = "AT+CLRBAND\r\n"; // no
		break;
		case 26:
			//ATstr = "AT+GETDCN<Param>\r\n"; // Param ?? 1-8 ?
		break;
		case 27:
			ATstr = "AT+DISC\r\n"; // Disconnect no
		break;
		case 28:
			//ATstr = "AT+AT_WXSWH<Param>\r\n"; // Param ?? 0-1), 0 ? H5 communication, 1 ? factory server, Default: 0
		break;
		case 29:
			ATstr = "AT+RESET\r\n";
		break;
		case 30: // hiden
			//ATstr = "AT+DEFAULT\r\n"; // 4dbm, 9600bps (115200bps), 200ms, PM=0, Onboard LED 2:1, External indicator led1: 2
		break;
		case 31:
			ATstr = "AT+HELP\r\n"; // Lists commands
		break;
		case 801:
			ATstr = "AT+PIN123456\r\n";
		break;
		case 802:
			ATstr = "AT+PIN654321\r\n";
		break;
		case 803:
			ATstr = "AT+PIN916919\r\n";
		break;
		case 901:
			ATstr = "AT+NAMEBT05\r\n"; // Param ? module Bluetooth name Default: BT05 longest ? 18 byte
		break;
		case 902:
			ATstr = "AT+NAMEHome1\r\n"; // Param ? module Bluetooth name Default: BT05 longest ? 18 byte
		break;
		case 903:
			ATstr = "AT+NAMEHome2\r\n"; // Param ? module Bluetooth name Default: BT05 longest ? 18 byte
		break;
		case 904:
			ATstr = "AT+NAMEHome3\r\n"; // Param ? module Bluetooth name Default: BT05 longest ? 18 byte
		break;
		case 905:
			ATstr = "AT+NAMEHome4\r\n"; // Param ? module Bluetooth name Default: BT05 longest ? 18 byte
		break;
		/******/
		default:
			ATstr = "AT\r\n";
		break;
	};
	return ATstr;
}

char* HC42ATcmd(uint16_t num){
	char* ATstr = NULL;
	switch(num)
	{
		case 1: // zs-040: works.
			ATstr = "AT\r\n";
		break;
		case 2: // zs-040: works.
			ATstr = "AT+VERSION\r\n";
		break;
		case 3: // zs-040 works
			ATstr = "AT+NAME=HC42\r\n";
		break;
		case 4:
			ATstr = "AT+RFPM=4\r\n"; // 4dBm (4, 3, 0, -4, -8, -12, -16, -20, -40)
		break;
		case 5:
			ATstr = "AT+UART=9600\r\n"; // ( 1200,2400,4800,9600,19200,38400, 57600,115200,230400 )
		break;
		case 6:
			ATstr = "AT+UART=38400\r\n"; // ( 1200,2400,4800,9600,19200,38400, 57600,115200,230400 )
		break;
		case 7:
			ATstr = "AT+PM\r\n";
		break;
		case 8:
			ATstr = "AT+PM=0\r\n"; // power consumption 0 or 1.
		break;
		case 9: // zs-040 works
			ATstr = "AT+SLEEP\r\n"; // when PM=1.
		break;
		case 10:
			ATstr = "AT+PD\r\n"; // shutdown command
		break;
		case 11:
			ATstr = "AT+LEDnM\r\n"; // (1-off, 2-depends power consumption, 3-on)
		break;
		case 12:
			ATstr = "AT+LEDnM=2\r\n"; // research choices ? (1-off, 2-depends power consumption, 3-on)
		break;
		case 13: // zs-040 works
			ATstr = "AT+DEFAULT\r\n"; // 4dbm, 9600bps (115200bps), 200ms, PM=0, Onboard LED 2:1, External indicator led1: 2
		break;
		case 14: // zs-040 works
			ATstr = "AT+ROLE\r\n"; // S or P, M or C
		break;
		case 15:
			ATstr = "AT+ROLE=S\r\n"; // S or P, M or C (slave or master)
		break;
		case 16: // zs-040 works
			ATstr = "AT+RESET\r\n";
		break;
		case 17:
			ATstr = "AT+IBEN\r\n"; // 0?OFF)
		break;
		case 18:
			ATstr = "AT+IBEN=0\r\n"; // 0?OFF) 1 (on)
		break;
		case 19:
			ATstr = "AT+IBUUID\r\n"; // inquire.
		break;
		case 20:
			ATstr = "AT+IBUUID=FDA50693-A4E2-4FB1-AFCF-C6EB07647825\r\n"; // example: FDA50693-A4E2-4FB1-AFCF-C6EB07647825
		break;
		case 21:
			ATstr = "AT+IBRSSI\r\n"; // 0xC3
		break;
		case 22:
			ATstr = "AT+IBRSSI=0xC3\r\n"; // 0xC3
		break;
		case 23:
			ATstr = "AT+IBMAJ\r\n"; // 0x27C6
		break;
		case 24:
			ATstr = "AT+IBMAJ=0x27C6\r\n"; // 0x27C6 (default)
		break;
		case 25:
			ATstr = "AT+IBMIN\r\n"; // 0x8B06
		break;
		case 26:
			ATstr = "AT+IBMIN=1234\r\n"; // 0x8B06 (default)
		break;
		case 27:
			ATstr = "AT+AINT\r\n"; // 200ms
		break;
		case 28:
			ATstr = "AT+AINT=200\r\n"; // 20ms-10000ms
		break;
		case 29:
			ATstr = "AT+HELP\r\n"; // Lists commands
		break;
		/******/
		default:
			ATstr = "AT\r\n";
		break;
	};
	return ATstr;
}

char* HC05ATcmd(uint16_t num){
	char* ATstr = NULL;
	switch(num)
	{
		case 1: // zs-040: works.
			ATstr = "AT\r\n";
		break;
		case 2: // zs-040: works.
			ATstr = "AT+VERSION?\r\n";
		break;
		case 3:
			ATstr = "AT+ORGL\r\n";
		break;
		case 4:
			ATstr = "AT+ADDR?\r\n";
		break;
		case 5: // zs-040: works
			ATstr = "AT+NAME=HC05\r\n";
		break;
		case 6: //This clears name if ends with '?'.
			ATstr = "AT+NAME?\r\n";
		break;
		case 7:
			ATstr = "AT+RNAME?0002,72,od2224\r\n";
		break;
		case 8: // ZS-040 WORKS
			ATstr = "AT+ROLE0\r\n";
		break;
		case 9:
			ATstr = "AT+ROLE?\r\n"; // 0 -> Slave, 1 -> Master, 2 -> Slave-Loop
		break;
		case 10:
			ATstr = "AT+CLASS=Param1\r\n";
		break;
		case 11:
			ATstr = "AT+CLASS?\r\n";
		break;
		case 12:
			ATstr = "AT+IAC=9e8b3f\r\n";
		break;
		case 13:
			ATstr = "AT+IAC?\r\n";
		break;
		case 14:
			ATstr = "AT+INQM=1,9,48\r\n";
		break;
		case 15:
			ATstr = "AT+INQM\r\n";
		break;
		case 16: // zs-040: not work
			ATstr = "AT+PWD:1234\r\n ";
		break;
		case 17: // zs-040: not work
			ATstr = "AT+PSWD?\r\n";
		break;
		case 18: // zs-040: not work
			ATstr = "AT+UART=9600,0,0,\r\n";
		break;
		case 19:
			ATstr = "AT+UART?\r\n";
		break;
		case 20:
			ATstr = "AT+CMODE=2\r\n";
		break;
		case 21:
			ATstr = "AT+CMODE?\r\n";
		break;
		case 22:
			ATstr = "AT+BIND=1234,56,abcdef\r\n";
		break;
		case 23:
			ATstr = "AT+BIND?\r\n";
		break;
		case 24:
			ATstr = "AT+POLAR=0,1\r\n";
		break;
		case 25:
			ATstr = "AT+POLAR?\r\n";
		break;
		case 26:
			ATstr = "AT+PI0=10,1\r\n";
		break;
		case 27:
			ATstr = "AT+PI0=10,0\r\n";
		break;
		case 28:
			ATstr = "AT+MPI0=404\r\n";
		break;
		case 29:
			ATstr = "AT+PI0=004\r\n";
		break;
		case 30:
			ATstr = "AT+PI0=400\r\n";
		break;
		case 31:
			ATstr = "AT+MPI0=0\r\n";
		break;
		case 32:
			ATstr = "AT+MPIO?\r\n";
		break;
		case 33:
			ATstr = "AT+IPSCAN=1234,500,1200,250\r\n";
		break;
		case 34:
			ATstr = "AT+IPSCAN?\r\n";
		break;
		case 35:
			ATstr = "AT+SNIFF=Param1,Param2,Param3,Param4";
		break;
		case 36:
			ATstr = "AT+SNIFF?\r\n";
		break;
		case 37:
			ATstr = "AT+SENM=Param1,Param2\r\n";
		break;
		case 38:
			ATstr = "AT+SENM?\r\n";
		break;
		case 39:
			ATstr = "AT+RMSAD=1234,56,abcdef\r\n";
		break;
		case 40:
			ATstr = "AT+RMAAD\r\n";
		break;
		case 41:
			ATstr = "AT+FSAD=1234,56,abcdef\r\n";
		break;
		case 42:
			ATstr = "AT+ADCN?\r\n";
		break;
		case 43:
			ATstr = "AT+MRAD?\r\n";
		break;
		case 44:
			ATstr = "AT+STATE?\r\n";
		break;
		case 45:
			ATstr = "AT+INIT\r\n";
		break;
		case 46:
			ATstr = "AT+IAC=9e8b33\r\n";
		break;
		case 47:
			ATstr = "AT+CLASS=0\r\n";
		break;
		case 48:
			ATstr = "AT+INQM=1,3,48\r\n";
		break;
		case 49: // vs-040: works
			ATstr = "AT+INQ\r\n";
		break;
		case 50:
			ATstr = "AT+PAIR=1234,56,abcdef,20\r\n";
		break;
		case 51:
			ATstr = "AT+FSAD=1234,56,abcdef\r\n";
		break;
		case 52:
			ATstr = "AT+LINK=1234,56,abcdef\r\n";
		break;
		case 53:
			ATstr = "AT+DISC\r\n";
		break;
		case 54:
			ATstr = "AT+ENSNIFF=Param1\r\n";
		break;
		case 55:
			ATstr = "AT+EXSNIFF=Param1";
		break;
		case 56: // zs-040: works.
			ATstr = "AT+RESET\r\n";
		break;
		case 57:
			ATstr = "AT+HELP\r\n"; // Lists commands
		break;
		default:
			ATstr = "AT\r\n";
		break;
	};
	return ATstr;
}

/***File Interrupt***/

/***EOF***/

