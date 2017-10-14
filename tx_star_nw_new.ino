//This sketch is from a tutorial video for networking more than two nRF24L01 tranciever modules on the ForceTronics YouTube Channel
//the code was leverage from the following code http://maniacbug.github.io/RF24/starping_8pde-example.html
//This sketch is free to the public to use and modify at your own risk

#include <SPI.h> //Call SPI library so you can communicate with the nRF24L01+
#include <nRF24L01.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/
#include <RF24.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/

const int pinCE = 9; //This pin is used to set the nRF24 to standby (0) or active mode (1)
const int pinCSN = 10; //This pin is used to tell the nRF24 whether the SPI communication is a command or message to send out
byte counter = 1; //used to count the packets sent
bool done = false; //used to know when to stop sending packets
RF24 wirelessSPI(pinCE, pinCSN); // Create your nRF24 object or wireless SPI connection
const uint64_t wAddress = 0xB00B1E50C3LL;              // Pipe to write or transmit on
const uint64_t rAddress = 0xB00B1E50A4LL;  //pipe to recive data on

void setup()  
{
  Serial.begin(57600);   //start serial to communicate process
  wirelessSPI.begin();            //Start the nRF24 module
  wirelessSPI.setPALevel(RF24_PA_MAX);
  wirelessSPI.openWritingPipe(wAddress);        //open writing or transmit pipe
  wirelessSPI.openReadingPipe(1,rAddress);  //open reading or recieve pipe
  unsigned long time = millis();
}


void loop()  
{
  unsigned long time;
  if(millis() - time > 2000)
  { byte value = digitalRead(8);
  
   while(!done) { //true once you guess the right number
    
    if (!wirelessSPI.write( &value, 1 )){  //if the write fails let the user know over serial monitor
         Serial.println("delivery failed");      
     }
     else { //if the write was successful 
          Serial.print("Success : ");
          Serial.println(value);
            done = true; //signal to loop that we are done guessing
          }
      delay(1000);
   }
    done=false;
    time = millis();
}
}

