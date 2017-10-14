//This sketch is from a tutorial video for networking more than two nRF24L01 tranciever modules on the ForceTronics YouTube Channel
//the code was leverage from the following code http://maniacbug.github.io/RF24/starping_8pde-example.html
//This sketch is free to the public to use and modify at your own risk

#include <SPI.h> //Call SPI library so you can communicate with the nRF24L01+
#include <nRF24L01.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/
#include <RF24.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/

const int pinCE = 9; //This pin is used to set the nRF24 to standby (0) or active mode (1)
const int pinCSN = 10; //This pin is used to tell the nRF24 whether the SPI communication is a command or message to send out
RF24 wirelessSPI(pinCE, pinCSN); // Declare object from nRF24 library (Create your wireless SPI) 
const uint64_t rAddress[] = {0xB00B1E50D2LL, 0xB00B1E50C3LL,0xB00B1E50E5LL};  //Create pipe addresses for the 2 nodes to recieve data, the "LL" is for LongLong type
const uint64_t wAddress[] = {0xB00B1E50B1LL, 0xB00B1E50A4LL,0xB00B1E50F6LL};  //Create pipe addresses for the 2 nodes to transmit data, the "LL" is for LongLong type

void setup()   
{
  Serial.begin(57600);  //start serial to communication
  wirelessSPI.begin();  //Start the nRF24 module
  wirelessSPI.openReadingPipe(1,rAddress[0]);      //open pipe o for recieving meassages with pipe address
  wirelessSPI.openReadingPipe(2,rAddress[1]); 
   wirelessSPI.openReadingPipe(3,rAddress[2]);//open pipe o for recieving meassages with pipe address
  wirelessSPI.startListening();                 // Start listening for messages
}

void loop()  
{   
    byte pipeNum = 0; //variable to hold which reading pipe sent data
    byte gotByte = 0; //used to store payload from transmit module
    
    while(wirelessSPI.available(&pipeNum)){ //Check if recieved data
     wirelessSPI.read( &gotByte, 1 ); //read one byte of data and store it in gotByte variable
     Serial.print("Recieved  from transmitter: "); 
     Serial.println(pipeNum); //print which pipe or transmitter this is from
     Serial.print("They sent : ");
     Serial.println(gotByte); //print payload or the number the transmitter guessed
     Serial.println();
    }

  delay(200);    
}
 

