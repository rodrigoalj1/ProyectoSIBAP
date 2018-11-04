
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const int RXPinGSM = 7, TXPinGSM = 8;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial myGsm(RXPinGSM, TXPinGSM);
SoftwareSerial ss(RXPin, TXPin);
double datosGps[5] = {0, 0, 0, 0, 0};

void setup(){
  Serial.begin(9600);
 
  myGsm.begin(GPSBaud);
  ss.begin(GPSBaud);
}

void printSerialData()
{
  while (myGsm.available() != 0)
    Serial.write(myGsm.read());
}

void httpgsm( String latitud,String longitud,String velocidad, String altura, String NumSatelites)
{
  
  myGsm.println("AT+CGATT=1");
  delay(1000);
  printSerialData();

  myGsm.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR,connection type is GPRS
  delay(1000);
  printSerialData();
  //myGsm.println("AT+SAPBR=3,1,\"APN\",\"wap.tmovil.cl\"");//setting the APN,2nd parameter empty works for all networks
  myGsm.println("AT+SAPBR=3,1,\"APN\",\"bam.entelpcs.cl\"");//setting the APN,2nd parameter empty works for all networks
  
  delay(1000);
  printSerialData();

  myGsm.println();
  myGsm.println("AT+SAPBR=1,1");
  delay(5000);
  printSerialData();

  myGsm.println("AT+HTTPINIT"); //init the HTTP request
  delay(1000);
  printSerialData();

  myGsm.println("AT+HTTPPARA=\"URL\",\"http://34.210.139.28/inserta_datos_gps.php?valor1=" + latitud + "&valor2=" + longitud + "&valor3=" + NumSatelites + "&valor4=" + altura + "&valor5=" + velocidad + "\""); // setting the httppara,
  delay(1000);
  printSerialData();

  myGsm.println();
  myGsm.println("AT+HTTPACTION=0");//submit the GET request
  delay(1000);//the delay is important if the return datas are very large, the time required longer.
  printSerialData();
  myGsm.println("AT+HTTPREAD=0,20");// read the data from the website you access
  delay(3000);
  printSerialData();

  myGsm.println("");
  delay(1000);
  myGsm.println("AT+HTTPTERM");// terminate HTTP service
  printSerialData();
}


//void myGps(){ 
//   ss.begin(GPSBaud);
      
// while (ss.available() > 0){
    
 //   gps.encode(ss.read());
 //   if (gps.location.isUpdated()){
 //     datosGps[0]=gps.location.lat(); 
 //     datosGps[1]=gps.location.lng();
 //     datosGps[2]=gps.speed.kmph();
 //     datosGps[3]=gps.altitude.meters();
 //     datosGps[4]=gps.satellites.value();
 //     }
 // }
//}
void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
 //Serial.println(datosGps[4]);
  //myGps ();
 //if (datosGps[4] > 0){
 while (ss.available() > 0){
    
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      datosGps[0]=gps.location.lat(); 
      datosGps[1]=gps.location.lng();
      datosGps[2]=gps.speed.kmph();
      datosGps[3]=gps.altitude.meters();
      datosGps[4]=gps.satellites.value();
      String latitud= String(datosGps[0],6);
String longitud=String(datosGps[1],6);
String velocidad=String(datosGps[2]);
String altura=String(datosGps[3]);
String NumSatelites=String(datosGps[4]);
  httpgsm( latitud, longitud,velocidad,altura,NumSatelites);
      
      }
  }
  Serial.println("***************************************");
  Serial.println(datosGps[0],6);
  Serial.println(datosGps[1],6);
 Serial.println(datosGps[2]);
Serial.println(datosGps[3]);
 Serial.println(datosGps[4]);
 //String latitud= String(datosGps[0],6);
//String longitud=String(datosGps[1],6);
//String velocidad=String(datosGps[2]);
//String altura=String(datosGps[3]);
//String NumSatelites=String(datosGps[4]);
 // httpgsm( latitud, longitud,velocidad,altura,NumSatelites);

 //}
}
