//=====================================================================================
//
//	Author					: Cytron Technologies		
//	Project					: Interface Free Controller
//	Project description			: Header file for IFC-XB01
//  Date					: JAN 2010
//
//=====================================================================================
#include<p18f2685.h>



//define
//=====================================================================================
#define error_led	LATCbits.LATC2
//#define	led1		LATBbits.LATB0




//function prototype
//=====================================================================================
void xb_MY(unsigned char add,unsigned short MY);
void xb_DL(unsigned char add,unsigned long DL);
void xb_DH(unsigned char add,unsigned long DH);
void xb_CH(unsigned char add, unsigned char CH);
void xb_ID(unsigned char add,unsigned short ID);
void xb_send(unsigned char add, unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3, unsigned char data4, unsigned char data5,unsigned char data6, unsigned char data7);
unsigned short xb_readMY(unsigned char add);
unsigned long xb_readDL(unsigned char add);
unsigned long xb_readDH(unsigned char add);
unsigned char xb_readCH(unsigned char add);
unsigned short xb_readID(unsigned char add);
unsigned long xb_readSH(unsigned char add);
unsigned long xb_readSL(unsigned char add);
void xb_receive(unsigned char add);
unsigned char xb_RSSI(unsigned char add);



// =================================================================================
// Library Functions
// This Library Functions will explain on the function prototype of IFC-XB01
// Please make sure the address on IFC-XB01 is compatible with program.
// =================================================================================

// void xb_MY(unsigned char add,unsigned short MY)
// ---------------------------------------------------------------------------------
// To set the 16-bit source address of the XBEE module.
// The address is in hexadecimal format and the range is 0 - 0xFFFF.
// Example:
//			xb_MY(add_xb, 12AB); 	 //set the source address to 0x12AB 
//
// ---------------------------------------------------------------------------------

// void xb_DL(unsigned char add,unsigned long DL)
// ---------------------------------------------------------------------------------
// To set the lower 32 bits of the 64-bit destination address of the XBEE module. 
// The address is in hexadecimal format. 
// For the transmission using 16-bit address, set DH parameter to zero and DL less than 0xFFFF.
// 0x000000000000FFFF is the broadcast address for the PAN.
// Example:
//			xb_DL(add_xb, 0000FFFF);    //set the destination address  low to 0xFFFF(broadcast address for the PAN) to broadcast 
//										//to all the IFC-XB01 cards which are having same channel(CH) and same PAN ID.
//
//			xb_DL(add_xb, 000012AB);    //set the destination address to match the source address (MY) for communication with
//										//that particular MY address matching IFC-XB01 card
//
// --------------------------------------------------------------------------------

// void xb_DH(unsigned char add,unsigned long DH)
// ---------------------------------------------------------------------------------
// To set the higher 32-bits of 64 bits destination address of the XBEE module. 
// Set DH to 0 for 16-bits addressing communication.(default value of DH is zero, this function is reserved) 
// Example:
//			xb_DH(add_xb, 00000000);    	//set DH to 0 for 16 bits addressing 
//
// ---------------------------------------------------------------------------------

// void xb_CH(unsigned char add, unsigned char CH)
// ---------------------------------------------------------------------------------
// To set the channel number used for transmitting and receiving data between IFC-XB01 cards.
// (Default value of CH is 0x0C). Users are advised to set CH to be different to avoid interference from other 
// XBEE systems that might operate in the same channel. Allowed channels are 0x0B - 0x1A (XBee) and 0x0C - 0x17 (XBee-PRO)
// Example:
//			xb_CH(add_xb, 1A);    	//set channel to 0x1A  
//
// ---------------------------------------------------------------------------------

// void xb_ID(unsigned char add,unsigned short ID)
// ---------------------------------------------------------------------------------
// To set the PAN (Personal Area Network) ID. Use 0xFFFF to broadcast messages to all PANs.
// Example:
//			xb_ID(add_xb, 1234);	//set the PAN ID to 1234
//
// ---------------------------------------------------------------------------------

// void xb_send(unsigned char add, unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3, unsigned char data4, unsigned char data5,unsigned char data6, unsigned char data7)
// ---------------------------------------------------------------------------------
// To send wireless data out of XBEE module. 
// 8 bytes of data can be sent out in a packet.
// API mode 2 is used in IFC-XB01 for send function.
// Example:
//			xb_send(add_xb, 7E,7D,11,13,AB,12,34,56)	 //sending 8 bytes of data
//
// ---------------------------------------------------------------------------------

// unsigned short xb_readMY(unsigned char add)
// ---------------------------------------------------------------------------------
// To read the 16-bit source address of the XBEE module.
// Example:
//			myadd=xb_readMY(add_xb);	//read source address of the XBEE module and save to variable myadd. 
// 
// ---------------------------------------------------------------------------------

// unsigned long xb_readDL(unsigned char add)
// ---------------------------------------------------------------------------------
// To read the lower 32 bits of the 64-bit destination address of the XBEE module.
// Example:
//			dest_L=xb_readDL(add_xb);	//read destination address low of the XBEE module and save to variable dest_L.
//
// --------------------------------------------------------------------------------- 

// unsigned long xb_readDH(unsigned char add)
// ---------------------------------------------------------------------------------
// To read the higher 32-bits of 64 bits destination address of the XBEE module.
// Example: 
//			dest_h=xb_readDH(add_xb) ;		// read destination address high of the XBEE module and save to variable dest_h
//
// ---------------------------------------------------------------------------------

// unsigned char xb_readCH(unsigned char add)
// ---------------------------------------------------------------------------------
// To read the channel number used for transmitting and receiving data of the IFC-XB01 card.
// Example:
//			Channel=xb_readCH(add_xb);		// read  CH of the XBEE module and save to variable Channel
//
// ---------------------------------------------------------------------------------

// unsigned short xb_readID(unsigned char add)
// ---------------------------------------------------------------------------------
// To read the PAN (Personal Area Network) ID of the XBEE module.
// Example:
//			PANID=xb_readID(add_xb);	//read the PAN ID of the XBEE module and save to variable PANID
//
// ---------------------------------------------------------------------------------		

// unsigned long xb_readSH(unsigned char add)
// ---------------------------------------------------------------------------------
// To read 32 bits Serial Number High of the XBEE module’s unique IEEE 64-bit address. 
// 64-bit source address is always enabled. 
// Example:
//			s_high=xb_readSH(add_xb);	//read serial number high and save to variable s_high
//
// ---------------------------------------------------------------------------------

// unsigned long xb_readSL(unsigned char add)
// ---------------------------------------------------------------------------------
// To read 32 bits Serial Number Low of the XBEE module's unique IEEE 64-bit address. 
// 64-bit source address is always enabled. 
// Example:
//			s_low=xb_readSL(add_xb);		//read serial number low and save to variable s_low
// 
// ---------------------------------------------------------------------------------

// void xb_receive(unsigned char add)
// ---------------------------------------------------------------------------------
// To read received data from the XBEE module.  
// User need to poll IFC_XB01 from using this function to keep update and to enable IFC_XB01 read received wireless data. 
// The received data are saved to predefined array, rec_data[8], user will need to read this array to retrieve the received data. 
// Example:
//			xb_receive(add_xb);		//read 8 bytes received data
//
// ---------------------------------------------------------------------------------

// unsigned char xb_RSSI(unsigned char add)
// ---------------------------------------------------------------------------------
// To read RSSI(RSSI is Received Signal Strength Indicator) of the received data packet. 
// The one byte RSSI value is hexadecimal equivalent of (-dBm) value. 
// (For example: If RX signal strength = -40 dBm, “0x28” (40 decimal) is returned). 
// Example:
//				rssi=xb_RSSI(add_xb);	//read RSSI of the receive data packet and save to variable rssi
//
// ----------------------------------------------------------------------------------


