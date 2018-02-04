#include <Servo.h>
// the pin that the LED is attached to
//String msg;
Servo left_wing_esc;
Servo right_wing_esc;
String inString = "";    // string to hold input


void setup()
{
  // put your setup code here, to run once:
  // initialize the serial communication:
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  left_wing_esc.attach(12);  //Specify here the pin number on which the signal pin of ESC is connected.
  left_wing_esc.write(30);   //ESC arm command. ESCs won't start unless input speed is less during initializati
  delay(3000);            //ESC initialization delay.

  right_wing_esc.attach(10);
  right_wing_esc.write(30);
  delay(3000);


  // Send a signal to PC that I am ready 


}

bool left_wing=false;
bool right_wing=false;

void loop() {

   // Read serial input:
  while (Serial.available() > 0) {
        int inChar = Serial.read();

    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    
    if(inChar == 'L')
    {
      left_wing = true;
      right_wing = false;  
    }
    
    if(inChar == 'R')
    {
      left_wing = false;
      right_wing = true;
    }



    if (inChar == 10) {

      if(left_wing)
      {
        if(inString.toInt()== 0)
         left_wing_esc.write(0);
         else 
         {
          int motor_speed = inString.toInt() + 50 ;
          Serial.print(" Right Motor Speed:");
          Serial.print(motor_speed);
          left_wing_esc.write(motor_speed);    //Vary this between 50-85 to change the speed of motor. Higher value, higher speed. [voltage is 7v & max current 2Amp]
          delay(15);
         }

      }
      if(right_wing)
      {

        if(inString.toInt()== 0)
         right_wing_esc.write(0);
         else 
         {
          int motor_speed = inString.toInt() + 50 ;
          Serial.print("Left Motor Speed:");
          Serial.print(motor_speed);
          right_wing_esc.write(motor_speed);    //Vary this between 50-85 to change the speed of motor. Higher value, higher speed. [voltage is 7v & max current 2Amp]
          delay(15);
         }
        
      }
      
      // clear the string for new input:
      inString = "";
    }
  }

//  // check if data has been sent from the computer:
//  Serial.setTimeout(50);
//  if (Serial.available()) {
//    // read the incoming byte:
//    msg = Serial.readString(); 
//
//    // say what you got:
//    Serial.print("I received: ");
//
//    Serial.println(msg);
//  }
//
//    esc_signal.write(59.7);    //Vary this between 50-85 to change the speed of motor. Higher value, higher speed. [voltage is 7v & max current 2Amp]
//    delay(15);
}
