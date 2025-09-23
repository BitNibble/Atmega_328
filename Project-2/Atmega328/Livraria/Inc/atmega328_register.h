/************************************************************************
	ATMEGA 328P REGISTER
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega 328 by ETT ET-BASE
Date:   06122024
************************************************************************/
#ifndef _ATMEGA328_REGISTER_H_
	#define _ATMEGA328_REGISTER_H_

/*** Compiler ***/
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

/*** Library ***/
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

/*** Base Type ***/
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} U_byte;

typedef union {
	struct{
		uint8_t l;
		uint8_t h;
	}par;
	uint16_t var;
} U_word;

/*****************************/
/*****      REGISTER      ****/
/*****************************/
// Reserved 0x20
// Reserved 0x21
// Reserved 0x22
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} PIN_b; //0x23
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} DD_rb; // 0x24
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} PORT_b; // 0x25
typedef union {
	struct{
		uint8_t c0:1;
		uint8_t c1:1;
		uint8_t c2:1;
		uint8_t c3:1;
		uint8_t c4:1;
		uint8_t c5:1;
		uint8_t c6:1;
		uint8_t fill0:1;
	}par;
	uint8_t var;
} PIN_c; // 0x26
typedef union {
	struct{
		uint8_t c0:1;
		uint8_t c1:1;
		uint8_t c2:1;
		uint8_t c3:1;
		uint8_t c4:1;
		uint8_t c5:1;
		uint8_t c6:1;
		uint8_t fill0:1;
	}par;
	uint8_t var;
} DD_rc; // 0x27
typedef union {
	struct{
		uint8_t c0:1;
		uint8_t c1:1;
		uint8_t c2:1;
		uint8_t c3:1;
		uint8_t c4:1;
		uint8_t c5:1;
		uint8_t c6:1;
		uint8_t fill0:1;
	}par;
	uint8_t var;
} PORT_c; // 0x28
typedef union {
	struct{
		uint8_t d0:1;
		uint8_t d1:1;
		uint8_t d2:1;
		uint8_t d3:1;
		uint8_t d4:1;
		uint8_t d5:1;
		uint8_t d6:1;
		uint8_t d7:1;
	}par;
	uint8_t var;
} PIN_d; // 0x29
typedef union {
	struct{
		uint8_t d0:1;
		uint8_t d1:1;
		uint8_t d2:1;
		uint8_t d3:1;
		uint8_t d4:1;
		uint8_t d5:1;
		uint8_t d6:1;
		uint8_t d7:1;
	}par;
	uint8_t var;
} DD_rd; // 0x2A
typedef union {
	struct{
		uint8_t d0:1;
		uint8_t d1:1;
		uint8_t d2:1;
		uint8_t d3:1;
		uint8_t d4:1;
		uint8_t d5:1;
		uint8_t d6:1;
		uint8_t d7:1;
	}par;
	uint8_t var;
} PORT_d; // 0x2B
// Reserved 0x2C
// Reserved 0x2D
// Reserved 0x2E
// Reserved 0x2F
// Reserved 0x30
// Reserved 0x31
// Reserved 0x32
// Reserved 0x33
// Reserved 0x34
typedef union {
	struct{
		uint8_t tov0:1;
		uint8_t ocf0a:1;
		uint8_t ocf0b:1;
		uint8_t fill0:5;
	}par;
	uint8_t var;
} TC0_ifr; // 0x35
typedef union {
	struct{
		uint8_t tov1:1;
		uint8_t ocf1a:1;
		uint8_t ocf1b:1;
		uint8_t fill0:2;
		uint8_t icf1:1;
		uint8_t fill1:2;
	}par;
	uint8_t var;
} TC1_ifr; // 0x36
typedef union {
	struct{
		uint8_t tov2:1;
		uint8_t ocf2a:1;
		uint8_t ocf2b:1;
		uint8_t fill0:5;
	}par;
	uint8_t var;
} TC2_ifr; // 0x37
// Reserved 0x38
// Reserved 0x39
// Reserved 0x3A
typedef union {
	struct{
		uint8_t pcif0:1;
		uint8_t pcif1:1;
		uint8_t pcif2:1;
		uint8_t fill0:5;
	}par;
	uint8_t var;
} EXINT_pcifr; // 0x3B
typedef union {
	struct{
		uint8_t intf0:1;
		uint8_t intf1:1;
		uint8_t fill0:6;
	}par;
	uint8_t var;
} EXINT_ifr; // 0x3C
typedef union {
	struct{
		uint8_t int0:1;
		uint8_t int1:1;
		uint8_t fill0:6;
	}par;
	uint8_t var;
} EXINT_imsk; // 0x3D
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} MCU_gpior0; // 0x3E
typedef union {
	struct{
		uint8_t eere:1;
		uint8_t eepe:1;
		uint8_t eempe:1;
		uint8_t eerie:1;
		uint8_t eepm:2;
		uint8_t fill0:2;
	}par;
	uint8_t var;
} EEPROM_cr; // 0x3F
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} EEPROM_dr; // 0x40
typedef union {
	struct{
		uint8_t L;
		uint8_t H;
	}par;
	uint16_t var;
} EEPROM_ar; // 0x41 0x42
typedef union {
	struct{
		uint8_t psrsync:1;
		uint8_t psrasy:1;
		uint8_t fill0:5;
		uint8_t tsm:1;
	}par;
	uint8_t var;
} GTC_cr; // 0x43
typedef union {
	struct{
		uint8_t wgm0:1;
		uint8_t wgm1:1;
		uint8_t fill0:2;
		uint8_t comb:2;
		uint8_t coma:2;
	}par;
	uint8_t var;
} TC0_cra; // 0x44
typedef union {
	struct{
		uint8_t cs:3;
		uint8_t wgm2:1;
		uint8_t fill0:2;
		uint8_t focb:1;
		uint8_t foca:1;
	}par;
	uint8_t var;
} TC0_crb; // 0x45
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} TC0_nt; // 0x46
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} TC0_ocra; // 0x47
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} TC0_ocrb; // 0x48
// Reserved 0x49
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} MCU_gpior1; // 0x4A
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} MCU_gpior2; // 0x4B
typedef union {
	struct{
		uint8_t spr:2;
		uint8_t cpha:1;
		uint8_t cpol:1;
		uint8_t mstr:1;
		uint8_t dord:1;
		uint8_t spe:1;
		uint8_t spie:1;
	}par;
	uint8_t var;
} SPI_cr; // 0x4C
typedef union {
	struct{
		uint8_t spi2x:1;
		uint8_t fill0:5;
		uint8_t wcol:1;
		uint8_t spif:1;
	}par;
	uint8_t var;
} SPI_sr; // 0x4D
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} SPI_dr; // 0x4E
// Reserved 0x4F
typedef union {
	struct{
		uint8_t acis:2;
		uint8_t acic:1;
		uint8_t acie:1;
		uint8_t aci:1;
		uint8_t aco:1;
		uint8_t acbg:1;
		uint8_t acd:1;
	}par;
	uint8_t var;
} AC_sr; // 0x50
// Reserved 0x51
// Reserved 0x52
typedef union {
	struct{
		uint8_t se:1;
		uint8_t sm:3;
		uint8_t fill0:4;
	}par;
	uint8_t var;
} MCU_smcr; // 0x53
typedef union {
	struct{
		uint8_t porf:1;
		uint8_t extrf:1;
		uint8_t borf:1;
		uint8_t wdrf:1;
		uint8_t fill0:4;
	}par;
	uint8_t var;
} MCU_sr; // 0x54
typedef union {
	struct{
		uint8_t ivce:1;
		uint8_t ivsel:1;
		uint8_t fill0:2;
		uint8_t pud:1;
		uint8_t bodse:1;
		uint8_t bods:1;
		uint8_t fill1:1;
	}par;
	uint8_t var;
} MCU_cr; // 0x55
// Reserved 0x56
typedef union {
	struct{
		uint8_t spmen:1;
		uint8_t pgers:1;
		uint8_t pgwrt:1;
		uint8_t blbset:1;
		uint8_t rwwsre:1;
		uint8_t sigrd:1;
		uint8_t rwwsb:1;
		uint8_t spmie:1;
	}par;
	uint8_t var;
} MCU_spmcsr; // 0x57
// Reserved 0x58
// Reserved 0x59
// Reserved 0x5A
// Reserved 0x5B
// Reserved 0x5C
typedef union {
	struct{
		uint8_t L;
		uint8_t H;
	}par;
	uint16_t var;
} MCU_sp; // 0x5D 0x5E
typedef union {
	struct{
		uint8_t c:1;
		uint8_t z:1;
		uint8_t n:1;
		uint8_t v:1;
		uint8_t s:1;
		uint8_t h:1;
		uint8_t t:1;
		uint8_t i:1;
	}par;
	uint8_t var;
} MCU_sreg; // 0x5F
typedef union {
	struct{
		uint8_t wdp0:1;
		uint8_t wdp1:1;
		uint8_t wdp2:1;
		uint8_t wde:1;
		uint8_t wdce:1;
		uint8_t wdp3:1;
		uint8_t wdie:1;
		uint8_t wdif:1;
	}par;
	uint8_t var;
} WDT_csr; // 0x60
typedef union {
	struct{
		uint8_t clkps:4;
		uint8_t fill0:3;
		uint8_t clkpce:1;
	}par;
	uint8_t var;
} MCU_clkpr; // 0x61
// Reserved 0x62
// Reserved 0x63
typedef union {
	struct{
		uint8_t pradc:1;
		uint8_t prusart0:1;
		uint8_t prspi:1;
		uint8_t prtim1:1;
		uint8_t fill0:1;
		uint8_t prtim0:1;
		uint8_t prtim2:1;
		uint8_t prtwi:1;
	}par;
	uint8_t var;
} MCU_prr; // 0x64
// Reserved 0x65
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} MCU_osccal; // 0x66
// Reserved 0x67
typedef union {
	struct{
		uint8_t pcie:3;
		uint8_t fill0:5;
	}par;
	uint8_t var;
} EXINT_pcicr; // 0x68
typedef union {
	struct{
		uint8_t isc0:2;
		uint8_t isc1:2;
		uint8_t fill0:4;
	}par;
	uint8_t var;
} EXINT_icra; // 0x69
// Reserved 0x6A
typedef union {
	struct{
		uint8_t pcint0:1;
		uint8_t pcint1:1;
		uint8_t pcint2:1;
		uint8_t pcint3:1;
		uint8_t pcint4:1;
		uint8_t pcint5:1;
		uint8_t pcint6:1;
		uint8_t pcint7:1;
	}par;
	uint8_t var;
} EXINT_pcmsk0; // 0x6B
typedef union {
	struct{
		uint8_t pcint8:1;
		uint8_t pcint9:1;
		uint8_t pcint10:1;
		uint8_t pcint11:1;
		uint8_t pcint12:1;
		uint8_t pcint13:1;
		uint8_t pcint14:1;
		uint8_t fill0:1;
	}par;
	uint8_t var;
} EXINT_pcmsk1; // 0x6C
typedef union {
	struct{
		uint8_t pcint16:1;
		uint8_t pcint17:1;
		uint8_t pcint18:1;
		uint8_t pcint19:1;
		uint8_t pcint20:1;
		uint8_t pcint21:1;
		uint8_t pcint22:1;
		uint8_t pcint23:1;
	}par;
	uint8_t var;
} EXINT_pcmsk2; // 0x6D
typedef union {
	struct{
		uint8_t toie:1;
		uint8_t ociea:1;
		uint8_t ocieb:1;
		uint8_t fill0:5;
	}par;
	uint8_t var;
} TC0_imsk; // 0x6E
typedef union {
	struct{
		uint8_t toie:1;
		uint8_t ociea:1;
		uint8_t ocieb:1;
		uint8_t fill0:2;
		uint8_t icie:1;
		uint8_t fill1:2;
	}par;
	uint8_t var;
} TC1_imsk; // 0x6F
typedef union {
	struct{
		uint8_t toie:1;
		uint8_t ociea:1;
		uint8_t ocieb:1;
		uint8_t fill0:5;
	}par;
	uint8_t var;
} TC2_imsk; // 0x70
// Reserved 0x71
// Reserved 0x72
// Reserved 0x73
// Reserved 0x74
// Reserved 0x75
// Reserved 0x76
// Reserved 0x77
typedef union {
	struct{
		uint8_t L;
		uint8_t H;
	}par;
	uint16_t var;
} ADC_dr; // 0x78 0x79
typedef union {
	struct{
		uint8_t adps:3;
		uint8_t adie:1;
		uint8_t adif:1;
		uint8_t adate:1;
		uint8_t adsc:1;
		uint8_t aden:1;
	}par;
	uint8_t var;
} ADC_sra; // 0x7A
typedef union {
	struct{
		uint8_t adts:3;
		uint8_t fill0:3;
		uint8_t acme:1;
		uint8_t fill1:1;
	}par;
	uint8_t var;
} ADC_srb; // 0x7B
typedef union {
	struct{
		uint8_t mux:4;
		uint8_t fill0:1;
		uint8_t adlar:1;
		uint8_t refs:2;
	}par;
	uint8_t var;
} ADC_admux; // 0x7C
// Reserved 0x7D
typedef union {
	struct{
		uint8_t adc0d:1;
		uint8_t adc1d:1;
		uint8_t adc2d:1;
		uint8_t adc3d:1;
		uint8_t adc4d:1;
		uint8_t adc5d:1;
		uint8_t fill0:2;
	}par;
	uint8_t var;
} ADC_didr0; // 0x7E
typedef union {
	struct{
		uint8_t ain0d:1;
		uint8_t ain1d:1;
		uint8_t fill0:6;
	}par;
	uint8_t var;
} AC_didr1; // 0x7F
typedef union {
	struct{
		uint8_t wgm0:1;
		uint8_t wgm1:1;
		uint8_t fill0:2;
		uint8_t comb:2;
		uint8_t coma:2;
	}par;
	uint8_t var;
} TC1_cra; // 0x80
typedef union {
	struct{
		uint8_t cs:3;
		uint8_t wgm2:1;
		uint8_t wgm3:1;
		uint8_t fill0:1;
		uint8_t ices:1;
		uint8_t icnc:1;
	}par;
	uint8_t var;
} TC1_crb; // 0x81
typedef union {
	struct{
		uint8_t fill0:6;
		uint8_t focb:1;
		uint8_t foca:1;
	}par;
	uint8_t var;
} TC1_crc; // 0x82
// Reserved 0x83
typedef union {
	struct{
		uint8_t L;
		uint8_t H;
	}par;
	uint16_t var;
} TC1_nt; // 0x84 0x85
typedef union {
	struct{
		uint8_t L;
		uint8_t H;
	}par;
	uint16_t var;
} TC1_icr; // 0x86 0x87
typedef union {
	struct{
		uint8_t L;
		uint8_t H;
	}par;
	uint16_t var;
} TC1_ocra; // 0x88 0x89
typedef union {
	struct{
		uint8_t L;
		uint8_t H;
	}par;
	uint16_t var;
} TC1_ocrb; // 0x8A 0x8B
// Reserved 0x8C
// Reserved 0x8D
// Reserved 0x8E
// Reserved 0x8F
// Reserved 0x90
// Reserved 0x91
// Reserved 0x92
// Reserved 0x93
// Reserved 0x94
// Reserved 0x95
// Reserved 0x96
// Reserved 0x97
// Reserved 0x98
// Reserved 0x99
// Reserved 0x9A
// Reserved 0x9B
// Reserved 0x9C
// Reserved 0x9D
// Reserved 0x9E
// Reserved 0x9F
// Reserved 0xA0
// Reserved 0xA1
// Reserved 0xA2
// Reserved 0xA3
// Reserved 0xA4
// Reserved 0xA5
// Reserved 0xA6
// Reserved 0xA7
// Reserved 0xA8
// Reserved 0xA9
// Reserved 0xAA
// Reserved 0xAB
// Reserved 0xAC
// Reserved 0xAD
// Reserved 0xAE
// Reserved 0xAF
typedef union {
	struct{
		uint8_t wgm0:1;
		uint8_t wgm1:1;
		uint8_t fill0:2;
		uint8_t comb:2;
		uint8_t coma:2;
	}par;
	uint8_t var;
} TC2_cra; // 0xB0
typedef union {
	struct{
		uint8_t cs:3;
		uint8_t wgm2:1;
		uint8_t fill0:2;
		uint8_t focb:1;
		uint8_t foca:1;
	}par;
	uint8_t var;
} TC2_crb; // 0xB1
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} TC2_nt; // 0xB2
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} TC2_ocra; // 0xB3
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} TC2_ocrb; // 0xB4
// Reserved 0xB5
typedef union {
	struct{
		uint8_t tcr2bub:1;
		uint8_t tcr2aub:1;
		uint8_t ocr2bub:1;
		uint8_t ocr2aub:1;
		uint8_t tcn2ub:1;
		uint8_t as2:1;
		uint8_t exclk:1;
		uint8_t fill0:1;
	}par;
	uint8_t var;
} TC2_assr; // 0xB6
// Reserved 0xB7
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} TWI_br; // 0xB8
typedef union {
	struct{
		uint8_t twps:2;
		uint8_t fill0:1;
		uint8_t tws:5;
	}par;
	uint8_t var;
} TWI_sr; // 0xB9
typedef union {
	struct{
		uint8_t twgce:1;
		uint8_t twa:7;
	}par;
	uint8_t var;
} TWI_ar; // 0xBA
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} TWI_dr; // 0xBB
typedef union {
	struct{
		uint8_t twie:1;
		uint8_t fill0:1;
		uint8_t twen:1;
		uint8_t twwc:1;
		uint8_t twsto:1;
		uint8_t twsta:1;
		uint8_t twea:1;
		uint8_t twint:1;
	}par;
	uint8_t var;
} TWI_cr; // 0xBC
typedef union {
	struct{
		uint8_t fill0:1;
		uint8_t twam:7;
	}par;
	uint8_t var;
} TWI_amr; // 0xBD
// Reserved 0xBE
// Reserved 0xBF
typedef union {
	struct{
		uint8_t mpcm:1;
		uint8_t u2x:1;
		uint8_t upe:1;
		uint8_t dor:1;
		uint8_t fe:1;
		uint8_t udre:1;
		uint8_t txc:1;
		uint8_t rxc:1;
	}par;
	uint8_t var;
} USART0_csra; // 0xC0
typedef union {
	struct{
		uint8_t txb8:1;
		uint8_t rxb8:1;
		uint8_t ucsz2:1;
		uint8_t txen:1;
		uint8_t rxen:1;
		uint8_t udrie:1;
		uint8_t txcie:1;
		uint8_t rxcie:1;
	}par;
	uint8_t var;
} USART0_csrb; // 0xC1
typedef union {
	struct{
		uint8_t ucpol:1;
		uint8_t ucsz0:1;
		uint8_t ucsz1:1;
		uint8_t usbs:1;
		uint8_t upm:2;
		uint8_t umsel:2;
	}par;
	uint8_t var;
} USART0_csrc; // 0xC2
// Reserved 0xC3
typedef union {
	struct{
		uint8_t L;
		uint8_t H;
	}par;
	uint16_t var;
} USART0_brr; // 0xC4 0xC5
typedef union {
	struct{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	}par;
	uint8_t var;
} USART0_dr; // 0xC6
// Reserved 0xC7
// Reserved 0xC8
// Reserved 0xC9
// Reserved 0xCA
// Reserved 0xCB
// Reserved 0xCC
// Reserved 0xCD
// Reserved 0xCE
// Reserved 0xCF
// Reserved 0xD0
// Reserved 0xD1
// Reserved 0xD2
// Reserved 0xD3
// Reserved 0xD4
// Reserved 0xD5
// Reserved 0xD6
// Reserved 0xD7
// Reserved 0xD8
// Reserved 0xD9
// Reserved 0xDA
// Reserved 0xDB
// Reserved 0xDC
// Reserved 0xDD
// Reserved 0xDE
// Reserved 0xDF
// Reserved 0xE0
// Reserved 0xE1
// Reserved 0xE2
// Reserved 0xE3
// Reserved 0xE4
// Reserved 0xE5
// Reserved 0xE6
// Reserved 0xE7
// Reserved 0xE8
// Reserved 0xE9
// Reserved 0xEA
// Reserved 0xEB
// Reserved 0xEC
// Reserved 0xED
// Reserved 0xEE
// Reserved 0xEF
// Reserved 0xF0
// Reserved 0xF1
// Reserved 0xF2
// Reserved 0xF3
// Reserved 0xF4
// Reserved 0xF5
// Reserved 0xF6
// Reserved 0xF7
// Reserved 0xF8
// Reserved 0xF9
// Reserved 0xFA
// Reserved 0xFB
// Reserved 0xFC
// Reserved 0xFD
// Reserved 0xFE
// Reserved 0xFF

#endif
/*** EOF ***/

