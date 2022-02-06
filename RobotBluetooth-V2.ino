
#include <Servo.h>
#include <PS2X_lib.h>

String input = "";

#define in1 4
#define in2 5
#define in3 6
#define in4 7


#define im1 8
#define im2 9
#define im3 10
#define im4 11

#define bel 30

#define PS2_DAT    17
#define PS2_CMD    15
#define PS2_SEL    16
#define PS2_CLK    14
#define pressures   false
#define rumble      true
PS2X ps2x;

int psError = 0;
byte psType = 0;
byte vibrate = 0;

Servo servo1;
int pos = 0;


void stopAll(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);

  digitalWrite(im1,LOW);
  digitalWrite(im2,LOW);

  digitalWrite(im3,LOW);
  digitalWrite(im4,LOW);

  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void kanan(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);

  digitalWrite(im1,HIGH);
  digitalWrite(im2,LOW);

  digitalWrite(im3,LOW);
  digitalWrite(im4,HIGH);

  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void kiri(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);

  digitalWrite(im1,LOW);
  digitalWrite(im2,HIGH);

  digitalWrite(im3,HIGH);
  digitalWrite(im4,LOW);

  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

//semua motor mundur
void mundur(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);

  digitalWrite(im1,HIGH);
  digitalWrite(im2,LOW);


  digitalWrite(im3,LOW);
  digitalWrite(im4,HIGH);

  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}


//Semua motor maju
void maju(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);

  digitalWrite(im1,LOW);
  digitalWrite(im2,HIGH);

  digitalWrite(im3,HIGH);
  digitalWrite(im4,LOW);

  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void serv(){
  Serial.println("serrrrrr");
  servo1.write(0);
  pos = 0;
  for (pos = 0; pos <= 180; pos += 2) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      servo1.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 2) { // goes from 180 degrees to 0 degrees
      servo1.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
  }
}

void handleBluetooth(){
  if (Serial1.available() > 0) {
      char x = Serial1.read();
      Serial.print(x);
      if(x == 'F'){
          maju();
          delay(80);
      }
      if(x == 'R'){
          kanan();
          delay(80);
      }
      if(x == 'L'){
          kiri();
          delay(80);
      }
      if(x == 'B'){
          mundur();
          delay(80);
      }
      if(x == 'S'){
          stopAll();
      }
      if(x == 'H'){
          serv();
      }
      digitalWrite(LED_BUILTIN, HIGH);
  }else {
      digitalWrite(LED_BUILTIN, LOW);
      stopAll();
  }
}

void handleStickPs(){
  ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed

  // || ps2x.Analog(PSS_LY) == 0
  if(ps2x.Button(PSB_PAD_UP)) {
      Serial.print("PSB_PAD_UP");
      maju();
      delay(80);
  }
  // || ps2x.Analog(PSS_LX) == 255
  if(ps2x.Button(PSB_PAD_RIGHT)) {
      Serial.print("PSB_PAD_RIGHT");
      kanan();
      delay(80);
  }
  // || ps2x.Analog(PSS_LX) == 0
  if(ps2x.Button(PSB_PAD_LEFT)) {
      Serial.print("PSB_PAD_LEFT");
      kiri();
      delay(80);
  }
  // || ps2x.Analog(PSS_LY) == 255
  if(ps2x.Button(PSB_PAD_DOWN)) {
      Serial.print("PSB_PAD_DOWN ");
      mundur();
      delay(80);
  }

  if(ps2x.ButtonReleased(PSB_PAD_UP)
      || ps2x.ButtonReleased(PSB_PAD_RIGHT)
      || ps2x.ButtonReleased(PSB_PAD_LEFT)
      || ps2x.ButtonReleased(PSB_PAD_DOWN) ){
      Serial.print("stopAll");
      stopAll();
  }

  delay(50);
}

void setup() {
  
  Serial1.begin(115200);
  Serial.begin(115200);
  servo1.attach(3);
  serv();
  delay(300);
  psError = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if(psError == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
        Serial.println("true ");
    else
        Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
        Serial.println("true)");
    else
        Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }
  else if(psError == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if(psError == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(psError == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");


  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  pinMode(im1,OUTPUT);
  pinMode(im2,OUTPUT);
  pinMode(im3,OUTPUT);
  pinMode(im4,OUTPUT);

  pinMode(bel,OUTPUT);
  pinMode(28,OUTPUT);
  digitalWrite(bel,LOW);
  digitalWrite(bel,HIGH);

  psType = ps2x.readType();
  switch(psType) {
      case 0:
      Serial.print("Unknown Controller type found ");
      break;
      case 1:
      Serial.print("DualShock Controller found ");
      break;
      case 2:
      Serial.print("GuitarHero Controller found ");
      break;
      case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
  }

  Serial.println("Setup Finish");
}

void loop() {
  handleStickPs();

}
