#include "mbed.h"

#define INTERVAL 40     // intervalo de lecturas en ms para el boton

typedef enum{
    BUTTON_DOWN,    // boton pulsado
    BUTTON_UP,      // boton sin pulsar
    BUTTON_FALLING, // boton siendo presionado
    BUTTON_RISING   // boton siendo soltado
}_eButtonState;

_eButtonState myButton; // dato del tipo enum (constantes enteras) para asignar los estados de la MEF

/**
 * @brief Inicializa MEF
 * Le da un valor a myButton
 */
void startMEF();

/**
 * @brief MEF maquina de estados finitos
 * Actualiza el estado del boton cada vez que se invoca
 * @param buttonState Se usa para pasar el estado del boton con el read()
 */
void actuallizaMef(uint8_t buttonState);

/**
 * @brief Cambia el estado del led
 * Cambia el estado de encendido a apagado o de apagado a encendido
 */
void togleLed();

DigitalOut LED(PC_13);
DigitalIn boton(PA_0);

int main(){
    
    while(1){
    	
    }
}

void startMEF(){
    myButton = BUTTON_UP;
}

void actuallizaMef(uint8_t buttonState){
    switch (myButton){
    case BUTTON_DOWN:                         //Con el estado anterior de presionado
        if(buttonState)                       //Si el boton está ahora "sin presionar" 
            myButton=BUTTON_RISING;           //El boton está el un flanco de subida

    break;
    case BUTTON_UP:                           //Con el estdo anterior de "sin presionar"
        if(!buttonState)                      //Si el boton está ahora "presionado"
            myButton=BUTTON_FALLING;          //El boton está en un flanco de bajada
    
    break;
    case BUTTON_FALLING:                      //Con el estado anterior de flanco de bajada
        if(!buttonState){                     //Si el boton ahora está "presionado"
            myButton=BUTTON_DOWN;             //El botón está presionado definitivamente
        }
        else                                  //Si el boton está "sin presionar"
            myButton=BUTTON_UP;                

    break;
    case BUTTON_RISING:                       //Con el estado anterior en flanco de subida
        if(buttonState){                      //Si el boton ahora está "sin presionar"
            myButton=BUTTON_UP;               //El boton está sin presionar definiticamente
        }

        else
            myButton=BUTTON_DOWN;
    
    break;
    
    default:
    startMEF();
        break;
    }
}

void togleLed(){
    LED=!LED;
}