/***************************************************************************************************
	PCF8563RTC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: PCF8563
Date:     29112022
***************************************************************************************************/
/*** Library ***/
#include "pcf8563rtc.h"

#if defined(__AVR_ATmega64__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
	#include "atmega328twi.h"
#elif #if defined(__AVR_ATmega324A__)
	#include "atmega328twi.h"
#else
	#error "MCU Lib not available"
#endif

/*** Procedure and Function declaration ***/
void PCF8563RTC_Init(void);
void PCF8563RTC_SetTime(uint8_t var_hour_u8, uint8_t var_min_u8, uint8_t var_sec_u8);
void PCF8563RTC_SetHour(uint8_t var_hour_u8);
void PCF8563RTC_SetMinute(uint8_t var_min_u8);
void PCF8563RTC_SetSecond(uint8_t var_sec_u8);
void PCF8563RTC_SetClkOut(uint8_t onoff, uint8_t freq);
void PCF8563RTC_SetDate(uint8_t var_day_u8, uint8_t var_weekday_u8, uint8_t var_month_u8, uint8_t var_year_u8);
void PCF8563RTC_SetDay(uint8_t var_day_u8);
void PCF8563RTC_SetWeekday(uint8_t var_weekday_u8);
void PCF8563RTC_SetMonth(uint8_t var_month_u8);
void PCF8563RTC_SetYear(uint8_t var_year_u8);
struct time PCF8563RTC_GetTime(void);
struct date PCF8563RTC_GetDate(void);
uint8_t PCF8563RTC_bcd2dec(uint8_t num);
uint8_t PCF8563RTC_bintobcd(uint8_t bin);

#ifdef _TWI_MODULE_

/*** Handler ***/
PCF8563RTC pcf8563rtc_enable(uint8_t prescaler)
{
	PCF8563RTC pcf;
	twi_enable('A', prescaler); // Initialize the I2c module.
	// Vtable
	pcf.SetTime = PCF8563RTC_SetTime;
	pcf.SetHour = PCF8563RTC_SetHour;
	pcf.SetMinute = PCF8563RTC_SetMinute;
	pcf.SetSecond = PCF8563RTC_SetSecond;
	pcf.SetClkOut = PCF8563RTC_SetClkOut;
	pcf.SetDate = PCF8563RTC_SetDate;
	pcf.SetDay = PCF8563RTC_SetDay;
	pcf.SetWeekday = PCF8563RTC_SetWeekday;
	pcf.SetMonth = PCF8563RTC_SetMonth;
	pcf.SetYear = PCF8563RTC_SetYear;
	pcf.GetTime = PCF8563RTC_GetTime;
	pcf.GetDate = PCF8563RTC_GetDate;
	pcf.bcd2dec = PCF8563RTC_bcd2dec;
	pcf.bintobcd = PCF8563RTC_bintobcd;
	
	PCF8563RTC_Init();
	
	return pcf;
}

/*** Procedure and Function definition ***/
// void PCF8563RTC_Init(uint8_t prescaler)
void PCF8563RTC_Init(void)
{
	twi()->start();									// Start I2C communication
	twi()->connect(PCF8563, TWI_WRITE);				// Connect to PCF8563 by sending its ID on I2c Bus
	twi()->master_write(PCF8563ControlRegAddress_U8);	// Select the PCF8563 ControlRegister to configure PCF8563
	twi()->master_write(0x00);							// Write 0x00 to Control register to disable SQW-Out
	twi()->stop();										// Stop I2C communication after initializing PCF8563
}
// void PCF8563RTC_SetTime(uint8_t var_hour_u8, uint8_t var_min_u8, uint8_t var_sec_u8)
void PCF8563RTC_SetTime(uint8_t var_hour_u8, uint8_t var_min_u8, uint8_t var_sec_u8)
{
	twi()->start();									// Start I2C communication
	twi()->connect(PCF8563, TWI_WRITE);				// connect to PCF8563 by sending its ID on I2c Bus
	twi()->master_write(PCF8563SecondRegAddress_U8);	// Select the SEC RAM address
	twi()->master_write(var_sec_u8);			        // Write sec from RAM address 02H
	twi()->master_write(var_min_u8);			        // Write min from RAM address 03H
	twi()->master_write(var_hour_u8);			        // Write hour from RAM address 04H
	twi()->stop();           							// Stop I2C communication after Setting the Time
}
// void PCF8563RTC_SetHour(uint8_t var_hour_u8)
void PCF8563RTC_SetHour(uint8_t var_hour_u8)
{
	twi()->start();									// Start I2C communication
	twi()->connect(PCF8563, TWI_WRITE);				// connect to PCF8563 by sending its ID on I2c Bus
	twi()->master_write(PCF8563HourRegAddress_U8);		// Select the SEC RAM address
	twi()->master_write(var_hour_u8);			        // Write hour from RAM address 04H
	twi()->stop();           							// Stop I2C communication after Setting the Time
}
// void PCF8563RTC_SetMinute(uint8_t var_min_u8)
void PCF8563RTC_SetMinute(uint8_t var_min_u8)
{
	twi()->start();									// Start I2C communication
	twi()->connect(PCF8563, TWI_WRITE);				// connect to PCF8563 by sending its ID on I2c Bus
	twi()->master_write(PCF8563MinuteRegAddress_U8);	// Select the SEC RAM address
	twi()->master_write(var_min_u8);			        // Write min from RAM address 03H
	twi()->stop();           							// Stop I2C communication after Setting the Time
}
// void PCF8563RTC_SetSecond(uint8_t var_sec_u8)
void PCF8563RTC_SetSecond(uint8_t var_sec_u8)
{
	twi()->start();									// Start I2C communication
	twi()->connect(PCF8563, TWI_WRITE);				// connect to PCF8563 by sending its ID on I2c Bus
	twi()->master_write(PCF8563SecondRegAddress_U8);	// Select the SEC RAM address
	twi()->master_write(var_sec_u8);			        // Write sec from RAM address 02H
	twi()->stop();           							// Stop I2C communication after Setting the Time
}
// void PCF8563RTC_SetClkOut(uint8_t onoff, uint8_t freq)
void PCF8563RTC_SetClkOut(uint8_t onoff, uint8_t freq)
{
	uint8_t word = 0;
	if(onoff)
		word = 0x80 | (freq & 0x03);
	twi()->start();								// Start I2C communication
	twi()->connect(PCF8563, TWI_WRITE);			// connect to PCF8563 by sending its ID on I2c Bus
	twi()->master_write(PCF8563CLKOUT_control_U8);	// Select the CLKOUT RAM address
	twi()->master_write(word);						// Write Clock from RAM address 0DH						
	twi()->stop();           						// Stop I2C communication after Setting the Time
}
// void PCF8563RTC_SetDate(uint8_t var_day_u8, uint8_t var_weekday_u8, uint8_t var_month_u8, uint8_t var_year_u8)
void PCF8563RTC_SetDate(uint8_t var_day_u8, uint8_t var_weekday_u8, uint8_t var_month_u8, uint8_t var_year_u8)
{
	twi()->start();								// Start I2C communication
	twi()->connect(PCF8563, TWI_WRITE);			// connect to PCF8563 by sending its ID on I2c Bus
	twi()->master_write(PCF8563DayRegAddress_U8);  // Request DAY RAM address at 05H
	twi()->master_write(var_day_u8);				// Write date on RAM address 05H
	twi()->master_write(var_weekday_u8);			// Write date on RAM address 06H
	twi()->master_write(var_month_u8);				// Write month on RAM address 07H
	twi()->master_write(var_year_u8);				// Write year on RAM address 08h
	twi()->stop();									// Stop I2C communication after Setting the Date
}
// void PCF8563RTC_SetYear(uint8_t var_year_u8)
void PCF8563RTC_SetYear(uint8_t var_year_u8)
{
	twi()->start();								// Start I2C communication
	twi()->connect(PCF8563, TWI_WRITE);			// connect to PCF8563 by sending its ID on I2c Bus
	twi()->master_write(PCF8563YearRegAddress_U8);	// Request DAY RAM address at 08H
	twi()->master_write(var_year_u8);			    // Write year on RAM address 08h
	twi()->stop();									// Stop I2C communication after Setting the Date
}
// void PCF8563RTC_SetMonth(uint8_t var_month_u8)
void PCF8563RTC_SetMonth(uint8_t var_month_u8)
{
	twi()->start();									// Start I2C communication
	twi()->connect(PCF8563, TWI_WRITE);				// connect to PCF8563 by sending its ID on I2c Bus
	twi()->master_write(PCF8563MonthRegAddress_U8);	// Request DAY RAM address at 07H
	twi()->master_write(var_month_u8);					// Write month on RAM address 07H
	twi()->stop();										// Stop I2C communication after Setting the Date
}
// void PCF8563RTC_SetWeekday(uint8_t var_weekday_u8)
void PCF8563RTC_SetWeekday(uint8_t var_weekday_u8)
{
	twi()->start();									// Start I2C communication
	twi()->connect(PCF8563, TWI_WRITE);				// connect to PCF8563 by sending its ID on I2c Bus
	twi()->master_write(PCF8563WeekdayRegAddress_U8);  // Request DAY RAM address at 06H
	twi()->master_write(var_weekday_u8);               // Write date on RAM address 06H
	twi()->stop();										// Stop I2C communication after Setting the Date
}
// void PCF8563RTC_SetDay(uint8_t var_day_u8)
void PCF8563RTC_SetDay(uint8_t var_day_u8)
{
	twi()->start();								// Start I2C communication
	twi()->connect(PCF8563, TWI_WRITE);			// connect to PCF8563 by sending its ID on I2c Bus
	twi()->master_write(PCF8563DayRegAddress_U8);  // Request DAY RAM address at 05H
	twi()->master_write(var_day_u8);			    // Write date on RAM address 05H
	twi()->stop();									// Stop I2C communication after Setting the Date
}
// struct time PCF8563RTC_GetTime(void)
struct time PCF8563RTC_GetTime(void)
{
	struct time result;
	twi()->start();											// Start I2C communication
	twi()->connect(PCF8563, TWI_WRITE);						// connect to PCF8563 by sending its ID on I2c Bus
	twi()->master_write(PCF8563SecondRegAddress_U8);			// Request Sec RAM address at 00H
	twi()->stop();												// Stop I2C communication after selecting Sec Register
	twi()->start();											// Start I2C communication
	twi()->connect(PCF8563, TWI_READ);							// connect to PCF8563(Read mode) by sending its ID
	result.VL_seconds = twi()->master_read(TWI_ACK) & ~0x80;	// read second and return Positive ACK
	result.minutes = twi()->master_read(TWI_ACK) & ~0x80;		// read minute and return Positive ACK
	result.hours = twi()->master_read(TWI_NACK) & ~0xC0;		// read hour and return Negative/No ACK
	twi()->stop();												// Stop I2C communication after reading the Time
	return result;
}
// struct date PCF8563RTC_GetDate(void)
struct date PCF8563RTC_GetDate(void)
{
	struct date result;
	twi()->start();												// Start I2C communication
	twi()->connect(PCF8563, TWI_WRITE);							// connect to PCF8563 by sending its ID on I2c Bus
	twi()->master_write(PCF8563DayRegAddress_U8);					// Request DAY RAM address at 04H
	twi()->stop();													// Stop I2C communication after selecting DAY Register
	twi()->start();												// Start I2C communication
	twi()->connect(PCF8563, TWI_READ);								// connect to PCF8563 (Read mode) by sending its ID
	result.days = twi()->master_read(TWI_ACK) & ~0xC0;				// read Day and return Positive ACK
	result.weekdays = twi()->master_read(TWI_ACK) & ~0xF8;			// read Month and return Positive ACK
	result.century_months = twi()->master_read(TWI_ACK) & ~0xE0;
	result.years = twi()->master_read(TWI_NACK);				    // read Year and return Negative/No ACK
	twi()->stop();													// Stop I2C communication after reading the Date
	return result;
}

#endif

// uint8_t PCF8563RTC_bcd2dec(uint8_t num)
uint8_t PCF8563RTC_bcd2dec(uint8_t num)
{
	return ((num / 16 * 10) + (num % 16));
}
// uint8_t PCF8563RTC_bintobcd(uint8_t bin)
uint8_t PCF8563RTC_bintobcd(uint8_t bin)
{
	return (((bin) / 10) << 4) + ((bin) % 10);
}

/*** EOF ***/

