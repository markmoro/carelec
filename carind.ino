const int leftIndicatorSwitch = 6;     // the number of the pushbutton pin
const int rightIndicatorSwitch = 5;     // the number of the pushbutton pin
const int hazardIndicatorSwitch = 4;     // the number of the pushbutton pin


const int leftIndicatorLed = 10;     // the number of the pushbutton pin
const int rightIndicatorLed = 3;     // the number of the pushbutton pin
const int topBarLeds[] = {0,1};     // the number of the pushbutton pin

const int barPins[] = {7,8,9};

const int powerSensorPin = 2; 

const int hazPat[4][5] =  {{HIGH,LOW,HIGH,LOW}, 
                         {LOW,HIGH,LOW,LOW,HIGH},
                         {HIGH,LOW,HIGH,LOW},
                         {LOW,HIGH,LOW,HIGH}};

void setup() {
  pinMode(leftIndicatorSwitch, INPUT);  
  pinMode(rightIndicatorSwitch, INPUT);  
  pinMode(hazardIndicatorSwitch, INPUT);  
  pinMode(powerSensorPin, INPUT);  

  pinMode(leftIndicatorLed, OUTPUT);      
  pinMode(rightIndicatorLed, OUTPUT);      
    
  for(int i=0;i<2;i++) {
    pinMode(topBarLeds[i], OUTPUT);      
  }
  for(int i=0;i<3;i++) {
    pinMode(barPins[i], OUTPUT);      
  }
  
}

void setCharge(int amount) {
  for(int i=0;i<3;i++) {
    if(amount>i)
      digitalWrite(barPins[i], HIGH);     
     else 
      digitalWrite(barPins[i], LOW);     
  }
  
}  
  
void indicators() {
  int leftIndicatorSwitchState = digitalRead(leftIndicatorSwitch);
  int rightIndicatorSwitchState = digitalRead(rightIndicatorSwitch);
  int hazardIndicatorSwitchState = digitalRead(hazardIndicatorSwitch);
  
    if (hazardIndicatorSwitchState == LOW) {     

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
    if (leftIndicatorSwitchState == HIGH) {     
      // turn LED on:    
      digitalWrite(leftIndicatorLed, HIGH);  
    }
    
    if (rightIndicatorSwitchState == HIGH) {     
      // turn LED on:    
      digitalWrite(rightIndicatorLed, HIGH);  
    } 
    }
}  

void hazard(int i) {
    int hazardIndicatorSwitchState = digitalRead(hazardIndicatorSwitch);

     if (hazardIndicatorSwitchState == HIGH) {     

    digitalWrite(topBarLeds[0], hazPat[i][0]);  
    digitalWrite(topBarLeds[1], hazPat[i][1]);  
    digitalWrite(leftIndicatorLed, hazPat[i][3]);  
    digitalWrite(rightIndicatorLed, hazPat[i][4]);  
     } else {
           digitalWrite(topBarLeds[0], LOW);  
    digitalWrite(topBarLeds[1], LOW);  

     }

}


void batteryMonitor() {
    int sensorValue = analogRead(powerSensorPin); 
  if(sensorValue >820 )
    setCharge(3);   
  else if(sensorValue >740 )
    setCharge(2);  
  else if(sensorValue >680 )
    setCharge(1);  
  else 
    setCharge(0); 
}
  
void loop(){
  // read the state of the pushbutton value:
  indicators();
  batteryMonitor();
  hazard(0); 
  delay(250);  
  hazard(1);
  delay(250);  
  hazard(2);
// wait for a second
  digitalWrite(leftIndicatorLed, LOW);  
  digitalWrite(rightIndicatorLed, LOW);  
  delay(250);  
  hazard(3);
  delay(250);  

}


