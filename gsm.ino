#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10); // pin 9 as Rx and pin10 as Tx

void setup()

{

  mySerial.begin(9600);   // Setting the baud rate of GSM Module 

  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)

  delay(100);

}

void loop()  // the program seeks input from serial monitor of arduino

{

  if (Serial.available()>0)  //check if data is coming through serial port if no data available then the return value is -1

   switch(Serial.read())   //read all the data available on serial buffer and return the first byte of the data

  {

    case 's':

      SendMessage();

      break;

    case 'd':

      DialCall();

      break;

  }

 if (mySerial.available()>0)  //check if any data from gsm module through pin 9 and 10 and returns the number of bytes available to read

   Serial.write(mySerial.read());     // print the data collected through software serial port to serial monitor

}

 void SendMessage()           // to send an sms 


{

  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+919784012422\"\r"); // Replace x with mobile number

  delay(1000);

  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send

  delay(100);

  mySerial.println((char)26);// ASCII code of CTRL+Z

  delay(1000);

}

 void RecieveMessage() //receive a live sms

{

  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS

  delay(1000);

}



  void DialCall()

 {

  mySerial.println("ATD+917737886232;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!

  delay(100);

 }




 
