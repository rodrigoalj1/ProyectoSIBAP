#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
//#include <SoftwareSerial.h>
#define I2C_ADDR    0x3F

LiquidCrystal_I2C             lcd(I2C_ADDR,2, 1, 0, 4, 5, 6, 7);
void setup()
   {    //Serial.begin(9600);
        lcd.begin (16,2);    // Inicializar el display con 16 caraceres 2 lineas
        lcd.setBacklightPin(3,POSITIVE);
        lcd.setBacklight(LOW); // Apagar luz de fondo
        delay(500);
        lcd.setBacklight(HIGH); // Encender luz de fondo    
        delay(500);
        lcd.setBacklight(LOW); // Apagar luz de fondo
        delay(500);
        //lcd.home ();                   // go home
   }  
void loop() 
   {   //Serial.begin(9600);
       lcd.setBacklight(HIGH); // Encender luz de fondo
       lcd.home (); 
       lcd.clear ();
       lcd.setCursor ( 0, 0 );
       lcd.print(" *NO TE MUEVAS*");
       lcd.setCursor ( 0, 1 );        // go to the 2nd line
       lcd.print("*TE LOCALIZAMOS*");
       delay(10000);
       lcd.setBacklight(LOW); // Apagar luz de fondo
       delay(3000); 
       
        
        
       
   }
