
#define in1 4
#define in2 5
#define in3 6
#define in4 7

#define im1 8
#define im2 9
#define im3 10
#define im4 11


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

void setup() {
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(in3,OUTPUT);
    pinMode(in4,OUTPUT);

    pinMode(im1,OUTPUT);
    pinMode(im2,OUTPUT);
    pinMode(im3,OUTPUT);
    pinMode(im4,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

}
