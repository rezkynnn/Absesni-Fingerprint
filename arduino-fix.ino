#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX untuk FPM10A
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
SoftwareSerial nodeSerial(10, 11); // RX, TX untuk NodeMCU

void setup()
{
  Serial.begin(9600);
  nodeSerial.begin(9600);
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Sensor sidik jari siap.");
  } else {
    Serial.println("Gagal menghubungkan sensor sidik jari.");
  }
}

void loop()
{
  getFingerprintID();
  delay(50);
}

uint8_t getFingerprintID()
{
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) return -1;

  Serial.print("ID ditemukan: ");
  Serial.println(finger.fingerID);

  nodeSerial.println(finger.fingerID); // Kirim ID ke NodeMCU
  return finger.fingerID;
}
