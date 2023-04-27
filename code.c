// RemoteXY select connection mode and include library  
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h> 

// RemoteXY connection settings  
#define REMOTEXY_SERIAL Serial 
#define REMOTEXY_SERIAL_SPEED 115200 
#define REMOTEXY_WIFI_SSID "Basket" 
#define REMOTEXY_WIFI_PASSWORD "12345678" 
#define REMOTEXY_SERVER_PORT 6377 


// RemoteXY configurate   
#pragma pack(push, 1) 
uint8_t RemoteXY_CONF[] = 
  { 255,0,0,64,0,74,0,8,13,0,
  67,4,3,29,20,5,2,26,16,67,
  4,26,29,20,5,2,26,16,67,4,
  54,29,20,5,2,26,16,67,4,76,
  29,20,5,2,26,16,129,0,2,20,
  95,7,17,65,100,100,101,100,32,68,
  101,108,101,116,101,100,32,32,66,105,
  108,108,32,32,32,67,111,117,110,116,
  0 }; 
   
// this structure defines all the variables of your control interface  
struct { 

    // output variable
  char text_1[16];  // string UTF8 end zero 
  char text_2[16];  // string UTF8 end zero 
  char text_3[16];  // string UTF8 end zero 
  char text_4[16];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY; 
#pragma pack(pop) 

///////////////////////////////////////////// 
//           END RemoteXY include          // 
///////////////////////////////////////////// 



#include <SPI.h>
/* Include the RFID library */
#include <RFID.h>
// include the library code:
/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 10
#define RESET_DIO 9
/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO); 
char card[20];
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //rs en d4d5d6d7
int bill=0;
int addi = 0;
int deli = 0;
int count=0;
int t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0;
String r;


void setup() 
{
 RemoteXY_Init (); 
   /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
  lcd.begin(16, 2);
    lcd.setCursor(0,0);
  lcd.print("Smart Basket");
   lcd.setCursor(0,1);
  lcd.print(" ");
  delay(3000);
  lcd.clear();
 
 
   lcd.setCursor(0,0);
  lcd.print("A:");
    lcd.setCursor(8,0);
  lcd.print("D:");
    lcd.setCursor(0,1);
  lcd.print("T:");
   lcd.setCursor(3,1);
  lcd.print(count);
   lcd.setCursor(8,1);
  lcd.print("B:");
  lcd.setCursor(11,1);
  lcd.print(bill);
pinMode(A0, OUTPUT);
pinMode(A1, OUTPUT);
digitalWrite(A0, LOW);
digitalWrite(A1, LOW);
  // TODO you setup code
  
}

void loop() 
{ 
 RemoteXY_Handler ();
  
lcd.setCursor(3,1);
  lcd.print(count);
  lcd.print("  ");
   itoa (count, RemoteXY.text_4, 10);
if (RC522.isCard())
  {
RC522.readCardSerial();
    Serial.println("Card detected:");
    for(int i=0;i<1;i++)
    {
   
     card[i] = RC522.serNum[i];
    Serial.println(card[i],DEC);
//Serial.println(r);
if(card[i] == -80 && t1 == 0)
{
  count++;
 card[i] = 0;
  lcd.setCursor(2,0);
  lcd.print("Mgg");
    t1 = 1;
    bill = bill+60;
  //  Serial.println("Product 1 added");
  strcpy  (RemoteXY.text_1, "Maggi "); 
  digitalWrite(A0, HIGH);
    lcd.setCursor(11,1);
    lcd.print(bill);
     lcd.print("    ");
      itoa (bill, RemoteXY.text_3, 10);
      delay(2000);
      digitalWrite(A0, LOW);
}
if(card[i] == -80 && t1 == 1)
{
  card[i] = 0;
  count--;
    t1 = 0;
    bill = bill-60;
      lcd.setCursor(10,0);
  lcd.print("Mgg");
   // Serial.println("Product 1 Deleted");
   strcpy  (RemoteXY.text_2, "Maggi "); 
  digitalWrite(A1, HIGH);
    lcd.setCursor(11,1);
    lcd.print(bill);
    lcd.print("    ");
     itoa (bill, RemoteXY.text_3, 10);
     delay(2000);
     digitalWrite(A1, LOW);
}
if(card[i] == -16 && t2 == 0)
{
 card[i] = 0;
  lcd.setCursor(2,0);
  lcd.print("Pen");
  count++;
    t2 = 1;
    bill = bill+69;
  //  Serial.println("Product 2 added");
   strcpy  (RemoteXY.text_1, "Pen    "); 
  digitalWrite(A0, HIGH);
    lcd.setCursor(11,1);
    lcd.print(bill);
     lcd.print("    ");
      itoa (bill, RemoteXY.text_3, 10);
      delay(2000);
      digitalWrite(A0, LOW);
}
if(card[i] == -16 && t2 == 1)
{
 card[i] = 0;
  count--;
    t2 = 0;
    bill = bill-69;
     lcd.setCursor(10,0);
  lcd.print("Pen");
    //Serial.println("Product 2 Deleted");
    strcpy  (RemoteXY.text_2, "Pen    ");
  digitalWrite(A1, HIGH);
    lcd.setCursor(11,1);
    lcd.print(bill);
    lcd.print("    ");
     itoa (bill, RemoteXY.text_3, 10);
     delay(2000);
     digitalWrite(A1, LOW);
}

if(card[i] == -125 && t3 == 0)
{
  
  card[i] = 0;
  count++;
  lcd.setCursor(2,0);
  lcd.print("Mun");
    t3 = 1;
    bill = bill+10;
   // Serial.println("Product 3 added");
    strcpy  (RemoteXY.text_1, "Munch "); 
   digitalWrite(A0, HIGH);
    lcd.setCursor(11,1);
    lcd.print(bill);
     lcd.print("    ");
      itoa (bill, RemoteXY.text_3, 10);
      delay(2000);
      digitalWrite(A0, LOW);
}
if(card[i] == -125 && t3 == 1)
{
  card[i] = 0;
  count--;
    t3 = 0;
    bill = bill-10;
    lcd.setCursor(10,0);
  lcd.print("Mun");
   // Serial.println("Product 3 Deleted");
   strcpy  (RemoteXY.text_2, "Munch "); 
  digitalWrite(A1, HIGH);
    lcd.setCursor(11,1);
    lcd.print(bill);
    lcd.print("    ");
     itoa (bill, RemoteXY.text_3, 10);
     delay(2000);
     digitalWrite(A1, LOW);
}
if(card[i] == -93 && t4 == 0)
{
  
  card[i] = 0;
  count++;
  lcd.setCursor(2,0);
  lcd.print("Tea");
    t4 = 1;
    bill = bill+40;
   // Serial.println("Product 3 added");
    strcpy  (RemoteXY.text_1, "Tea "); 
   digitalWrite(A0, HIGH);
    lcd.setCursor(11,1);
    lcd.print(bill);
     lcd.print("    ");
      itoa (bill, RemoteXY.text_3, 10);
      delay(2000);
      digitalWrite(A0, LOW);
}
if(card[i] == -93 && t4 == 1)
{
  card[i] = 0;
  count--;
    t4 = 0;
    bill = bill-40;
    lcd.setCursor(10,0);
  lcd.print("Tea");
   // Serial.println("Product 3 Deleted");
   strcpy  (RemoteXY.text_2, "Tea "); 
  digitalWrite(A1, HIGH);
    lcd.setCursor(11,1);
    lcd.print(bill);
    lcd.print("    ");
     itoa (bill, RemoteXY.text_3, 10);
     delay(2000);
     digitalWrite(A1, LOW);
}

    }
  }
  
  
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer


}