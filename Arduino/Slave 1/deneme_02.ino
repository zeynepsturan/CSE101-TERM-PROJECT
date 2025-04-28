#include <Wire.h>
#include <EEPROM.h>

int biggest_point;
int number2;
int PinA=3;
int PinB=7;
int PinC=10;
int PinD=12;
int PinE=13;
int PinF=4;
int PinG=9;
int Segment1=2;
int Segment2=5;
int Segment3=6;
int Segment4=8;
int Sayi;
int Binler=0;
int Yuzler=0;
int Onlar=0;
int Birler=0;
int Bekleme=5;

void setup()
{

 

  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PinA, OUTPUT);
  pinMode(PinB, OUTPUT);
  pinMode(PinC, OUTPUT);
  pinMode(PinD, OUTPUT);
  pinMode(PinE, OUTPUT);
  pinMode(PinF, OUTPUT);
  pinMode(PinG, OUTPUT);
  pinMode(Segment1, OUTPUT);
  pinMode(Segment2, OUTPUT);
  pinMode(Segment3, OUTPUT);
  pinMode(Segment4, OUTPUT);
 
  
}

void loop()
{

biggest_point=EEPROM.read(10);



if((number2/40)>biggest_point){

biggest_point=(number2/40);

EEPROM.write(10,biggest_point);
print_number2(number2);

number2=0;

}


 else if(number2>0){

print_number(number2);

    number2=0;

 }   
}

  

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
      
int i=0; char c[4];

  while(0 < Wire.available()) // loop through all but the last
  {
   c[i] = Wire.read(); // receive byte as a character
    Serial.print(c[i]);         // print the character
    i++;
  }
  String str(c);
  int number = str.toInt();
  Serial.print(number);
  number2=number;
  
    }





void print_number(int number){

  digitalWrite(Segment1, HIGH);
  digitalWrite(Segment2, HIGH);
  digitalWrite(Segment3, HIGH);
  digitalWrite(Segment4, HIGH);

  if(number>10)
  {
    Birler=number%10;
    Onlar=(number/10)%10;
    Yuzler=(number/100)%10;
    Binler=number/1000;
    
    for(int i=0;i<1000;i++){

      digitalWrite(Segment4, LOW);
      Rakam(Birler);
      delay(Bekleme);
      digitalWrite(Segment4, HIGH);
      
      digitalWrite(Segment3, LOW);
      Rakam(Onlar);
      delay(Bekleme);
      digitalWrite(Segment3, HIGH);

      digitalWrite(Segment2, LOW);
      Rakam(Yuzler);
      delay(Bekleme);
      digitalWrite(Segment2, HIGH);

      digitalWrite(Segment1, LOW);
      Rakam(Binler);
      delay(Bekleme);
      digitalWrite(Segment1, HIGH);

    }
  }
}

void print_number2(int number){

  digitalWrite(Segment1, HIGH);
  digitalWrite(Segment2, HIGH);
  digitalWrite(Segment3, HIGH);
  digitalWrite(Segment4, HIGH);

  if(number>10)
  {
    Birler=number%10;
    Onlar=(number/10)%10;
    Yuzler=(number/100)%10;
    Binler=number/1000;
    
    for(int i=0;i<1000;i++){

      digitalWrite(Segment4, LOW);
      Rakam(Birler);
      delay(Bekleme);
      digitalWrite(Segment4, HIGH);
      
      digitalWrite(Segment3, LOW);
      Rakam(Onlar);
      delay(Bekleme);
      digitalWrite(Segment3, HIGH);

      digitalWrite(Segment2, LOW);
      Rakam(Yuzler);
      delay(Bekleme);
      digitalWrite(Segment2, HIGH);

      digitalWrite(Segment1, LOW);
      Rakam(Binler);
      delay(Bekleme);
      digitalWrite(Segment1, HIGH);


      if(i%20==0){

    digitalWrite(Segment1, HIGH);
     delay(200);



      }

    }
  }
}









void Rakam(int x)
  {
    switch(x) 
    {
      case 1: Bir(); break;
      case 2: Iki(); break;
      case 3: Uc(); break;
      case 4: Dort(); break;
      case 5: Bes(); break;
      case 6: Alti(); break;
      case 7: Yedi(); break;
      case 8: Sekiz(); break;
      case 9: Dokuz(); break;
      default: Sifir(); break;
    }
  }

 



void Bir()
{
  digitalWrite(PinA,  LOW);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, LOW);
  digitalWrite(PinE, LOW);
  digitalWrite(PinF, LOW);
  digitalWrite(PinG, LOW);
}

void Iki()
{
  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, LOW);
  digitalWrite(PinD, HIGH);
  digitalWrite(PinE, HIGH);
  digitalWrite(PinF, LOW);
  digitalWrite(PinG, HIGH);
}

void Uc()
{
  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, HIGH);
  digitalWrite(PinE, LOW);
  digitalWrite(PinF, LOW);
  digitalWrite(PinG, HIGH);
}

void Dort()
{
  digitalWrite(PinA, LOW);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, LOW);
  digitalWrite(PinE, LOW);
  digitalWrite(PinF, HIGH);
  digitalWrite(PinG, HIGH);
}

void Bes()
{
  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, LOW);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, HIGH);
  digitalWrite(PinE, LOW);
  digitalWrite(PinF, HIGH);
  digitalWrite(PinG, HIGH);
}

void Alti()
{
  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, HIGH);
  digitalWrite(PinE, HIGH);
  digitalWrite(PinF, HIGH);
  digitalWrite(PinG, LOW);
}

void Yedi()
{
  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, LOW);
  digitalWrite(PinE, LOW);
  digitalWrite(PinF, LOW);
  digitalWrite(PinG, LOW);
}

void Sekiz()
{
  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, HIGH);
  digitalWrite(PinE, HIGH);
  digitalWrite(PinF, HIGH);
  digitalWrite(PinG, HIGH);
}

void Dokuz()
{
  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, HIGH);
  digitalWrite(PinE, LOW);
  digitalWrite(PinF, HIGH);
  digitalWrite(PinG, HIGH);
}

void Sifir()
{
  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, HIGH);
  digitalWrite(PinE, HIGH);
  digitalWrite(PinF, HIGH);
  digitalWrite(PinG, LOW);
}



