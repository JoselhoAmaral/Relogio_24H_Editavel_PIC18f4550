#include<18F4550.h>           
#fuses HS, NOWDT, CPUDIV1
#use delay (clock=20MHz)

int horasDezena = 0;
int horasUnidade = 0;
int minutosDezena = 0;
int minutosUnidade = 0;
long int conteSegundos = 0;

/*Matriz de 10 posi��es contendo o valor a ser enviado para a porta D a fim de
   mostrar o d�gito referente nos displays */
int digito[10] =
               {0b00111111,    //D�gito 0
                0b00000110,    //D�gito 1
                0b01011011,    //D�gito 2
                0b01001111,    //D�gito 3
                0b01100110,    //D�gito 4
                0b01101101,    //D�gito 5
                0b01111101,    //D�gito 6
                0b00000111,    //D�gito 7
                0b01111111,    //D�gito 8
                0b01101111     //D�gito 9
               };
               
void main(){

port_b_pullups(true);   // Liga os pull ups
output_d(0);            // Desliga todas as portas D
SET_TRIS_B(0xFF);
SET_TRIS_D(0x00);

while(true){

//--- Ciclo de repeti��o do dos 4 display's LED's. dura��o 20ms -------------//
//Display horas dezena
OUTPUT_D(digito[horasDezena]);
OUTPUT_A(0b00000100);
delay_ms(5); 

//Display horas unidade
OUTPUT_D(digito[horasUnidade]);
OUTPUT_A(0b00001000);
delay_ms(5);

//Display minutos dezena
OUTPUT_D(digito[minutosDezena]);
OUTPUT_A(0b00010000);
delay_ms(5);

//Display minutos unidade
OUTPUT_D(digito[minutosUnidade]);
OUTPUT_A(0b00100000);
delay_ms(5);
//---------------------------------------------------------------------------// 

// Dado que 60s = 60.000ms = 3.000x20ms = 1min.
if(conteSegundos == 3000){
   minutosUnidade++;
}

// if que adiciona + 1 minuto caso aperte o bot�o B0 ------------------------//
if((input(pin_b0)) == 0){
   minutosUnidade++;
   delay_ms(300);
}

// if que adiciona + 1 hora caso aperte o bot�o B1 --------------------------//
if((input(pin_b1)) == 0){
   horasUnidade++;
   delay_ms(300);
}

// Reseta o ciclo unidade quando chega a 10 e adiciona mais 1 ao ciclo dezena//
if (minutosUnidade == 10){
   minutosUnidade = 0;
   minutosDezena++; 
}

// Reseta o ciclo de 60 minutos e adiciona 1 a horas ------------------------//
if (((minutosDezena*10) + minutosUnidade) == 60){
   minutosDezena = 0;   
   minutosUnidade = 0;
   horasUnidade++;
}

// Reseta a unidade de horas quando ela chega a 10 e adiciona 1 a dezena de horas //
if (horasUnidade == 10){
   horasUnidade = 0;
   horasDezena++; 
}

// Zera o rel�gio quando chega em 24 horas.
if ((horasDezena == 2)&&(horasUnidade == 4)){
   horasDezena = 0;
   horasUnidade = 0;
   minutosDezena = 0;
   minutosUnidade = 0;
}
conteSegundos++;
}
}
