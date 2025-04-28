#include <IRremote.h>
#include <LedControl.h>
#include <Wire.h>
#include <EEPROM.h>

#define BUZZER_PIN 9
#define CLK 5 
#define CS 6 
#define DIN 7 
#define MaxDevices 1

#define BUTTON_1 16753245
#define BUTTON_2 16736925
#define BUTTON_3 16769565
#define BUTTON_4 16720605
#define BUTTON_5 16712445

int IR_RECEIVE_PIN = 2;
IRrecv irrecv(IR_RECEIVE_PIN);
decode_results irResults;

int ledRow = 0;
int gameGrid[8][4];  // 2D array representing the game grid.
int gridColumns = 8; 
int gridRows = 4;

int displayOffset = 2;  //Offsets for LED display.
int currentPosition;  //Tracks the current position in the game.

byte crossSymbol[8] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
byte tickSymbol[8] = {0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04};

LedControl ledControl = LedControl(DIN, CLK, CS, MaxDevices);

void setup() {
  Wire.begin();  // I2C communication initialization
  Serial.begin(9600);  // Serial communication initialization
  irrecv.enableIRIn();  // Enable the IR receiver
}

void loop() {
if (Serial.available() > 0) {
    char receivedValue = Serial.read();

    if(receivedValue == 'a'){
      gridColumns = 4;
       startGame();
    }else if (receivedValue == 'b'){ 
      gridColumns = 5;
      startGame();
    }else if (receivedValue == 'c'){ 
      gridColumns = 6;
      startGame();
    }else if (receivedValue == 'd'){ 
      gridColumns = 7;
      startGame();
    }else if (receivedValue == 'e'){ 
      gridColumns = 8;
      startGame();
    }

  }
}

void startGame() {
  int highestScore;
  int attemptCounter = 0;
  char buffer[5];

  highestScore = EEPROM.read(10);  // Retrieves highest score from EEPROM.
  Serial.print(highestScore); 

  ledControl.setIntensity(0, 10);  // Brightness setting
  ledControl.shutdown(0, false);   // Sets up LED matrix brightness and activates it.
  ledControl.clearDisplay(0);     // Clears LED display.

  long randomSeed = analogRead(0);  // Generates a random seed for grid creation.
  srand(randomSeed);
  createGameGrid();  // Calls createGameGrid() to generate the game grid.

  double startTime = millis();
  while (1) {
    if (gameStep() == 1) {  // Calls gameStep() to handle player input and game logic.
      Serial.println("Congratulations! You won");
      displaySymbol(tickSymbol);

      double finishTime = millis();
      double elapsedTime = (finishTime - startTime);  // Calculates and sends score to another device.

      int playerScore = calculateScore((elapsedTime / 1000), attemptCounter);
      itoa(playerScore, buffer, 10);
      Wire.beginTransmission(4);  // Send data to device 4
      Wire.write(buffer);  // Send received value
      Wire.endTransmission();  // Stop sending

      Serial.println(playerScore / 40);
      Serial.println(highestScore);

      if ((playerScore / 40) > highestScore) {  // Updates highest score in EEPROM if necessary.
        highestScore = (playerScore / 40);      
        EEPROM.write(10, highestScore);
        sendSignal('2');
      } else {
        sendSignal('3');
      }

      delay(2000);
      ledControl.clearDisplay(0);
      break;
    } else {
      attemptCounter++;
    }
  }
}

void createGameGrid() //create a grid and random correct path
{
  for (int i = 0; i < gridColumns; i++) {
    int newRandom = rand() % gridRows; // random number for every row

    for (int k = 0; k < gridRows; k++) {
      if (k == newRandom) {
        gameGrid[i][k] = 1; // 1 correct
      } else {
        gameGrid[i][k] = 0; // 3 incorrect
      }
    }
  }

  for (int i = 0; i < gridColumns; i++) { // show the correct path to user for a short period of time
    for (int k = 0; k < gridRows; k++) {
      if (gameGrid[i][k] == 1) // coordinates of correct tiles
      {
        ledControl.setLed(0, k + displayOffset, i, true);
        delay(500);
      }
    }
  }

  delay(3000); // display time
  ledControl.clearDisplay(0); // clear the board
  currentPosition = 0; // setting current row to 0 for start of game
}
int gameStep() //itaration for every game step. each itareation starts with user input(returns 0 if contuning 1 of game is completed)
{
  Serial.println("Please input a value from 1 to 4");
  int input;

  while (1) //taking input from user and storing it in input variable
  {
    if (irrecv.decode(&irResults)) {
      if (irResults.value == BUTTON_1) {
        input = 1;
        irrecv.resume();
        break;
      }
      if (irResults.value == BUTTON_2) {
        input = 2;
        irrecv.resume();
        break;
      }
      if (irResults.value == BUTTON_3) {
        input = 3;
        irrecv.resume();
        break;
      }
      if (irResults.value == BUTTON_4) {
        input = 4;
        irrecv.resume();
        break;
      }
      irrecv.resume();
    }
  }

  input = input - 1; // converting 1-4 user input to 0-3 in order to proccess grid correctly
  // currentposition -> current row ****** input -> selected column
  if (gameGrid[currentPosition][input] == 1) // condition works if user selects correct tile for the current row
  {
    for (int i = 0; i <= currentPosition; i++) //loop for previous tiles and current tile to to display correct answers
    {
      for (int k = 0; k < gridRows; k++) {
        if (gameGrid[i][k] == 1) // coordinate of correct tiles
        {          
          ledControl.setLed(0, k + displayOffset, i, true); // light on for previous correct tiles and current correct tile
        } 
      }
    }
    currentPosition++; // incrementing the current row to precceed to next step
    Serial.print("\nYou hit\n");
  }
  else// condition works if user selects incorrect tile for the current row
  {
    for (int i = 0; i < currentPosition; i++) //loop for previous tiles 
    {
      for (int k = 0; k < gridRows; k++) {
        if (gameGrid[k][i] == 1) //coordinate of correct tiles
         {
          ledControl.setLed(0, i + displayOffset, k, true); // light on for previous correct tiles(not for current one)
        }
      }
    }
    currentPosition = 0; // changing current row to start the game over
    Serial.print("\nYou missed. Start again.\n");
    displaySymbol(crossSymbol); // informing the user that thet failed

    Wire.beginTransmission(5);
    Wire.write('1');
    Wire.endTransmission();

    delay(1500);

    ledControl.clearDisplay(0);// clear the board
  }

  if (currentPosition == gridColumns) // checks if game is completed by comparing current row and desired row
  {
    return 1;
  } else {
    return 0;
  }
}

void displaySymbol(byte character[]) {
  int i = 0;
  for (i = 0; i < 8; i++) {
    ledControl.setRow(0, i, character[i]);
  }
}

int calculateScore(int time, int counter) {
  int score = (6000 - (time * 40) - (counter * 100));
  if (score <= 0) {
    score = 0;
  }
  return score;
}

void sendSignal(char signal) {
  Wire.beginTransmission(5);
  Wire.write(signal);
  Wire.endTransmission();
}




