#include <SoftwareSerial.h>
#include <TinyGPS.h>
TinyGPS gps;
SoftwareSerial myGsm(7,8);
SoftwareSerial serialgps(4,3);

unsigned long chars;
unsigned short sentences, failed_checksum;
float latitude, longitude;

void setup()
{
      Serial.begin(9600);
      //serialgps.begin(9600);
      myGsm.begin(9600);
      delay(500);
}

void loop()
{
    //String la="-29.90572",lo="-71.26649";
    //httpgsm(la,lo);
    sequenciaGPS();
    delay(1000);
}

void printSerialData()
{
    while(myGsm.available()!=0)
    Serial.write(myGsm.read());
}

void httpgsm(String longitud, String latitud)
{
  
      myGsm.println("AT+CGATT=1");
      delay(1000);
      printSerialData();

      myGsm.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR,connection type is GPRS
      delay(1000);
      printSerialData();
      myGsm.println("AT+SAPBR=3,1,\"APN\",\"wap.tmovil.cl\"");//setting the APN,2nd parameter empty works for all networks
      delay(5000);
      printSerialData();

      myGsm.println();
      myGsm.println("AT+SAPBR=1,1");
      delay(10000);
      printSerialData();
      
      myGsm.println("AT+HTTPINIT"); //init the HTTP request
      delay(2000);
      printSerialData();

      myGsm.println("AT+HTTPPARA=\"URL\",\"http://34.210.139.28/inserta_datos.php?valor1="+longitud+"&valor2="+latitud+"\"");// setting the httppara,
      delay(1000);
      printSerialData();
      
      myGsm.println();
      myGsm.println("AT+HTTPACTION=0");//submit the GET request
      delay(8000);//the delay is important if the return datas are very large, the time required longer.
      printSerialData();
      myGsm.println("AT+HTTPREAD=0,20");// read the data from the website you access
      delay(3000);
      printSerialData();

      myGsm.println("");
      delay(1000);
      myGsm.println("AT+HTTPTERM");// terminate HTTP service
      printSerialData();
}

void sequenciaGPS()
{   Serial.println("sequenciaGPS");
    int c = serialgps.read();
    if (gps.encode(c))
    { Serial.print("entro al if");
      gps.f_get_position(&latitude, &longitude);
      Serial.print("Lat/Long: ");
      Serial.print(latitude, 5);
      Serial.print(", ");
      Serial.println(longitude, 5);
      //httpgsm(String((longitude, 5),DEC),String((latitude, 5),DEC));
      gps.stats(&chars, &sentences, &failed_checksum);
    }
}
