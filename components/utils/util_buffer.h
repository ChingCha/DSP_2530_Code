//-------------------------------------------------------------------
// Filename: util_buffer.h
// Description: Ringbuffer interface
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// CONSTANTS AND DEFINES
//-------------------------------------------------------------------
#define BUF_SIZE    64

//-------------------------------------------------------------------
// TYPEDEFS
//-------------------------------------------------------------------
typedef struct
{
    volatile uint8 pData[BUF_SIZE];
    volatile uint8 nBytes;
    volatile uint8 iHead;
    volatile uint8 iTail;
} ringBuf_t;

//-------------------------------------------------------------------
// MACROS
//-------------------------------------------------------------------
#define bufFlush(pBuf)  bufInit(pBuf)

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void bufInit(ringBuf_t *pBuf);
uint8 bufPut(ringBuf_t *pBuf, const uint8 *pData, uint8 n);
uint8 bufGet(ringBuf_t *pBuf, uint8 *pData, uint8 n);
uint8 bufPeek(ringBuf_t *pBuf, uint8 *pData, uint8 nBytes);
uint8 bufNumBytes(ringBuf_t *pBuf);
