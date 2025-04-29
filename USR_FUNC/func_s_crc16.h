#ifndef __FUNC_S_CRC16_H_
#define __FUNC_S_CRC16_H_


// ---------------- POPULAR POLYNOMIALS ----------------

#define  CRC_16_POLYNOMIALS_0x8005   1      // CRC-16: x^16 + x^15 + x^2 + x^0  (0x8005)
#define  CRC_16_POLYNOMIALS_0x1021   1      // CCITT:  x^16 + x^12 + x^5 + x^0  (0x1021)



/******************CRC16–£—È÷µ*******************************/
#ifdef	CRC_16_POLYNOMIALS_0x8005
extern unsigned int FUNC_S_CRC16_MODBUS_CAL(unsigned char* pchMsg, unsigned int wDataLen);

extern unsigned int FUNC_S_CRC16_MODBUS_CHECK(unsigned char* pchMsg, unsigned int wDataLen);
#endif

#ifdef	CRC_16_POLYNOMIALS_0x1021
extern unsigned int FUNC_S_CRC16_XMODEM_CAL(unsigned char* pchMsg, unsigned int wDataLen);

extern unsigned int FUNC_S_CRC16_XMODEM_CHECK(unsigned char* pchMsg, unsigned int wDataLen);
#endif


#endif

