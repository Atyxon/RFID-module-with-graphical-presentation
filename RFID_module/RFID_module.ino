#include <SPI.h>  // include library for SPI communication protocol
#include <MFRC522.h>  // include library for RFID module

const int resetPin = 9; // Declaration of constant variable for reset pin
const int ssPin = 10; // Declaration of constant variable for slave select pin
const int ledGreenPin = 2; // Declaration of constant variable for green LED pin
const int ledRedPin = 4; // Declaration of constant variable for red LED pin
String acceptableCards[] = {"E3 E9 72 1E", "E2 34 26 19"};  // Declaration of string array containing UID to be accepted by RFID reader

MFRC522 mfrc522(ssPin, resetPin);  // Create MFRC522 instance

void setup() {
  // Set mode for LED pins
  pinMode(ledGreenPin, OUTPUT); 
  pinMode(ledRedPin, OUTPUT);

	Serial.begin(9600); // Initialize serial communication
	while (!Serial);  // Do nothing if no serial port is opened
	SPI.begin();  // Begin SPI communication with peripheral device
	mfrc522.PCD_Init(); // Init RFID module
	delay(10);  // Delay to finish initialization
	Serial.println("Program started");  // Print in serial monitor to show that program started
}

void loop() {
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
    // Returns true if a PICC responds to PICC_CMD_REQA.
    // PICC_CMD_REQA is REQuest command, type A which invites PICC in state IDLE to be ready for read
		return;
	}

	if ( ! mfrc522.PICC_ReadCardSerial()) {
    // Returns true if a UID could be read.
		return;
	}

  String content= ""; // Empty UID string
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));  // Check if UID byte is lesser than 0x10 in HEX to prevent bad UID read, add " 0" to content string if true or " " if false
    content.concat(String(mfrc522.uid.uidByte[i], HEX)); // Add HEX value of UID to content string 
  }
  content.toUpperCase(); 
  if (content.substring(1) != NULL) // Check substring(1) to skip first char in content string which is space
  {
    bool cardAuthorized = false;  // Auxiliary variable
    for(String UID : acceptableCards) // Check if UID is acceptable
    {
      if(content.substring(1) == UID) // Check substring(1) to skip first char in content string which is space
      {
        cardAuthorized = true;
        validCard();
        break;
      }
    }
    if(!cardAuthorized)
      invalidCard();
  }
  delay(100);
}

void validCard()
{
  // If PICC UID is accepted, print "Authorized access" in serial monitor and light green LED for 1s
  Serial.println("Authorized access");
  digitalWrite(ledGreenPin, HIGH);
  delay(1000);
  digitalWrite(ledGreenPin, LOW);
  delay(1000);
}

void invalidCard()
{
  // If PICC UID is not accepted, print "Access denied" in serial monitor and light red LED for 1s
  Serial.println("Access denied");
  digitalWrite(ledRedPin, HIGH);
  delay(1000);
  digitalWrite(ledRedPin, LOW);
  delay(1000);
}

