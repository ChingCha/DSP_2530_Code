//-------------------------------------------------------------------
// Filename: M250.c
// Description: M250 library RFIDÅª¥d¼Ò²Õ(DI)
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "M250.h"

uint8 rfBuf[20];
uint8 rfLowBit, rfHighByte;
uint8 rfTagUID[5];

//-------------------------------------------------------------------
void rfShiftData(uint8 value)
{
    uint8 i;
    uint8 j, k;

    j = rfBuf[0] &0x01;
    rfBuf[0] = rfBuf[0] >> 1;
    for (i = 1; i < (value / 8); i++)
    {
        k = rfBuf[i] &0x01;
        rfBuf[i] = rfBuf[i] >> 1;
        if (k)
        {
            rfBuf[i - 1] |= 0x80;
        }
        else
        {
            rfBuf[i - 1] &= 0x7f;
        }
    }
    if (j)
    {
        rfBuf[(value / 8) - 1] |= 0x80;
    }
    else
    {
        rfBuf[(value / 8) - 1] &= 0x7f;
    }
}

//-------------------------------------------------------------------
uint8 rfGetBit(uint8 source, uint8 i)
{
    uint8 uch; //  Get bit 0-7 

    uch = 1 << i;
    uch &= source;
    if (uch)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//-------------------------------------------------------------------
void rfGetPosition(uint8 i)
{
    rfHighByte = (uint8)(i / 8);
    rfLowBit = (uint8)(i % 8);
}

//-------------------------------------------------------------------
uint8 rfSameBit(void)
{
    uint8 i;

    for (i = 0; i < 128; i += 2)
    // 0 2 4 6 8 --- 126/192/254
    {
        rfGetPosition(i);
        if (rfGetBit(rfBuf[rfHighByte], rfLowBit) == rfGetBit(rfBuf[rfHighByte], rfLowBit + 1))
        {
            return 0;
        }
        // has same bit 11  00
    }
    return 1;
}

//-------------------------------------------------------------------
void rfSetBit(uint8 i, uint8 k)
{
    uint8 hi, low, ch;

    hi = (uint8)(i / 16);
    low = (uint8)((i % 16) / 2);
    ch = 1 << low;
    if (k == 1)
    {
        rfBuf[hi] |= ch;
    }
    else
    {
        rfBuf[hi] &= (~ch);
    }
}

//-------------------------------------------------------------------
uint8 rfGetHeader(void)
{
    uint8 i, j, flag;

    for (i = 0; i < 65; i++)
    {
        // find 9 bits header 0111111111
        flag = 0;
        if (rfGetBit(rfBuf[0], 0) != 0)
        // 0
        {
            flag = 1;
        }
        for (j = 1; j < 8; j++)
        {
            if (rfGetBit(rfBuf[0], j) != 1)
            // 1 2 3 4 5 6 7
            {
                flag = 1;
            }
        }
        if (rfGetBit(rfBuf[1], 0) != 1 || rfGetBit(rfBuf[1], 1) != 1)
        {
            flag = 1;
        }
        if (flag == 0)
        {
            // shift 10 bit
            for (i = 0; i < 10; i++)
            {
                rfShiftData(128 / 2);
            }
            return 1;
        }
        rfShiftData(128 / 2);
    }
    return 0;
}

//-------------------------------------------------------------------
uint8 rfTransTureData(void)
{
    uint8 i, j, n, Rparity, Cparity;

    for (i = 0; i < 5; i++)
    {
        rfTagUID[i] = 0;
    }
    j = 0x00;
    Rparity = 0;
    Cparity = 0;
    for (i = 0; i < 54; i++)
    {
        n = i % 5;
        if (0x01 &(rfBuf[i / 8] >> (i % 8)))
        {
            Cparity ^= 0x01 << n; // PC0 - PC3  n=0-3  4 not use
            if (i < 50)
            {
                Rparity ^= 0x01;
            }
            if (i < 49)
            {
                if (n != 4)
                {
                    rfTagUID[4-(j / 8)] |= (0x80 >> (j % 8));
                }
            }
        }
        if (n == 4)
        {
            if (Rparity)
            {
                return 0;
            }
        }
        else
        {
            j++;
        }
    }
    if (Cparity &0x0f)
    {
        return 0;
    }
    return 1;
}

//-------------------------------------------------------------------
uint8 rfCompareData(void)
{
    uint8 p;

    if (rfSameBit() == 0)
    // has same bit
    {
        rfShiftData(128);
        if (rfSameBit() == 0)
        {
            return 0;
        }
    }
    //  trans 1-0 to 1  0-1 to 0   i=0 2 4 6 ..... 126
    for (p = 0; p < 128; p += 2)
    {
        rfGetPosition(p);
        if (rfGetBit(rfBuf[rfHighByte], rfLowBit) == 0 && rfGetBit(rfBuf[rfHighByte], rfLowBit + 1) == 1)
        {
            rfSetBit(p, 0);
        }
        else
        {
            rfSetBit(p, 1);
        }
    }

    if (rfGetHeader() == 0)
    {
        return 0;
    }

    if (rfTransTureData() == 0)
    {
        return 0;
    }
    return 1;
}

//-------------------------------------------------------------------
uint8 rfCheckTag(void)
{
    uint8 err;
    uint8 n,ch;
    uint8 posi;

    posi = 0;
    err = 0;
    while (1)
    {
		n=0;
        while (n++ < 100 && HAL_RF_DAT() != 0)
        {
            halMcuWaitUs(6);
        }
        rfHighByte = posi / 8;
        rfLowBit = posi % 8;
        ch = 1 << rfLowBit;
        rfBuf[rfHighByte] |= ch;
        if ((n > 15) && (n <= 35))
        {
            posi++;
        }
        else if ((n > 35) && (n < 70))
        //
        {
            posi++;
            if (posi < 128)
            {
                rfHighByte = posi / 8;
                rfLowBit = posi % 8;
                ch = 1 << rfLowBit;
                rfBuf[rfHighByte] |= ch;
                posi++;
            }
        }
        else
        {
            err++;
            posi = 0;
            if (err > 10)
            {
                break;
            }
        }

        if (posi >= 128)
        {
            return 1;
        }
      	n=0;
        while (n++< 100 && HAL_RF_DAT() == 0)
      	{
        	halMcuWaitUs(6);
      	}

        rfHighByte = posi / 8;
        rfLowBit = posi % 8;
        ch = 1 << rfLowBit;
        rfBuf[rfHighByte] &= (~ch);

        if ((n > 15) && (n <= 35))
        {
            posi++;
        }
        else if ((n > 35) && (n < 70))
        //
        {
            posi++;
            if (posi < 128)
            {
                rfHighByte = posi / 8;
                rfLowBit = posi % 8;
                ch = 1 << rfLowBit;
                rfBuf[rfHighByte] &= (~ch);
                posi++;
            }
        }
        else
        {
            err++;
            posi = 0;
            if (err > 10)
            {
                break;
            }
        }
        if (posi >= 128)
        {
            return 1;
        }
    }
    return 0;
}

//-------------------------------------------------------------------
// @fn      M250_Init
// @brief   Set up port M250 
// @return  none
//-------------------------------------------------------------------
void M250_Init(void)
{
    HAL_RF_CLK_DIR_IN();
    HAL_RF_DAT_DIR_IN();
    HAL_RF_MOD_DIR_OUT();
  
    HAL_RF_MOD_CLR();
}

//-------------------------------------------------------------------
// @fn      M250_ReadTag
// @brief   Enable int move interrupt
// @param   none
// @return  none
//-------------------------------------------------------------------
uint8 M250_ReadTag(void)
{
    if(rfCheckTag()==1)
	    if(rfCompareData()==1)
			return 1;
    return 0;
}
