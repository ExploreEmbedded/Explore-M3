void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(13,0);
rgbWriteAll(1,1,0);
delay(200);
rgbWriteAll(1,0,1);
delay(200);
rgbWriteAll(0,1,1);
delay(200);
digitalWrite(13,1);
delay(200);
Serial.println("Explore M3");
}
