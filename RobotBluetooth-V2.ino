
#include <PS2X_lib.h>

#define in1 4
#define in2 5
#define in3 6
#define in4 7

#define im1 8
#define im2 9
#define im3 10
#define im4 11

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


  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  pinMode(im1,OUTPUT);
  pinMode(im2,OUTPUT);
  pinMode(im3,OUTPUT);
  pinMode(im4,OUTPUT);

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
  // put your main code here, to run repeatedly:

}
