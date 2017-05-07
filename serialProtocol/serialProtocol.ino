 int pinA = 2;  // Connected to CLK on KY-040
 int pinB = 3;  // Connected to DT on KY-040
 int encoderPosCount = 0; 
 int pinALast;  
 int aVal;
 boolean bCW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial Configured for 9600");

  pinMode (pinA,INPUT);
  pinMode (pinB,INPUT);
  pinALast = digitalRead(pinA);
}

void loop() {
  char buffer[64];
  int buffer_len = 63;
  //
  // Check for data on serial port.
  // If the data is a command perform the command and respond with OK
  //
  if (Serial.available()) {
    byte bytesRead = Serial.readBytesUntil(10, buffer, buffer_len);
  
    if (bytesRead > 0) {
      buffer[bytesRead] = 0; // Null terminate string
      switch (buffer[0]) {
        case 'r': // Go right
          Serial.println("right");
          break;
        case 'l': // Go left
          Serial.println("left");
          break;
        case 's': // Stop turning
          Serial.println("stop");
          break;
        case 'g': // Set speed
          if (bytesRead > 1) {
            String speedString = String(&buffer[1]);
            int speed = speedString.toInt();
            Serial.println(speed, DEC);
          }
          break;
        case 'a': // Abort/stop
          Serial.println("abort");
          break;
      }
    }
  }

  
  aVal = digitalRead(pinA);
   if (aVal != pinALast){ // Means the knob is rotating
     // if the knob is rotating, we need to determine direction
     // We do that by reading pin B.
     if (digitalRead(pinB) != aVal) {  // Means pin A Changed first - We're Rotating Clockwise
       encoderPosCount ++;
       bCW = true;
     } else {// Otherwise B changed first and we're moving CCW
       bCW = false;
       encoderPosCount--;
     }
     Serial.print ("Rotated: ");
     if (bCW){
       Serial.println ("clockwise");
     }else{
       Serial.println("counterclockwise");
     }
     Serial.print("Encoder Position: ");
     Serial.println(encoderPosCount);
     
   } 
   pinALast = aVal;
}
