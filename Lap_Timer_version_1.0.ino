// Laptimer version 1.0
// 07.09.18 - inital release

unsigned long start, finished, elapsed;
#include<LiquidCrystal.h>

//Arduino Mega 2560 pin assignments
#define startButton A4
#define stopButton A5
#define contrast 9
#define buzzer 10
#define Start 11
#define Stop 12
#define readyLED 13

int distance = 102; //in feet, down and back flyball course length for calc MPH
float velocity;
float time; //seconds
boolean  recordedTime = false;
float oldTime = 0;
LiquidCrystal lcd (7,6,5,4,3,2); //Arduino Mega 2560 digital pin assignments
int x =0;
 float h, m;
 int s, ms;
 unsigned long over;
 
 //arrays to build custom font segments
byte AA[8] =
{  B11111,  B11111,  B11111,  B11111,  B00000,  B00000,  B00000,  B00000};
byte BB[8] =
{  B00000,  B00000,  B00000,  B00000,  B11111,  B11111,  B11111,  B11111};
byte CC[8] =
{  B00000,  B00000,  B11111,  B11111,  B11111,  B11111,  B00000,  B00000};
byte DD[8] =
{  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B00000,  B00000};
byte EE[8] =
{  B00000,  B00000,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111};
byte FF[8] =
{  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111};
byte GG[8] =
{  B00000,  B00000,  B00000,  B00000,  B00000,  B00000,  B00000,  B00000};
byte dot[8] =
{ B00000,   B00000,  B00000,  B00000,  B00000,  B01110,  B01110,  B01110};

void setup()
{

  
 lcd.begin(20,4);
pinMode(Start, INPUT_PULLUP); // the start trigger
pinMode(Stop, INPUT_PULLUP); // the stop trigger
pinMode(startButton, INPUT_PULLUP);
pinMode(stopButton, INPUT_PULLUP);
pinMode(readyLED, OUTPUT); // Light to say when the stopwatch is ready
//pinMode(buzzer, OUTPUT);

  lcd.createChar(7,AA);
  lcd.createChar(1,BB);
  lcd.createChar(2,CC);
  lcd.createChar(3,DD);
  lcd.createChar(4,EE);
  lcd.createChar(5,FF);
  lcd.createChar(6,GG);
  lcd.createChar(8,dot);
  digitalWrite(readyLED, LOW);
  lcd.setCursor(5,0);  lcd.print("Lap Timer"); //title
  lcd.setCursor(4,1);  lcd.print("version 1.0");
  delay(500); //title delay before ready
  //lcd.clear();
  //analogWrite(buzzer, 0);
  //analogWrite(contrast, 75);
  //lcd.noDisplay();
 lcd.setCursor(0, 3); // set cursor to first row
 lcd.print("READY");
 //lcd.write(1);lcd.write(2);lcd.write(3);lcd.write(4);lcd.write(5);lcd.write(6);lcd.write(7); lcd.write(8);
 //lcd.setCursor(0, 3); lcd.print("12345678"); 
 digitalWrite(readyLED, HIGH);
}

void loop()
{
  
 if  (recordedTime == true) {
  lcd.setCursor(13,0); 
  lcd.print((millis()-start) /1000.0);  //original set to /1000.0
  lcd.setCursor(16,1); 
  //lcd.print((millis()-start) /100);  //display running timmer until stop is pressed.
 }


 
 if (digitalRead(Start) == LOW || digitalRead(startButton) == LOW )   {
     start = millis();
     //lcd.clear();
     digitalWrite(readyLED, LOW);
     lcd.setCursor(0,0);lcd.print("Current Lap         ");
     lcd.setCursor(0,1);lcd.print("----Previous Lap----");
     lcd.setCursor(0,2);lcd.print("                    ");
     velocity = distance /time*0.6818; //convert to MPH
     lcd.setCursor(0,2);lcd.print("Avg spd: "); lcd.print(velocity);lcd.print("MPH"); 
     lcd.setCursor(0,3);lcd.print("Time=      ");
     recordedTime = true;
     beepLow();
     //lcd.setCursor(0,17); lcd.print("s ");
     lcd.display();
     delay(1500); //for debounce to eliminate false triggers
     }


if (digitalRead(Stop) == LOW || digitalRead(stopButton) == LOW )   {
     finished = millis();
     lcd.clear();
     displayResult();
     printBigNumbers();
     beepHigh();
     recordedTime = false; //stop showing running time
     delay(1500); // for debounce to eliminate false triggers
     digitalWrite(readyLED, HIGH);
     //oldTime = 
     }

}


void displayResult()  {

 elapsed = finished - start;
 time = elapsed/1000;
 h = int(elapsed / 3600000);
 over = elapsed % 3600000;
 m = int(over / 60000);
 over = over % 60000;
 s = int(over / 1000);
 ms = over % 1000;
 lcd.setCursor(9,3);
 lcd.print("   ");
 lcd.setCursor(12,3);

 lcd.print(m,0); //0 needed for some reason bc its a float number ???
 lcd.print(":");
 if (s < 10)        //leading zeroes
   {lcd.print('0');}  
 lcd.print(s);
 lcd.print(":");
 if (ms < 100) {lcd.print('0');} //leading zeroes
 if (ms <  10) {lcd.print('0');} //leading zeroes
 lcd.print(ms);
 
 
 
colons();
}

void colons(){
  lcd.setCursor(10,3);   // write the decimal place as big font
  lcd.write(4);
  //lcd.setCursor(8,2);
  //lcd.write(3);
  

}

void beepLow(){
  analogWrite(buzzer, 100); delay(100);
  analogWrite(buzzer, 0);  
}

void beepHigh(){
  analogWrite(buzzer, 100); delay(50);
  analogWrite(buzzer, 0);  delay(50);
  analogWrite(buzzer, 100); delay(50);
  analogWrite(buzzer, 0); 
}

void printBigNumbers() {
//rounding numbers to the tenths
if (ms >= 995 && ms <=999) {s = s ++; ms=0;}
if (ms <  0 && ms <= 4 || ms % 10 <  0 && ms % 10 <= 4 ) {ms = 0;}  
if (ms >= 5 && ms <= 9 || ms % 10 >= 5 && ms % 10 <=9 ) {ms = ms + 10;} 


//racers place
 if (ms >= 0   && ms <= 99 )  {x= 12; custom0();    }
 if (ms >= 100 && ms <= 199)  {x= 12; custom1();    }
 if (ms >= 200 && ms <= 299)  {x= 12; custom2();    }
 if (ms >= 300 && ms <= 399)  {x= 12; custom3();    }
 if (ms >= 400 && ms <= 499)  {x= 12; custom4();    }
 if (ms >= 500 && ms <= 599)  {x= 12; custom5();    }
 if (ms >= 600 && ms <= 699)  {x= 12; custom6();    }
 if (ms >= 700 && ms <= 799)  {x= 12; custom7();    }
 if (ms >= 800 && ms <= 899)  {x= 12; custom8();    }
 if (ms >= 900 && ms <= 999)  {x= 12; custom9();    }
 
 //tenths' place
 if (ms >= 0 && ms <= 90) {x=16; custom0();}
 if (ms >=  0 && ms <=  9 || ms % 100 >=  0 && ms % 100 <=  9  ) {x=16; custom0(); }
 if (ms >= 10 && ms <= 19 || ms % 100 >= 10 && ms % 100 <= 19  ) {x=16; custom1(); }
 if (ms >= 20 && ms <= 29 || ms % 100 >= 20 && ms % 100 <= 29  ) {x=16; custom2(); }
 if (ms >= 30 && ms <= 39 || ms % 100 >= 30 && ms % 100 <= 39  ) {x=16; custom3(); }
 if (ms >= 40 && ms <= 49 || ms % 100 >= 40 && ms % 100 <= 49  ) {x=16; custom4(); }
 if (ms >= 50 && ms <= 59 || ms % 100 >= 50 && ms % 100 <= 59  ) {x=16; custom5(); }
 if (ms >= 60 && ms <= 69 || ms % 100 >= 60 && ms % 100 <= 69  ) {x=16; custom6(); }
 if (ms >= 70 && ms <= 79 || ms % 100 >= 70 && ms % 100 <= 79  ) {x=16; custom7(); }
 if (ms >= 80 && ms <= 89 || ms % 100 >= 80 && ms % 100 <= 89  ) {x=16; custom8(); }
 if (ms >= 90 && ms <= 99 || ms % 100 >= 90 && ms % 100 <= 99  ) {x=16; custom9(); }
 
 //seconds
 //if seconds / 10 and remainder is 0 (0,10,20,30,40,50) print the custom zero in the one's place
  if (s == 0 || s % 10 == 0)  { x=5; huge0();    }
  if (s == 1 || s % 10 == 1)  { x=5; huge1();    }
  if (s == 2 || s % 10 == 2)  { x=5; huge2();    }
  if (s == 3 || s % 10 == 3)  { x=5; huge3();    }
  if (s == 4 || s % 10 == 4)  { x=5; huge4();    }
  if (s == 5 || s % 10 == 5)  { x=5; huge5();    }
  if (s == 6 || s % 10 == 6)  { x=5; huge6();    }
  if (s == 7 || s % 10 == 7)  { x=5; huge7();    }
  if (s == 8 || s % 10 == 8)  { x=5; huge8();    }
  if (s == 9 || s % 10 == 9)  { x=5; huge9();    }
  if (s < 10 )                { x=0; huge0();    }
  if (s >= 10 && s < 20 )     { x=0; huge1();    }
  if (s >= 20 && s < 30 )     { x=0; huge2();    }
  if (s >= 30 && s < 40 )     { x=0; huge3();    }
  if (s >= 40 && s < 50 )     { x=0; huge4();    }
  if (s >= 50 && s < 60 )     { x=0; huge5();    }
}


//section for assembling the large font numbers
void custom0()
{ 
  lcd.setCursor(x, 0); // set cursor to first row
  lcd.write(5);  //call each segment to create
  lcd.write(7);  //top
  lcd.write(5);
  lcd.setCursor(x, 1); // set cursor to second row
  lcd.write(5);  // call each segment to create
  lcd.write(6);  // middle
  lcd.write(5);
  lcd.setCursor(x, 2); //set cursor to place 0, line 2
  lcd.write(5);  // call each segment to create
  lcd.write(1);  // bottom
  lcd.write(5);
}

void custom1(){
  lcd.setCursor(x, 0); lcd.write(7);  lcd.write(5);  lcd.write(6);
  lcd.setCursor(x, 1); lcd.write(6);  lcd.write(5);  lcd.write(6);
  lcd.setCursor(x, 2); lcd.write(1);  lcd.write(5);  lcd.write(1);    }

void custom2(){
  lcd.setCursor(x, 0); lcd.write(7);  lcd.write(7);  lcd.write(5);
  lcd.setCursor(x, 1); lcd.write(4);  lcd.write(2);  lcd.write(3);
  lcd.setCursor(x, 2); lcd.write(5);  lcd.write(1);  lcd.write(1);    }

void custom3(){
  lcd.setCursor(x, 0); lcd.write(7);  lcd.write(7);  lcd.write(5);
  lcd.setCursor(x, 1); lcd.write(2);  lcd.write(2);  lcd.write(5);
  lcd.setCursor(x, 2); lcd.write(1);  lcd.write(1);  lcd.write(5);    }

void custom4(){
  lcd.setCursor(x, 0); lcd.write(5);  lcd.write(6);  lcd.write(5);
  lcd.setCursor(x, 1); lcd.write(3);  lcd.write(2);  lcd.write(5);
  lcd.setCursor(x, 2); lcd.write(6);  lcd.write(6);  lcd.write(5);    }

void custom5(){
  lcd.setCursor(x, 0);  lcd.write(5);  lcd.write(7);  lcd.write(7);
  lcd.setCursor(x, 1);  lcd.write(3);  lcd.write(2);  lcd.write(4);
  lcd.setCursor(x, 2);  lcd.write(1);  lcd.write(1);  lcd.write(5);    }

void custom6(){
  lcd.setCursor(x, 0); lcd.write(5);  lcd.write(6);  lcd.write(6);
  lcd.setCursor(x, 1); lcd.write(5);  lcd.write(2);  lcd.write(4);
  lcd.setCursor(x, 2); lcd.write(5);  lcd.write(1);  lcd.write(5);    }

void custom7(){
  lcd.setCursor(x, 0); lcd.write(7);  lcd.write(7);  lcd.write(5);
  lcd.setCursor(x, 1); lcd.write(6);  lcd.write(6);  lcd.write(5);
  lcd.setCursor(x, 2); lcd.write(6);  lcd.write(6);  lcd.write(5);    }

void custom8(){
  lcd.setCursor(x, 0); lcd.write(5);  lcd.write(7);  lcd.write(5);
  lcd.setCursor(x, 1); lcd.write(5);  lcd.write(2);  lcd.write(5);
  lcd.setCursor(x, 2); lcd.write(5);  lcd.write(1);  lcd.write(5);    }

void custom9(){
  lcd.setCursor(x, 0); lcd.write(5);  lcd.write(7);  lcd.write(5);
  lcd.setCursor(x, 1); lcd.write(3);  lcd.write(2);  lcd.write(5);
  lcd.setCursor(x, 2); lcd.write(6);  lcd.write(6);  lcd.write(5);    }
  
void huge0(){
  lcd.setCursor(x, 0); lcd.write(5);  lcd.write(7);  lcd.write(7);  lcd.write(5);
  lcd.setCursor(x, 1); lcd.write(5);  lcd.write(6);  lcd.write(6);  lcd.write(5);
  lcd.setCursor(x, 2); lcd.write(5);  lcd.write(6);  lcd.write(6);  lcd.write(5);
  lcd.setCursor(x, 3); lcd.write(5);  lcd.write(1);  lcd.write(1);  lcd.write(5); }
  
void huge1(){
  lcd.setCursor(x, 0); lcd.write(6);  lcd.write(1);  lcd.write(5);  lcd.write(6);
  lcd.setCursor(x, 1); lcd.write(6);  lcd.write(6);  lcd.write(5);  lcd.write(6);
  lcd.setCursor(x, 2); lcd.write(6);  lcd.write(6);  lcd.write(5);  lcd.write(6);
  lcd.setCursor(x, 3); lcd.write(6);  lcd.write(1);  lcd.write(5);  lcd.write(1); }
void huge2(){
  lcd.setCursor(x, 0); lcd.write(7);  lcd.write(7);  lcd.write(7);  lcd.write(5);
  lcd.setCursor(x, 1); lcd.write(1);  lcd.write(1);  lcd.write(1);  lcd.write(5);
  lcd.setCursor(x, 2); lcd.write(5);  lcd.write(6);  lcd.write(6);  lcd.write(6);
  lcd.setCursor(x, 3); lcd.write(5);  lcd.write(1);  lcd.write(1);  lcd.write(1); }
  
  void huge3(){
  lcd.setCursor(x, 0); lcd.write(7);  lcd.write(7);  lcd.write(7);  lcd.write(5);
  lcd.setCursor(x, 1); lcd.write(1);  lcd.write(1);  lcd.write(1);  lcd.write(5);
  lcd.setCursor(x, 2); lcd.write(6);  lcd.write(6);  lcd.write(6);  lcd.write(5);
  lcd.setCursor(x, 3); lcd.write(1);  lcd.write(1);  lcd.write(1);  lcd.write(5); }
  
  void huge4(){ //another way to build the numbers
  int row0[4]= {5,6,6,5};  lcd.setCursor(x, 0);for (int i =0; i<4; i++){  lcd.write(row0[i]);}
  int row1[4]= {5,1,1,5};  lcd.setCursor(x, 1);for (int i =0; i<4; i++){  lcd.write(row1[i]);} 
  int row2[4]= {6,6,6,5};  lcd.setCursor(x, 2);for (int i =0; i<4; i++){  lcd.write(row2[i]);} 
  int row3[4]= {6,6,6,5};  lcd.setCursor(x, 3);for (int i =0; i<4; i++){  lcd.write(row3[i]);} }  

  void huge5(){ // yet another way to build the numbers
  int row[16]= {5,7,7,7,5,1,1,1,6,6,6,5,1,1,1,5};
  lcd.setCursor(x, 0);for (int i = 0; i< 4; i++){  lcd.write(row[i]);}
  lcd.setCursor(x, 1);for (int i = 4; i< 8; i++){  lcd.write(row[i]);}
  lcd.setCursor(x, 2);for (int i = 8; i<12; i++){  lcd.write(row[i]);}
  lcd.setCursor(x, 3);for (int i =12; i<16; i++){  lcd.write(row[i]);} }


  void huge6(){
  int row0[4]= {5,6,6,6};  lcd.setCursor(x, 0);for (int i =0; i<4; i++){  lcd.write(row0[i]);}  
  int row1[4]= {5,6,6,6};  lcd.setCursor(x, 1);for (int i =0; i<4; i++){  lcd.write(row1[i]);} 
  int row2[4]= {5,7,7,5};  lcd.setCursor(x, 2);for (int i =0; i<4; i++){  lcd.write(row2[i]);} 
  int row3[4]= {5,1,1,5};  lcd.setCursor(x, 3);for (int i =0; i<4; i++){  lcd.write(row3[i]);} }

  void huge7(){
  int row0[4]= {7,7,7,5};  lcd.setCursor(x, 0);for (int i =0; i<4; i++){  lcd.write(row0[i]);}  
  int row1[4]= {6,6,6,5};  lcd.setCursor(x, 1);for (int i =0; i<4; i++){  lcd.write(row1[i]);} 
  int row2[4]= {6,6,6,5};  lcd.setCursor(x, 2);for (int i =0; i<4; i++){  lcd.write(row2[i]);} 
  int row3[4]= {6,6,6,5};  lcd.setCursor(x, 3);for (int i =0; i<4; i++){  lcd.write(row3[i]);} }

  void huge8(){
  int row0[4]= {5,7,7,5};  lcd.setCursor(x, 0);for (int i =0; i<4; i++){  lcd.write(row0[i]);}  
  int row1[4]= {5,1,1,5};  lcd.setCursor(x, 1);for (int i =0; i<4; i++){  lcd.write(row1[i]);} 
  int row2[4]= {5,6,6,5};  lcd.setCursor(x, 2);for (int i =0; i<4; i++){  lcd.write(row2[i]);} 
  int row3[4]= {5,1,1,5};  lcd.setCursor(x, 3);for (int i =0; i<4; i++){  lcd.write(row3[i]);} }

  void huge9(){
  int row0[4]= {5,7,7,5};  lcd.setCursor(x, 0);for (int i =0; i<4; i++){  lcd.write(row0[i]);}  
  int row1[4]= {5,1,1,5};  lcd.setCursor(x, 1);for (int i =0; i<4; i++){  lcd.write(row1[i]);}
  int row2[4]= {6,6,6,5};  lcd.setCursor(x, 2);for (int i =0; i<4; i++){  lcd.write(row2[i]);} 
  int row3[4]= {6,6,6,5};  lcd.setCursor(x, 3);for (int i =0; i<4; i++){  lcd.write(row3[i]);} }
 

