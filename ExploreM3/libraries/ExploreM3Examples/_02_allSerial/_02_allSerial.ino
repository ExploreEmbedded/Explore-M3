//Example to test all serial ports at once.
//Explore M3 has 4 hardware serial ports and 1 USB serial.
//Serial --refers to USB Serial
//Serial0, Serial1, Serial2 and Serial3 refer to the hardware serial ports. Refer the pinout diagram for more details
//This example prints a string on all the serial ports, you need to connect a USB to serial convertor to check messages on hardware serial ports.

void setup() {
  Serial.begin(9600);// refers to USB Serial, the baud rate actually has no meaning.
  Serial0.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
}

void loop() {
  Serial.println("Message printed on USB Serial");
  Serial0.println("Serial communcation with Serial 0");
  Serial1.println("Serial communcation with Serial 1");
  Serial2.println("Serial communcation with Serial 2");
  Serial3.println("Serial communcation with Serial 3");
}