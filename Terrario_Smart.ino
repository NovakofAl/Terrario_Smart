#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 8       // Define the pin used to connect the dht sensor
#define DHTTYPE DHT11  // Define the sensor type

#define HEATPIN 10    // Define the pin used to control the Heatpad 
#define WATERPIN 11   // Define the pin used to control the Atomizer

#define MAXTEMP 29    // Define the max value of temperature that we can have inside the terrarium
#define MINTEMP 25    // Define the min value of temperature that we can have inside the terrarium
#define HUMIDITY 60   // Define the correct percentuage of humidity that we need inside the terrarium

#define SPECIES "Correlophus Ciliatus" //Define the Species contained in the terrarium
#define SPECIMENS 1 //Define the number of Specimens

String names[SPECIMENS] = {"Skelly"}; //A Strings array that contains the names of all the Specimens

DHT dht(DHTPIN, DHTTYPE);  // Create a DHT object

LiquidCrystal lcd(7,6,5,4,3,2);

const int inputPin = A0;
const int ledPin = 9;

uint16_t inputValue = 0;

unsigned long timeT = 0;
unsigned long deltaT = 30000;
float t; //temperature
float h; //humidity

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  pinMode(HEATPIN, OUTPUT);
  pinMode(WATERPIN, OUTPUT);
  lcd.begin(16, 2);         // set up the LCD's number of columns and rows
  lcd.print("Device ON");   // Print a message on the LCD  
  dht.begin();
}

void loop() {
  //check if the last temperature check was more than 30 second away
  if(millis() > timeT + deltaT){
    t = dht.readTemperature();
    h = dht.readHumidity();

    if(t <= MINTEMP){
      digitalWrite(HEATPIN, HIGH); 
    }
    if(t >= MAXTEMP){
      digitalWrite(HEATPIN, LOW);
    }

    if(h <= HUMIDITY){
      digitalWrite(WATERPIN, HIGH);
    }else{
      digitalWrite(WATERPIN, LOW);
    }

    timeT = millis();
  }
  
  // check buttons status
  inputValue = analogRead(inputPin);

  if(inputValue < 100 && inputValue >= 0) inputValue = 1;
    else if(inputValue < 250 && inputValue > 150) inputValue = 2;
    else if(inputValue < 470 && inputValue > 370) inputValue = 3;
    else if(inputValue < 670 && inputValue > 570) inputValue = 4;
    else if(inputValue < 870 && inputValue > 770) inputValue = 5;
    else if(inputValue <= 1023 && inputValue > 950) inputValue = 0;
    
  //show the temperature
  if(inputValue == 1){
    temp();
  }
  //show the status of heatpad and atomizer
  if(inputValue == 2){
    status();
  }
  //show the species and the number of specimen
  if(inputValue == 3){
    info();
  }
}

void temp(){
  
  t = dht.readTemperature();
  h = dht.readHumidity();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223);
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(h);
  lcd.print((char)37);
  delay(2000);
}

void status(){
  
  lcd.setCursor(0, 0);
  lcd.print("HeatPad: ");
  
  if(digitalRead(HEATPIN) == HIGH){
    lcd.print("ON");
  }else{
    lcd.print("OFF");
  }
  
  lcd.setCursor(0, 1);
  
  lcd.print("Atomizer: ");
  if(digitalRead(WATERPIN) == HIGH){
    lcd.print("ON");
  }else{
    lcd.print("OFF");
  }
  
}

void info(){
  lcd.setCursor(0, 0);

  for(int i = 0; i< SPECIMENS; i++){
    lcd.print(names[i]);
    delay(500);
    if(i+1 != SPECIMENS){
      lcd.print(", ");
    }
  }

  lcd.setCursor(0, 1); 
  lcd.print(SPECIES); 
}
