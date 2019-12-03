#include "me_init.h"
#include <string.h>


/********************************************************************
 *             Global variables and function declarations           *
 ********************************************************************/

short speed = 0;
int incdec = 0;
int abc = 0;


void carspeed(void);

/********************************************************************
 *                         Application entry point                  *
 ********************************************************************/

void carspeed()
{

  if(speed >= 0 && incdec == 0)
  {
	  speed += 5;
	  if(speed == 300)
	  {
		  speed = 300;
		  incdec = 1;
	  }
  }
  else if(incdec == 1)
  {
	  speed -= 5;
	  if(speed == 0)
	  {
	  	  speed = 0;
	  	  incdec = 0;
	  }
  }
}


int main(void) {

  /* Board and modules initialization */
  ME_Init();
  PIT_ConfigureTimer(1,200);
  //PIT_StartTimer(1);



  /* Application main loop that runs forever*/
for ( ; ; ) {
/********************************************************************
 *                           Main Loop                              *
 *                    _____  ___  ___   ___                         *
 *                   |_   _|/ _ \|   \ / _ \                        *
 *                     | | | (_) | |) | (_) |                       *
 *                     |_|  \___/|___/ \___/                        *
 *                                                                  *
 *                  Write down your logic here.                     *
 ********************************************************************/

   /* Operating System Delay*/
   osalThreadDelayMilliseconds(250UL);
 }
}



/********************************************************************
 *                   Can Reception Function                         *
 ********************************************************************/
void can_receive() {
   if(CAN_0.IFRL.B.BUF5I == 1)
   {
	   switch(CAN_0.BUF[0].ID.B.STD_ID)
	   {
	   	   case 0xFF:
	   	   {
	   		   U1 = ~U1;
	   		   break;
	   	   }
	   	   case 0x01:
	   	   {
	   		   U2 = 0;
	   		   PIT_StartTimer(1);
	   		   break;
	   	   }
	   	   case 0x02:
	   	   {
	   		   U3 = CAN_0.BUF[0].DATA.B[X];
	   		   break;
	   	   }


	   }
   }
}



/********************************************************************
 *                      Interrupt Functions                         *
 *                    _____  ___  ___   ___                         *
 *                   |_   _|/ _ \|   \ / _ \                        *
 *                     | | | (_) | |) | (_) |                       *
 *                     |_|  \___/|___/ \___/                        *
 *                                                                  *
 *                Interrupts can be handled below.                  *
 ********************************************************************
 *                   Interrupt Handlers for PIT                     *
 ********************************************************************/
void Toggle(void)
{
  U1 = ~U1;
  char speedvalue[2];
  memcpy(speedvalue,(char*)&speed,2);
  CAN_0.BUF[8].DATA.B[0] = speedvalue[1];
  CAN_0.BUF[8].DATA.B[1] = speedvalue[0];

  CAN_0.BUF[8].CS.B.CODE = 12;
  carspeed();
  PIT.CHANNEL[1].TFLG.B.TIF=1;
}

/********************************************************************
*                   Interrupt Handlers for CAN Message Buffer       *
********************************************************************/
IRQ_HANDLER(SPC5_FLEXCAN0_BUF_08_11_HANDLER) {
	CAN_0.IFRL.B.BUF8I = 1;

}






