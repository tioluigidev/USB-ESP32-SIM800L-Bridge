

#ifndef ESP32
#error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#endif

#define MODEM_RST        5  // Modem reset, active in low
#define MODEM_POWER      23 // Modem module power, active in high
#define MODEM_PWKEY      4  // Modem power key, active in low
#define MODEM_TX         27 // Modem TX
#define MODEM_RX         26 // Modem RX


#define Serial_USB Serial
#define Serial_GSM Serial2

void setup() 
{
 
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER, OUTPUT);
  
  
  digitalWrite(MODEM_RST, HIGH);   // Disable reset signal
  digitalWrite(MODEM_POWER, HIGH); // Power on module
  digitalWrite(MODEM_PWKEY, LOW);  // "Press the ON key" (and forget it pressed on)
  
  Serial_USB.begin(115200);

  Serial_GSM.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);

  Serial_USB.println(F("============================================================"));
  Serial_USB.println(F("You can now send AT commands."));
  Serial_USB.println(F("Enter \"AT\" (without quotes), and you should see \"OK\"."));
  Serial_USB.println(F("If it doesn't work, select \"Both NL & CR\" in Serial Monitor."));
  Serial_USB.println(F("============================================================"));

}

void loop()
{
  if (Serial_GSM.available()) Serial_USB.write(Serial_GSM.read());    
  if (Serial_USB.available()) Serial_GSM.write(Serial_USB.read());
}
