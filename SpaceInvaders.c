// Red SparkFun Nokia 5110 (LCD-10168)
// -----------------------------------
// Signal        (Nokia 5110) LaunchPad pin
// 3.3V          (VCC, pin 1) power
// Ground        (GND, pin 2) ground
// SSI0Fss       (SCE, pin 3) connected to PA3
// Reset         (RST, pin 4) connected to PA7
// Data/Command  (D/C, pin 5) connected to PA6
// SSI0Tx        (DN,  pin 6) connected to PA5
// SSI0Clk       (SCLK, pin 7) connected to PA2
// back light    (LED, pin 8) not connected, consists of 4 white LEDs which draw ~80mA total

#include "..//tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "Random.h"
#include "TExaS.h"
#include "button.h"
#include "led.h"
#include "uart.h"

// 2. Declarations Section
//   function prototype
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Timer2_Init(unsigned long period);
void Delay100ms(unsigned long count); // time delay in 0.1 seconds
void DX_Ball();  //update x-y corrdinate and display at nokia

//   Global Variables
unsigned long TimerCount;
unsigned long Semaphore;

unsigned char flag=0;
unsigned long eypos = 9;
int k = 1; 
int i, j , x = 4, bunkerXPOS = 34, ballXPOS = 41, ballYPOS = 47 - 5, ballxf = 0, ballyf = -1, u_d = 1, l_r = 3, cnt = 0;

const int nwall = 20, nrow = 4;

unsigned char xpositions[nwall], ypositions[nrow];

int exist[nrow][nwall], nexist = nrow * nwall , success = 0;

// *************************** Images ***************************
const unsigned char Bunker0[] ={
 0x42, 0x4D, 0xB2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00,
 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0xFF,

};

const unsigned char block[] ={
 0x42, 0x4D, 0xB6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

};
const unsigned char wall[] ={
 0x42, 0x4D, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xAA, 0x00, 0x00, 0x00, 0xAA, 0x00, 0x00, 0x00, 0xFF,

};
const unsigned char ball[] ={
 0x42, 0x4D, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0xAA, 0xAA,
 0x00, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0xFF,

};
	
// *************************** Capture image dimensions out of BMP**********
#define WALLW       ((unsigned char)wall[18])
#define WALLH       ((unsigned char)wall[22])
	
#define BALLW       ((unsigned char)ball[18])
#define BALLH       ((unsigned char)ball[22])
	
#define BUNKERW     ((unsigned char)Bunker0[18])
#define BUNKERH     ((unsigned char)Bunker0[22])

int main(void){
  TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
  Random_Init(1);
  Nokia5110_Init();
  Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();      // draw buffer
	UART_Init();
  Nokia5110_Clear();
  Nokia5110_SetCursor(1, 1);
  Nokia5110_OutString("plz press");
  Nokia5110_SetCursor(1, 2);
  Nokia5110_OutString("enter for");
  Nokia5110_SetCursor(1, 3);
  Nokia5110_OutString("begin!");
  Nokia5110_SetCursor(2, 4);
	/*initalize x and y coordinates for small balls*/
	for(i = 0; i < nwall; ++i){
		xpositions[i] = x;
		x = x + 4;		
	}
	x = 4;
	for(i = 0; i < nrow; ++i){
		ypositions[i] = x ;
		x = x + 4;
	}
	/*initalize 2-demintional array by 1 inicate that all small balls is exits*/
	for(i = 0; i < nrow; ++i){
		for(j = 0; j < nwall; ++j){
			exist[i][j] = 1;
		}
	}
	
	LED_Init(PORTB_ID,PIN0_ID); //led 1 init
	LED_Init(PORTB_ID,PIN1_ID); //led 2 init
	if(UART_InChar()){  //recieve from keyboard
			UART_OutString("Welcome ");  //show in putty
			BUTTON_Init(PORTB_ID,PIN3_ID,INT);  //initalize        
			BUTTON_Init(PORTB_ID,PIN4_ID,INT);
			Timer2_Init(8000000);
			EnableInterrupts();  // The grader uses interrupts
	}
  while(cnt<3){
		
  }
	
	LED_Off(PORTB_ID,PIN0_ID);
	LED_Off(PORTB_ID,PIN1_ID);
	Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();      // draw buffer
	if(success){
		Nokia5110_Clear();
		Nokia5110_SetCursor(1, 1);
		Nokia5110_OutString("CONGRATULAT");
		Nokia5110_SetCursor(4, 2);
		Nokia5110_OutString("IONS");
		Nokia5110_SetCursor(3, 4);
		Nokia5110_OutString("YOU WON");
	}
	else{
		Nokia5110_Clear();
		Nokia5110_SetCursor(1, 1);
		Nokia5110_OutString("GAME OVER");
		Nokia5110_SetCursor(1, 2);
		Nokia5110_OutString("Nice try!");
	}
	UART_OutString("Bye ");
}


void DX_Ball(){
	// check if the ball hit any block 
	for(i = 0; i < nrow; ++i){
			for(j = 0; j < nwall; ++j){
				if(exist[i][j] == 1){
						// if the ball hit block from below	
						if((ballYPOS - BALLH == ypositions[i])  && (( ballXPOS <= xpositions[j] && ballXPOS + BALLW >= xpositions[j] ) || ( ballXPOS <= xpositions[j] + WALLW && ballXPOS + BALLW >= xpositions[j] + WALLW )) ){ 
								u_d = 2;
								l_r = Random() % 2;
								exist[i][j] = 0;
								nexist -= 1;
						}
						// if the ball hit block from above
						else if((ballYPOS == ypositions[i] - 2)  && (( ballXPOS <= xpositions[j] && ballXPOS + BALLW >= xpositions[j] ) || ( ballXPOS <= xpositions[j] + WALLW && ballXPOS + BALLW >= xpositions[j] + WALLW )) ){
								u_d = 1;
								l_r = Random() % 2;
								exist[i][j] = 0;
								nexist -= 1;
						}
						// if the ball hit block from left
						else if((ballXPOS + BALLW == xpositions[j]) && ((ypositions[i] <= ballYPOS && ypositions[i] >= ballYPOS - BALLH) || ((ypositions[i] - WALLH <= ballYPOS && ypositions[i] - WALLH >= ballYPOS - BALLH)) ) ){
								l_r = 0;
								exist[i][j] = 0;
								nexist -= 1;
						}
						// if the ball hit block from right
						else if((ballXPOS + 1 == xpositions[j] + WALLW) && ((ypositions[i] <= ballYPOS && ypositions[i] >= ballYPOS - BALLH) || ((ypositions[i] - 1 <= ballYPOS && ypositions[i] - 1 >= ballYPOS - BALLH)) ) ){
								exist[i][j] = 0;
								l_r = 1;
								nexist -= 1;
						}
				}
			}
		}
		// check if you win the game
		if(nexist <= 0) {
			success = 1;
			cnt = 100;
		}
		// if the ball hit the upper border of screen
		if(ballYPOS - BALLH == 2 ) u_d = 2, l_r = Random() % 2;
		
		// if the ball hit the bunker
		if(((ballYPOS == 47 - BUNKERH) && ((ballXPOS >= bunkerXPOS && ballXPOS <= bunkerXPOS + BUNKERW) || (ballXPOS + BALLW >= bunkerXPOS && ballXPOS + BALLW <= bunkerXPOS + BUNKERW)))){
			u_d = 1;
			l_r = Random() % 2;
		}
		
		// change the factor of  y according to the value of up_down(u_d) variable
		if(u_d == 1) ballyf = -1;
		else if(u_d == 2) ballyf = 1;
		else ballyf = 0;
		
		// change the factor of  x according to the value of up_down(u_d) variable
		if(l_r == 0) ballxf = -1;
		else if(l_r == 1)ballxf = 1;
		
		// if the ball hit the ground (you lose)
		if(ballYPOS == 47) {
				cnt+=1;
				bunkerXPOS = 34;
				ballXPOS = 41;
				ballYPOS = 47 - 5;
				ballxf = 0;
				ballyf = -1;
				u_d = 1;
				l_r = 3;
				Delay100ms(10);
		}
		
		// if the ball in the left border
		if(ballXPOS == 4) l_r = 1;
		
		// if the ball in the right border
		if(ballXPOS + BALLW == 81)l_r = 0;
		
		
		Nokia5110_ClearBuffer();
		
		// print the exist blocks
		for(i = 0; i < nrow; ++i){
			for(j = 0; j < nwall; ++j){
				
				if(exist[i][j] == 1){
					Nokia5110_PrintBMP(xpositions[j],  ypositions[i], wall, 0);
				}
			}
		}
		
		Nokia5110_PrintBMP(bunkerXPOS, 47 , Bunker0, 0);
		Nokia5110_PrintBMP(ballXPOS, ballYPOS , ball, 0);	
		Nokia5110_DisplayBuffer();	

}
// You can use this timer only if you learn how it works
void Timer2_Init(unsigned long period){ 
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
  delay = SYSCTL_RCGCTIMER_R;
  TimerCount = 0;
  Semaphore = 0;
  TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 39, interrupt number 23
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC
  TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}

void GPIOPortB_Handler(void){
		uint8 i=0;
		for(i=0;i<=7;i++){
			if(GPIO_PORTB_RIS_R & (1<<i)){
				SET_BIT(GPIO_PORTB_ICR_R,i);      // acknowledge (clear flag)
				//if(g_callBackPtr!=NULL_PTR){(*g_callBackPtr)();}
				if(i==3){//left
					if(bunkerXPOS > 3) bunkerXPOS = bunkerXPOS - 3; 
					LED_On(PORTB_ID,PIN0_ID);  // LED is green
					LED_Off(PORTB_ID,PIN1_ID);
				}
				if(i==4){//right
					if(bunkerXPOS + BUNKERW < 82) bunkerXPOS = bunkerXPOS + 3;
					LED_On(PORTB_ID,PIN1_ID);  // LED is green
					LED_Off(PORTB_ID,PIN0_ID);
					//LED_Off(PORTB_ID,PIN2_ID);
				}
				break;
			}
		}
}

void Timer2A_Handler(void){ 
  TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
  TimerCount++;
  Semaphore = 1; // trigger
	
	ballYPOS = ballYPOS + ballyf;
	ballXPOS = ballXPOS + ballxf;
	
	DX_Ball();
}

void Delay100ms(unsigned long count){unsigned long volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}


