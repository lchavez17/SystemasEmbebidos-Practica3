#include <18F4620.h>
#USE delay(clock=16000000)        //Configurando el reloj a 32Mhz
#fuses XT, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)
int contador_100ms=0;         //Declaramos variable contador para tiempo de 100ms. Sabremos cuantas veces se ha ejecutado la interrupción
int contador_500ms=0;         //Declaramos variable contador para tiempo de 100ms. Sabremos cuantas veces se ha ejecutado la interrupción
int contador_1000ms=0;        //Declaramos variable contador para tiempo de 100ms. Sabremos cuantas veces se ha ejecutado la interrupción
int contador_1500ms=0;        //Declaramos variable contador para tiempo de 100ms. Sabremos cuantas veces se ha ejecutado la interrupción
#int_timer0                  //Declaramos interrupción de TIMER0
void TIMER0_funcion(void)    //Funcion de interupción de TIMER0. Cada que ocurra una interrupcion de TIMER0 ingcrementara en uno las variables de los contadores de tiempo
{
   contador_100ms++;         
   contador_500ms++;
   contador_1000ms++;
   contador_1500ms++;
}
   
   void main(void)
   {
      setup_oscillator(OSC_16MHZ);
      SETUP_ADC_PORTS(NO_ANALOGS);
      int8 conAnilloA=0x20;             //Variable con el valor del valor para el contador de anillo del puerto A. Lo ponemos en el MSB
      int8 conAnilloB=0x80;             //Variable con el valor del valor para el contador de anillo del puerto B. Lo ponemos en el MSB
      int8 conAnilloC=0x80;             //Variable con el valor del valor para el contador de anillo del puerto C. Lo ponemos en el MSB
      int8 conAnilloD=0x80;             //Variable con el valor del valor para el contador de anillo del puerto D. Lo ponemos en el MSB}
      set_timer0(0);
      setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|T0_8_BIT);   //Configuracion de la fuente y divisor del TMR0 <<<<<<Acomodar
      enable_interrupts(int_TIMER0);  //Abilitamos la interrupcion TIMER0
      enable_interrupts(GLOBAL);      //Abilitamos las interrupciones globales   
      //
      //Configuramos puertos A,B,C y D como puertos de salida
      set_tris_a(0);
      set_tris_b(0);
      set_tris_c(0);
      set_tris_d(0);
      while(True)                        //Ciclo infinito
      {
         if(contador_100ms>=6)   //Si nuestro contador_100ms es mayor o igual a 6 quiere decir que ya han pasado 100ms desde que se desplazo conAnilloA entonces, se ejecuta contador de anillo del puerto A
         {
            conAnilloA>>=1;            //Desplazamos el bit del contador de anilo del puerto A
            contador_100ms=0;          //Regresemos el valor de contador_100ms a 0
            if(conAnilloA==0)          //Si el valor de conAnilloA sobrepaso el LSM, devuelbe el valor al MSB
            {
               conAnilloA=0x20; 
            }
         }
         if(contador_500ms>=30)   //Si nuestro contador_500ms es mayor o igual a 30 quiere decir que ya han pasado 500ms desde que se desplazo conAnilloB entonces, se ejecuta contador de anillo del puerto B
         {
            conAnilloB>>=1;            //Desplazamos el bit del contador de anillo del puerto B
            contador_500ms=0;          //Regresemos el valor de contador_500ms a 0
            if(conAnilloB==0)          //Si el valor de conAnilloB sobrepaso el LSM, devuelbe el valor al MSB
            {
               conAnilloB=0x80; 
            }
         }
         if(contador_1000ms>=61)   //Si nuestro contador_1000ms es mayor o igual a 61 quiere decir que ya han pasado 1000ms desde que se desplazo conAnilloC entonces, se ejecuta contador de anillo del puerto C
         {
            conAnilloC>>=1;            //Desplazamos el bit del contador de anilo del puerto C
            contador_1000ms=0;         //Regresemos el valor de contador_1000ms a 0
            if(conAnilloC==0)          //Si el valor de conAnilloC sobrepaso el LSM, devuelbe el valor al MSB
            {
               conAnilloC=0x80; 
            }
         }
         if(contador_1500ms>=91)   //Si nuestro contador_1500ms es mayor o igual a 91 quiere decir que ya han pasado 1500ms desde que se desplazo conAnilloD entonces, se ejecuta contador de anillo del puerto D
         {
            conAnilloD>>=1;            //Desplazamos el bit del contador de anilo del puerto D
            contador_1500ms=0;         //Regresemos el valor de contador_1500ms a 0
            if(conAnilloD==0)          //Si el valor de conAnilloD sobrepaso el LSM, devuelbe el valor al MSB
            {
               conAnilloD=0x80; 
            }
         }
         //Imprimimos contadores de anillos de los puertos A,B,C y D
         output_a(conAnilloA);
         output_b(conAnilloB);
         output_c(conAnilloC);
         output_d(conAnilloD);
         
      }
   }
