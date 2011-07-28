/*************************************************
 * Project: FadeCube 10x10x10 led-cube control
 *          application, written by Gergo Huszty
 *
 * Published on: https://github.com/libesz
 *          and  http://libesz.digitaltrip.hu
 * 
 * Used ENC28J60 driver and UDP/IP stack got from
 * www.tuxgraphics.com
 * (TCP stack is disabled)
 *
 * Chip type           : Atmega32 with ENC28J60
 *************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <compat/deprecated.h>
#include "ip_arp_udp_tcp.h"
#include "enc28j60.h"
#include "timeout.h"
#include "net.h"
#include "avr_init.h"

#define nop() asm volatile ("nop") 

static uint8_t mymac[6] = {0x54,0x55,0x58,0x10,0x00,0x29};
// how did I get the mac addr? Translate the first 3 numbers into ascii is: TUX
static uint8_t myip[4] = {192,168,1,99};

// listen port for udp
#define MYUDPPORT 1125 //because it is my birthday :)
#define BUFFER_SIZE 550
static uint8_t buf[BUFFER_SIZE+1];

volatile unsigned char cube[250];
volatile unsigned char actual_layer = 0;
volatile unsigned char led_value = 0, four_led_value = 0, led_data_mask = 0;

#define LAYERS 10

static inline void do_clk( unsigned char amount )
{
   for( ; amount; amount--)
   {
      COL_CLK = 1;
      COL_CLK = 0;
   }
}

//See TLC5947 manual to understand the communication
ISR( TIMER0_COMP_vect )
{
   unsigned char actual_column = 0;
   if( ++actual_layer == LAYERS )
   {
      actual_layer = 0;
   }
   for( actual_column = 0; actual_column < 100; actual_column++ )
   {
      if( !led_data_mask )
      {
         led_data_mask = 128;
         four_led_value = cube[ ( actual_layer * 25 ) + ( actual_column / 4 ) ]; 
      }
      led_value = 0;
      if( four_led_value & led_data_mask )
      {
         led_value |= 2;
      }
      led_data_mask >>= 1;
      if( four_led_value & led_data_mask )
      {
         led_value |= 1;
      }
      led_data_mask >>= 1;
      
      //This method cunsumed the less time to run, though it is a bit ugly
      switch( led_value )
      {
         case 0:
            COL_DATA = 0;
            do_clk( 12 );
            break;
         case 1:
            COL_DATA = 0;
            do_clk( 2 );
            
            COL_DATA = 1;
            do_clk( 1 );
            
            COL_DATA = 0;
            do_clk( 1 );
            
            COL_DATA = 1;
            do_clk( 1 );

            COL_DATA = 0;
            do_clk( 1 );
            
            COL_DATA = 1;
            do_clk( 4 );

            COL_DATA = 0;
            do_clk( 2 );
            break;
         case 2:
            COL_DATA = 0;
            do_clk( 1 );
            
            COL_DATA = 1;
            do_clk( 1 );
            
            COL_DATA = 0;
            do_clk( 1 );
            
            COL_DATA = 1;
            do_clk( 3 );

            COL_DATA = 0;
            do_clk( 1 );
            
            COL_DATA = 1;
            do_clk( 1 );

            COL_DATA = 0;
            do_clk( 4 );
            break;
         case 3:
            COL_DATA = 1;
            do_clk( 12 );
            break;
      }
   }
   nop();
   nop(); 
   COL_BLANK = 1;
   COL_XLAT = 1;
   nop();
   nop(); 
   COL_XLAT = 0;
   if( !actual_layer )
   {
      ROW_RESET = 1;
      ROW_RESET = 0;
   }
   else
   {
      ROW_CLK = 1;
      ROW_CLK = 0;
   }
   COL_BLANK = 0;
}

int main(void)
{
#include "avr_init.c"
   uint16_t plen;
   uint16_t dat_p;
   uint8_t payloadlen=0;

   uint8_t source_ip[4] = {0,0,0,0};

   /*initialize enc28j60*/
   enc28j60Init(mymac);
   enc28j60clkout(2); // change clkout from 6.25MHz to 12.5MHz
   _delay_loop_1(0); // 60us

   /* Magjack leds configuration, see enc28j60 datasheet, page 11 */
   // LEDB=yellow LEDA=green
   //
   // 0x476 is PHLCON LEDA=links status, LEDB=receive/transmit
   // enc28j60PhyWrite(PHLCON,0b0000 0100 0111 01 10);
   enc28j60PhyWrite(PHLCON,0x476);

   //init the web server ethernet/ip layer:
   init_ip_arp_udp_tcp(mymac,myip,80);

   while(1)
   {
      //wdt_reset();
      // handle ping and wait for a udp packet
      cli();
      plen=enc28j60PacketReceive(BUFFER_SIZE, buf);
      buf[BUFFER_SIZE]='\0';
      dat_p=packetloop_icmp_tcp(buf,plen);
      sei();
      // udp start, we listen on udp port 1125
      // check if ip packets are for us:
      if( eth_type_is_ip_and_my_ip(buf,plen) == 0 )
      {
         continue;
      }
      if( buf[IP_PROTO_P] == IP_PROTO_UDP_V && buf[UDP_DST_PORT_H_P] == (MYUDPPORT>>8) && buf[UDP_DST_PORT_L_P] == (MYUDPPORT&0xff) )
      {
         //IP address is saved after first packet on MYUDPPORT, any other IP will be forbidden after this
         if( ( buf[ IP_SRC_P   ] != source_ip[0] ) ||
             ( buf[ IP_SRC_P +1] != source_ip[1] ) ||
             ( buf[ IP_SRC_P +2] != source_ip[2] ) ||
             ( buf[ IP_SRC_P +3] != source_ip[3] ) )
         {
            if( !source_ip[0] )
            {
               source_ip[0] = buf[ IP_SRC_P   ];
               source_ip[1] = buf[ IP_SRC_P +1];
               source_ip[2] = buf[ IP_SRC_P +2];
               source_ip[3] = buf[ IP_SRC_P +3];
            }
            else
            {
               continue;
            }
         }

         if( !buf[ UDP_DATA_P ] ) //first byte is 0 --> hello
         {
               char *hello_reply = "FadeCube v1.0";
               make_udp_reply_from_request(buf,hello_reply,strlen(hello_reply),MYUDPPORT); 
         }
         else if( 1 == buf[ UDP_DATA_P ] ) //first byte is 1 --> cube data recieved
         {
            unsigned int data_index = 1;
            payloadlen = buf[UDP_LEN_L_P]-UDP_HEADER_LEN;
         
            for( ; data_index < payloadlen; data_index++ )
            {
               cube[data_index - 1] = buf[ UDP_DATA_P + data_index ];
            }
         }

      }
   }
   return (0);
}
