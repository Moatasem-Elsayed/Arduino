#include "tm4c123gh6pm.h" // Device header


/******** i use the driver of TMC4123 for lcd , keypad ,gpios(motor)
and the next defenations of memory mapping i use it to defind uart0
***********/
// UART registers (UART0)
//
//*****************************************************************************
#define UART0_DR_R              (*((volatile uint32_t *)0x4000C000))
#define UART0_RSR_R             (*((volatile uint32_t *)0x4000C004))
#define UART0_ECR_R             (*((volatile uint32_t *)0x4000C004))
#define UART0_FR_R              (*((volatile uint32_t *)0x4000C018))
#define UART0_ILPR_R            (*((volatile uint32_t *)0x4000C020))
#define UART0_IBRD_R            (*((volatile uint32_t *)0x4000C024))
#define UART0_FBRD_R            (*((volatile uint32_t *)0x4000C028))
#define UART0_LCRH_R            (*((volatile uint32_t *)0x4000C02C))
#define UART0_CTL_R             (*((volatile uint32_t *)0x4000C030))
#define UART0_IFLS_R            (*((volatile uint32_t *)0x4000C034))
#define UART0_IM_R              (*((volatile uint32_t *)0x4000C038))
#define UART0_RIS_R             (*((volatile uint32_t *)0x4000C03C))
#define UART0_MIS_R             (*((volatile uint32_t *)0x4000C040))
#define UART0_ICR_R             (*((volatile uint32_t *)0x4000C044))
#define UART0_DMACTL_R          (*((volatile uint32_t *)0x4000C048))
#define UART0_9BITADDR_R        (*((volatile uint32_t *)0x4000C0A4))
#define UART0_9BITAMASK_R       (*((volatile uint32_t *)0x4000C0A8))
#define UART0_PP_R              (*((volatile uint32_t *)0x4000CFC0))
#define UART0_CC_R              (*((volatile uint32_t *)0x4000CFC8))
#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty
#define UART_LCRH_WLEN_8        0x00000060  // 8 bit word length
#define UART_LCRH_FEN           0x00000010  // UART Enable FIFOs
#define UART_CTL_UARTEN         0x00000001  // UART Enable
//*****************************************************************************
#define GPIO_PORTA_DATA_BITS_R  ((volatile uint32_t *)0x40004000)
#define GPIO_PORTA_DATA_R       (*((volatile uint32_t *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile uint32_t *)0x40004400))
#define GPIO_PORTA_IS_R         (*((volatile uint32_t *)0x40004404))
#define GPIO_PORTA_IBE_R        (*((volatile uint32_t *)0x40004408))
#define GPIO_PORTA_IEV_R        (*((volatile uint32_t *)0x4000440C))
#define GPIO_PORTA_IM_R         (*((volatile uint32_t *)0x40004410))
#define GPIO_PORTA_RIS_R        (*((volatile uint32_t *)0x40004414))
#define GPIO_PORTA_MIS_R        (*((volatile uint32_t *)0x40004418))
#define GPIO_PORTA_ICR_R        (*((volatile uint32_t *)0x4000441C))
#define GPIO_PORTA_AFSEL_R      (*((volatile uint32_t *)0x40004420))
#define GPIO_PORTA_DR2R_R       (*((volatile uint32_t *)0x40004500))
#define GPIO_PORTA_DR4R_R       (*((volatile uint32_t *)0x40004504))
#define GPIO_PORTA_DR8R_R       (*((volatile uint32_t *)0x40004508))
#define GPIO_PORTA_ODR_R        (*((volatile uint32_t *)0x4000450C))
#define GPIO_PORTA_PUR_R        (*((volatile uint32_t *)0x40004510))
#define GPIO_PORTA_PDR_R        (*((volatile uint32_t *)0x40004514))
#define GPIO_PORTA_SLR_R        (*((volatile uint32_t *)0x40004518))
#define GPIO_PORTA_DEN_R        (*((volatile uint32_t *)0x4000451C))
#define GPIO_PORTA_LOCK_R       (*((volatile uint32_t *)0x40004520))
#define GPIO_PORTA_CR_R         (*((volatile uint32_t *)0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile uint32_t *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile uint32_t *)0x4000452C))
#define GPIO_PORTA_ADCCTL_R     (*((volatile uint32_t *)0x40004530))
#define GPIO_PORTA_DMACTL_R     (*((volatile uint32_t *)0x40004534))

#define SYSCTL_RCGCUART_R       (*((volatile uint32_t *)0x400FE618))
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))
/*********************************************************************************************/
//Displays character pressed on keypad on LCD
#define MOTOR		GPIOF
#define MOTOR_PIN       0
#define KEYPAD_ROW 	GPIOE
#define KEYPAD_COL 	GPIOC

#define LCD_DATA GPIOB
#define LCD_CTRL GPIOA
#define RS 0x20 /* PORTA BIT5 mask */
#define RW 0x40 /* PORTA BIT6 mask */
#define EN 0x80 /* PORTA BIT7 mask */

void UART_Init(void);
char UART_InChar(void);
unsigned int UART_InUDec(void);

void delayMs(int n);
void delayUs(int n);

void lcd_string(const unsigned char*str);
void lcd_clear();
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);

void keypad_init(void);
unsigned char keypad_getkey(void);

void portf_init();

unsigned int id_client=12345;
int main(void)
{
    unsigned char id_trial=0,key=0,floor=0,wait;
    UART_Init();
    keypad_init();
    LCD_init();
    portf_init();
    while(1)
    {
        lcd_clear();
        LCD_command(0x80); 			/* LCD set cursor location at first line  */
        lcd_string("please enter id ");
        id_trial=UART_InUDec();                 // get the id number from user
        
        if(id_trial==id_client)                  //check if user`s id equal to our client 
        {
          
            lcd_clear();
            LCD_command(0x80); 
            lcd_string("Welcome MR ..... ");
            
            LCD_command(0xC0); 
            lcd_string("please set the floor");
            delayMs(2000);
            key = keypad_getkey(); 		/* read the keypad */
                          
                       if (key >='0'&&key<='8')
                           {
                              floor=key;
                              wait=(10000);   // floor 1 motor will work ten second and floor 2 will work 20 second and etc 
                              /* if a key is pressed */
                                lcd_clear();
                                LCD_command(0x80); 
                                lcd_string("your floor is ");
                                delayMs(1000);
                                
                                LCD_command(0xC0); // second line 
                                LCD_data(key); /* display the key label */
                                delayMs(1000);
                                
                                LCD_command(0x80); 
                                lcd_string("                                 "); // clear first line and leave the second with number of floor
                                
                                LCD_command(0x80);
                                lcd_string(" press '*' to confirm or rest ");
                                delayMs(1000);
                                        do{ 
                                                key = keypad_getkey(); 		/* read the keypad */
                                        }while(key != '*');
                                        
                                for(int i=1;i<=(floor-'0');i++)
                                {
                                      MOTOR->DATA |=(1<<MOTOR_PIN);
                                      delayMs(wait);                    // we can replace the delay with input sensor like limitswitch 
                                     
                                     LCD_command(0xC0); // second line 
                                      LCD_data(i); /* display the key label */
                                 }
                                   MOTOR->DATA &=~(1<<MOTOR_PIN);
                            }
                            
                            else
                            {
                              //key of floor not pressed
                            }
        }
        else if (id_trial!=0 && id_trial!=id_client)
        {
          /****** wrong id ******/
                      lcd_clear();
                      LCD_command(0x80); 
                      lcd_string("try again  ");
                        delayMs(2000);
          }
        else
        {
          /* still not entered the id 
            **/
        }
      
    }//while
}//void
/***************************************************************************************************/
void portf_init()
{
    volatile unsigned long delay;
    SYSCTL->RCGC2|=(1<<5); //clock to portf
    delay=SYSCTL->RCGC2; // wait to se the clock
    GPIOF->LOCK=0x4C4F434B; // unlock portf
    MOTOR->AMSEL=0x00;
    MOTOR->DIR|=(1<<MOTOR_PIN);
    MOTOR->DEN|=(1<<MOTOR_PIN) ;
}


/* this function initializes the ports connected to the keypad */
void keypad_init(void)
{
    SYSCTL->RCGCGPIO |= 0x04; /* enable clock to GPIOC */
    SYSCTL->RCGCGPIO |= 0x10; /* enable clock to GPIOE */

    KEYPAD_ROW->DIR |= 0x0F; /* set row pins 3-0 as output */
    KEYPAD_ROW->DEN |= 0x0F; /* set row pins 3-0 as digital pins */
    KEYPAD_ROW->ODR |= 0x0F; /* set row pins 3-0 as open drain */

    KEYPAD_COL->DIR &= ~0xF0; /* set column pin 7-4 as input */
    KEYPAD_COL->DEN |= 0xF0; /* set column pin 7-4 as digital pins */
    KEYPAD_COL->PUR |= 0xF0; /* enable pull-ups for pin 7-4 */
}

/* This is a non-blocking function to read the keypad. */
/* If a key is pressed, it returns the key label in ASCII encoding. Otherwise, it returns a 0 (not ASCII 0). */
unsigned char keypad_getkey(void)
{
    const unsigned char keymap[4][4] =
    {
        { '1', '2', '3', 'A'},
        { '4', '5', '6', 'B'},
        { '7', '8', '9', 'C'},
        { '*', '0', '#', 'D'},
    };

    int row=0, col=0;

    /* check to see any key pressed first */
    KEYPAD_ROW->DATA = 0; /* enable all rows */
    col = KEYPAD_COL->DATA & 0xF0; /* read all columns */
    if (col == 0xF0) return 0; /* no key pressed */

    /* If a key is pressed, it gets here to find out which key. */
    /* Although it is written as an infinite loop, it will take one of the breaks or return in one pass.*/
    while (1)
    {
        row = 0;
        KEYPAD_ROW->DATA = 0x0E; /* enable row 0 */
        delayUs(2); /* wait for signal to settle */
        col = KEYPAD_COL->DATA & 0xF0;
        if (col != 0xF0) break;

        row = 1;
        KEYPAD_ROW->DATA = 0x0D; /* enable row 1 */
        delayUs(2); /* wait for signal to settle */
        col = KEYPAD_COL->DATA & 0xF0;
        if (col != 0xF0) break;

        row = 2;
        KEYPAD_ROW->DATA = 0x0B; /* enable row 2 */
        delayUs(2); /* wait for signal to settle */
        col = KEYPAD_COL->DATA & 0xF0;
        if (col != 0xF0) break;

        row = 3;
        KEYPAD_ROW->DATA = 0x07; /* enable row 3 */
        delayUs(2); /* wait for signal to settle */
        col = KEYPAD_COL->DATA & 0xF0;
        if (col != 0xF0) break;

        return 0; /* if no key is pressed */
    }

    /* gets here when one of the rows has key pressed */
    if (col == 0xE0) return keymap[row][0]; /* key in column 0 */
    if (col == 0xD0) return keymap[row][1]; /* key in column 1 */
    if (col == 0xB0) return keymap[row][2]; /* key in column 2 */
    if (col == 0x70) return keymap[row][3]; /* key in column 3 */
    return 0; /* just to be safe */
}

void LCD_init(void)
{
    SYSCTL->RCGCGPIO |= 0x01; /* enable clock to GPIOA */
    SYSCTL->RCGCGPIO |= 0x02; /* enable clock to GPIOB */

    LCD_CTRL->DIR |= 0xE0; /* set PORTA pin 7-5 as output for control */
    LCD_CTRL->DEN |= 0xE0; /* set PORTA pin 7-5 as digital pins */
    LCD_DATA->DIR = 0xFF; /* set all PORTB pins as output for data */
    LCD_DATA->DEN = 0xFF; /* set all PORTB pins as digital pins */

    delayMs(20); /* initialization sequence */
    LCD_command(0x30);
    delayMs(5);
    LCD_command(0x30);
    delayUs(100);
    LCD_command(0x30);

    LCD_command(0x38); /* set 8-bit data, 2-line, 5x7 font */
    LCD_command(0x06); /* move cursor right */
    LCD_command(0x01); /* clear screen, move cursor to home */
    LCD_command(0x0F); /* turn on display, cursor blinking */
}

void LCD_command(unsigned char command)
{
    LCD_CTRL->DATA = 0; /* RS = 0, R/W = 0 */
    LCD_DATA->DATA = command;
    LCD_CTRL->DATA = EN; /* pulse E */
    delayUs(0);
    LCD_CTRL->DATA = 0;
    if (command < 4) delayMs(2); /* command 1 and 2 needs up to 1.64ms */ else delayUs(40); /* all others 40 us */
}
void LCD_data(unsigned char data)
{
    LCD_CTRL->DATA = RS; /* RS = 1, R/W = 0 */
    LCD_DATA->DATA = data;
    LCD_CTRL->DATA = EN | RS; /* pulse E */
    delayUs(0);
    LCD_CTRL->DATA = 0;
    delayUs(40);
}

void lcd_string(const unsigned char*str)
{
    unsigned char i=0;
    while(str[i]!='\0')
    {
        LCD_data(str[i]);
        i++;
    }
}
void lcd_clear()
{
LCD_command(0x01);
}
/* delay n milliseconds (50 MHz CPU clock) */
void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 3180; j++)
        {} /* do nothing for 1 ms */
}

/* delay n microseconds (50 MHz CPU clock) */
void delayUs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 3; j++)
        {} /* do nothing for 1 us */
}

//------------UART_Init------------

// Initialize the UART for 115,200 baud rate (assuming 50 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// uart on portA pin 0 rx
// uart on portA pin 1 tx

void UART_Init(void)
{

    SYSCTL_RCGCUART_R |= 0x01;            // activate UART0
    SYSCTL_RCGCGPIO_R |= 0x01;            // activate port A
    while((SYSCTL_PRGPIO_R&0x01) == 0);
    UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
    UART0_IBRD_R = 27;                    // IBRD = int(50,000,000 / (16 * 115,200)) = int(27.1267)
    UART0_FBRD_R = 8;                     // FBRD = int(0.1267 * 64 + 0.5) = 8
    // 8 bit word length (no parity bits, one stop bit, FIFOs)
    UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
    UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART
    GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
    GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1-0
    // configure PA1-0 as UART
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
    GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA
}

//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
char UART_InChar(void)
{
    while((UART0_FR_R&UART_FR_RXFE) != 0);
    return((char)(UART0_DR_R&0xFF));
}

//------------UART_InUDec------------
// InUDec accepts ASCII input in unsigned decimal format
//     and converts to a 32-bit unsigned number
//     valid range is 0 to 4294967295 (2^32-1)
// Input: none
// Output: 32-bit unsigned number
// If you enter a number above 4294967295, it will return an incorrect value
// Backspace will remove last digit typed
uint32_t UART_InUDec(void)
{
    uint32_t number=0, length=0;
    char character;
    character = UART_InChar();
    while(character != '\0')  // accepts until <finsinsh string> is typed
    {
// The next line checks that the input is a digit, 0-9.
// If the character is not 0-9, it is ignored and not echoed
        if((character>='0') && (character<='9'))
        {
            number = 10*number+(character-'0');   // this line overflows if above 4294967295
            length++;
            //UART_OutChar(character);
        }
      
        character = UART_InChar();
    }
    return number;
}

