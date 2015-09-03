///////////////////////////////
/*
Program for laser table.
Three lasers on table,
three lamps with according colors,
one relay for electromagnetic lock
*/
///////////////////////////////

 #include <mega328p.h>
 #include <delay.h>
      
 //DDR Inputs
 #define RED_SENS_DDR   DDRD.3
 #define GREEN_SENS_DDR DDRD.2
 #define BLUE_SENS_DDR  DDRD.1
 
 //Input Pins
 #define RED_PIN   PIND.3
 #define GREEN_PIN PIND.2
 #define BLUE_PIN  PIND.1
 
 //PINs Pull-Down
 #define RED_PIN_PU   PORTD.3
 #define GREEN_PIN_PU PORTD.2
 #define BLUE_PIN_PU  PORTD.1
  
 //DDR Output Lamps 
 #define RED_LAMP_DDR   DDRB.0
 #define GREEN_LAMP_DDR DDRD.6
 #define BLUE_LAMP_DDR  DDRD.4
 //Lamp's Ports
 #define RED_LAMP   PORTB.0
 #define GREEN_LAMP PORTD.6
 #define BLUE_LAMP  PORTD.4
 
 //Laser turn-off relay port
 #define LASERS_DDR DDRD.5       
 #define LASERS_OFF PORTD.5
 
 //Lock open port
 #define LOCK_OPEN_DDR DDRD.7
 #define LOCK_OPEN     PORTD.7
 
 char red=0, green=0, blue=0;
            
 
 void main(void) {
 
 RED_SENS_DDR = GREEN_SENS_DDR = BLUE_SENS_DDR = 0; //пины сенсоров: на вход

 RED_PIN_PU = GREEN_PIN_PU = BLUE_PIN_PU = 1; //подтяжка пинов к Vcc
 
 RED_LAMP_DDR = GREEN_LAMP_DDR = BLUE_LAMP_DDR = LASERS_DDR = LOCK_OPEN_DDR = 1; //пины ламп, лазеров и отпирания замка: на выход
 
 RED_LAMP = GREEN_LAMP = BLUE_LAMP = LASERS_OFF = LOCK_OPEN = 0; //изначальные уровни ламп, реле выключения лазеров и реле отпирания замка - низкие
  
 DDRB.5=1;  //конфигурации для
 PORTB.5=0; //штатного светодиода на плате   
    
  while(1) {
  
    if (!RED_PIN)   {delay_ms(1); if (!RED_PIN)   {RED_LAMP=1;   red=1;  }}
    if (!GREEN_PIN) {delay_ms(1); if (!GREEN_PIN) {GREEN_LAMP=1; green=1;}}
    if (!BLUE_PIN)  {delay_ms(1); if (!BLUE_PIN)  {BLUE_LAMP=1;  blue=1; }}
    
    if (red && green && blue) {
    PORTB.5=1;    //штатный светодиод на плате
    LOCK_OPEN=1;  //открыли замок
    LASERS_OFF=1; //выключили лазеры
    while(1);     //закончили, до перезапуска (запуск при переходе игроков из кабинета в лабораторию)
    }
  }
 
 }