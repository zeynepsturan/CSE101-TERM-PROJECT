
#include<Wire.h>
#include<pitches.h>
#define BUZZER_PIN 9

int victoryMelody[] = { 262 };  // G5, A5, B5, C6, D6, E6, F6, G6
int durations[] = { 1000 };
char cont;


void playVictoryMelody(int* melody) {
  for (int note = 0; note < sizeof(durations) / sizeof(int); note++) {
    int duration = durations[note];
    if (melody[note] != 0) {
      tone(BUZZER_PIN, melody[note], duration);
    } else {
      noTone(BUZZER_PIN);
    }
    delay(duration * 1.30);
  }
}


void PlaywonMusic(){

int melody[] = {
  659, 784, 880, 880, 0, 
  880, 988, 1047, 1047, 0, 
  1047, 1175, 988, 988, 0, 
  880, 784, 880, 0, 
  
  659, 784, 880, 880, 0, 
  880, 988, 1047, 1047, 0, 
  1047, 1175, 988, 988, 0, 
  880, 784, 880, 0, 
  
  659, 784, 880, 880, 0, 
  880, 1047, 1175, 1175, 0, 
  1175, 1319, 1397, 1397, 0, 
  1319, 1175, 1319, 880, 0, 
  
  880, 988, 1047, 1047, 0, 
  1175, 1319, 880, 0, 
  880, 1047, 988, 988, 0, 
  1047, 880, 988, 0, 
  
  880, 880, 
  // Repeat of the first part
  880, 988, 1047, 1047, 0, 
  1047, 1175, 988, 988, 0, 
  880, 784, 880, 0, 
  
  659, 784, 880, 880, 0, 
  880, 988, 1047, 1047, 0, 
  1047, 1175, 988, 988, 0, 
  880, 784, 880, 0, 
  
  659, 784, 880, 880, 0, 
  880, 1047, 1175, 1175, 0, 
  1175, 1319, 1397, 1397, 0, 
  1319, 1175, 1319, 880, 0, 
  
  880, 988, 1047, 1047, 0, 
  1175, 1319, 880, 0, 
  880, 1047, 988, 988, 0, 
  1047, 880, 988, 0, 
  // End of Repeat
  
  1397, 0, 0, 1479, 0, 0, 
  1397, 1397, 0, 1568, 0, 1479, 1319, 0, 0, 
  1319, 0, 0, 1175, 0, 0, 
  1109, 1175, 0, 1109, 0, 988, 
  
  1397, 0, 0, 1479, 0, 0, 
  1397, 1397, 0, 1568, 0, 1479, 1319, 0, 0, 
  1319, 0, 0, 1175, 0, 0, 
  1109, 1175, 0, 1109, 0, 988
};

int durations[] = {
  8, 8, 4, 8, 8, 
  8, 8, 4, 8, 8, 
  8, 8, 4, 8, 8, 
  8, 8, 4, 8, 
  
  8, 8, 4, 8, 8, 
  8, 8, 4, 8, 8, 
  8, 8, 4, 8, 8, 
  8, 8, 4, 8, 
  
  8, 8, 4, 8, 8, 
  8, 8, 4, 8, 8, 
  8, 8, 4, 8, 8, 
  8, 8, 8, 4, 8, 
  
  8, 8, 4, 8, 8, 
  4, 8, 4, 8, 
  8, 8, 4, 8, 8, 
  8, 8, 4, 4, 
  
  4, 8, 
  // Repeat of First Part
  8, 8, 4, 8, 8, 
  8, 8, 4, 8, 8, 
  8, 8, 4, 8, 
  8, 8, 4, 8, 
  
  8, 8, 4, 8, 8, 
  8, 8, 4, 8, 8, 
  8, 8, 4, 8, 8, 
  8, 8, 4, 8, 
  
  8, 8, 4, 8, 8, 
  8, 8, 4, 8, 8, 
  8, 8, 4, 8, 8, 
  8, 8, 8, 4, 8, 
  
  8, 8, 4, 8, 8, 
  4, 8, 4, 8, 
  8, 8, 4, 8, 8, 
  8, 8, 4, 4, 
  // End of Repeat
  
  4, 8, 4, 4, 8, 4, 
  8, 8, 8, 8, 8, 8, 8, 8, 4, 
  4, 8, 4, 4, 8, 4, 
  8, 8, 8, 8, 8, 2, 
  
  4, 8, 4, 4, 8, 4, 
  8, 8, 8, 8, 8, 8, 8, 8, 4, 
  4, 8, 4, 4, 8, 4, 
  8, 8, 8, 8, 8, 2
};

int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    //stop the tone playing:
    noTone(BUZZER_PIN);
  }


}


void playNokia(){

  int melody[] = {
  NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_GS4, 
  NOTE_CS5, NOTE_B4, NOTE_D4, NOTE_E4, 
  NOTE_B4, NOTE_A4, NOTE_CS4, NOTE_E4,
  NOTE_A4
  };

  int durations[] = {
    8, 8, 4, 4,
    8, 8, 4, 4,
    8, 8, 4, 4,
    2
  };

  
    int size = sizeof(durations) / sizeof(int);

    for (int note = 0; note < size; note++) {
      //to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int duration = 1000 / durations[note];
      tone(BUZZER_PIN, melody[note], duration);

      //to distinguish the notes, set a minimum time between them.
      //the note's duration + 30% seems to work well:
      int pauseBetweenNotes = duration * 1.30;
      delay(pauseBetweenNotes);
      
      //stop the tone playing:
      noTone(BUZZER_PIN);
    }
  
}



void setup() {


  Wire.begin(5);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output




}

void loop() {

  
  if(cont=='1'){

playVictoryMelody(victoryMelody);
delay(2000);  // Wait a moment after the melody is played
cont='4';
}

if(cont=='2'){


PlaywonMusic();
delay(2000);  // Wait a moment after the melody is played

cont='4';

}

if(cont=='3'){


playNokia();
delay(2000);  // Wait a moment after the melody is played

cont='4';

}




}


void receiveEvent(int howMany)
{
      

  while(0 < Wire.available()) // loop through all but the last
  {
   cont = Wire.read(); // receive byte as a character
    Serial.print(cont);         // print the character
  }
  
    }

    

