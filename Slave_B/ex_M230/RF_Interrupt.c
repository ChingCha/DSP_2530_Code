#pragma vector=RF_VECTOR  
__interrupt void rf_isr(void)  
{  
  EA =0;  
   
  // 接收到一个完整的数据包  
  if(RFIRQF0&(1<<6))  
  {  
   rf_receive_isr();                          //调用接收中断处理函数  
   S1CON =0;                                   //清除RF中断标志  
   RFIRQF0 &=~(1<<6);                        //清除RF接收完成数据包中断  
  }  
  EA =1;  
}

  
void rf_receive_isr()  
{  
  int rf_rx_len=0;  
  int rssi=0;  
  char crc_ok=0;  
   
 rf_rx_len = RFD-2;                       //长度去除两字节附加结果  
 rf_rx_len &=0x7F;  
  for(int i=0; i< rf_rx_len; i++)  
  {  
   rf_rx_buf[i]= RFD;                      //连续读取接收缓冲区内容  
  }  
   
  rssi = RFD-73;                           //读取RSSI结果  
 crc_ok = RFD;                              //读取CRC校验结果 BIT7  
   
  RFST =0xED;                               //清除接收缓冲区  
  if( crc_ok&0x80)  
  {  
   uart0_sendbuf( rf_rx_buf, rf_rx_len);   //串口发送   
   printf("[%d]",rssi);  
  }  
  else  
  {  
   printf("\r\nCRC Error\r\n");  
  }  
}   