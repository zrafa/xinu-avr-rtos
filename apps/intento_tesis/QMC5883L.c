#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include "twi.h"
#include <stddef.h>
#include <xinu.h>


/* Dirección i2c del chip */
uint8_t SLAVE = 0x0D;

/* Números de Registro */
uint8_t REG_X_LSB = 0;
uint8_t REG_X_MSB = 1;
uint8_t REG_Y_LSB = 2 ;
uint8_t REG_Y_MSB = 3;
uint8_t REG_Z_LSB = 4;
uint8_t REG_Z_MSB = 5;
uint8_t REG_STATUS = 6;
uint8_t REG_TEMP_LSB = 7;
uint8_t REG_TEMP_MSB = 8;
uint8_t REG_CONFIG = 9;
uint8_t REG_CONFIG2 = 10;
uint8_t REG_RESET = 11;
uint8_t REG_RESERVED = 12;
uint8_t REG_CHIP_ID = 13;

/* Configuraciones para registros */

// 1) Regsitro STATUS
#define STATUS_DRDY 1
#define STATUS_OVL 2
#define STATUS_DOR 4

// 2) Registro CONFIG 

// Valores de oversampling
#define CONFIG_OS512 0b00000000
#define CONFIG_OS256 0b01000000
#define CONFIG_OS128 0b10000000
#define CONFIG_OS64  0b11000000

// Valores de rango
#define CONFIG_2GAUSS 0b00000000
#define CONFIG_8GAUSS 0b00010000

// Valores de velocidad
#define CONFIG_10HZ   0b00000000
#define CONFIG_50HZ   0b00000100
#define CONFIG_100HZ  0b00001000
#define CONFIG_200HZ  0b00001100

// Valores de modo 
#define CONFIG_STANDBY 0b00000000
#define CONFIG_CONT    0b00000001

// Valores de reset
#define CONFIG_SOFTRESET 0b10000000

// 3) Registro CONFIG2
#define CONFIG2_NOINTERRUPT 0b00000001
#define CONFIG2_INTERRUPT 0b00000000
#define CONFIG2_POINTROLLOVER_NORMAL 0b00000000
#define CONFIG2_POINTROLLOVER_DESPLAZAMIENTO 0b01000000

// 4) Registro RESET
#define RESET_SETRESET 0b00000001

uint8_t dato, *medicion, buffer[2];
int mx, my, mz;
double declinacion_cipo = 2.5; //declinación +2°5'(Cipolletti-Río Negro)
double declinacion_nqn = 2.1; //declinación +2°1'(Neuquén-Talero 454)


void leer_dato(uint8_t address, uint8_t *data)
{
    dato = *data;    
}

void leer_medicion_eje(uint8_t address, uint8_t *data)
{
    medicion = data;    
}

//Lee la config del reg 9 de configuración y la imprime por serial
//Solo se usó para debugging
void leer_reg_config_1()
{
    twi_write(SLAVE,&REG_CONFIG ,1,NULL);
    twi_read(SLAVE,1,leer_dato);

    printf("\n\r Registro de config: %d",dato);

}

void magnetometro_init(void)
{
    twi_init();  //Inicializa la interfaz i2c
    sei();       //Habilita interrupciones
   
    //Hace un soft reset. Prende el bit 7 del registro 0AH
    buffer[0]=REG_CONFIG;
    buffer[1]=CONFIG_SOFTRESET;
    twi_write(SLAVE,(uint8_t *)&buffer,2,NULL);

    //Como aconseja el datasheet, deja el registro 11 como 0x01
    buffer[0]=REG_RESET;
    buffer[1]=RESET_SETRESET;
    twi_write(SLAVE,(uint8_t *)&buffer,2,NULL);

    //Configura el registro 2
    //Desactiva interrupciones y activa Point Roll Over Function
    buffer[0]=REG_CONFIG2;
    buffer[1]=CONFIG2_NOINTERRUPT || CONFIG2_POINTROLLOVER_DESPLAZAMIENTO;
    twi_write(SLAVE,(uint8_t *)&buffer,2,NULL);

    //Configura el registro 1
    //Modo continuo, ODR=100Hz, RNG=8G y OSR=512
    buffer[0]=REG_CONFIG;
    buffer[1] = CONFIG_CONT || CONFIG_100HZ || CONFIG_8GAUSS || CONFIG_OS512;
    twi_write(SLAVE,(uint8_t *)&buffer,2,NULL);
    
    printf("\n\rInit terminado");
}

//Función que utilizamos para la primer interacción con el módulo
void hello(uint8_t SLAVE)
{
    //Envia 2 veces 0x0D
    twi_write(SLAVE,&SLAVE, 1,NULL);
    
    //Lee la respuesta
    twi_read(SLAVE,1,leer_dato);

    printf("\n\r Respuesta inicial: %d",dato);

}

double get_angulo()
{
        twi_write(SLAVE,&REG_X_LSB , 1,NULL);
        twi_read(SLAVE,1,leer_medicion_eje);

        printf("  delay para la lectura  ");
         
        mx = *medicion;
        
        twi_write(SLAVE,&REG_X_MSB,1,NULL);
        twi_read(SLAVE,1,leer_medicion_eje);
        
        mx = mx + ((*medicion)<<8);
        
        twi_write(SLAVE,&REG_Y_LSB , 1,NULL);
        twi_read(SLAVE,1,leer_medicion_eje);

        printf("  delay para la lectura  ");
        
        my = *medicion;
        
        twi_write(SLAVE,&REG_Y_MSB, 1,NULL);
        twi_read(SLAVE,1,leer_medicion_eje);
        
        my = my + ((*medicion)<<8);
        
        twi_write(SLAVE,&REG_Z_LSB , 1,NULL);
        twi_read(SLAVE,1,leer_medicion_eje);

        printf("  delay para la lectura  ");
        
        mz = *medicion;
        
        twi_write(SLAVE,&REG_Z_MSB , 1,NULL);
        twi_read(SLAVE,1,leer_medicion_eje);

        
        mz = mz + ((*medicion)<<8);
        
        //Calcula el ángulo del eje X con respecto al norte
        double angulo = atan2(my, mx);
        angulo=angulo*(180/M_PI);//Conversión de Radianes a grados
        angulo=angulo-declinacion_nqn; //Corrige la declinación magnética
        
        //Calcula el ángulo equivalente de [-180,180] a [0,360]
        if(angulo<0) angulo=angulo+360;
  
        return angulo;
        
}


void printf_double (double valor){
//Toma como entrada una variable double y produce un arreglo
//de caracteres con ese valor de entrada.
//Formato de la salida: xxx.x
    
    char resultado[6];
    int valor_entero = valor*10, i, divisor = 1000;
    	
	for(i=0;i<3;i++)
	{
		resultado[i] = valor_entero/divisor + 48;
        valor_entero = valor_entero % divisor;
        divisor = divisor/10; 
	}
    resultado[3]='.';
    resultado[4]=valor_entero+48;
	resultado[5]='\0'; //Fin de cadena
	
	printf("%s",resultado);
}

int mostrar_angulo(void)
{
    double angulo;      
    angulo = get_angulo();
    printf("\n\rÁngulo: ");
    printf_double(angulo);

    return 0;
}

//No debería ir en este dirver - es solo para probar
/*int main(void)
{
    double angulo;    

    serial_init(); //Inicializar el puerto serial
    magnetometro_init(); //Inicia el magnetómetro
           
    while(1){
        angulo = get_angulo();
        serial_put_str("\n\rAngulo MAIN:");
        serial_put_double(angulo,4,4);
        _delay_ms(1500);
    }
    return 0;
}*/
