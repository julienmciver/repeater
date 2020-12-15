int sVal, sVal2;
bool redBool[2] = {false, false};
bool greenBool, resetBool = false;
unsigned long tm, prevTm = 0;
long interval = 500;

unsigned long recordingAr[150];
int numRecs = 0;
int arCounter = 0;
bool onBool = false;
bool onSwitch, timeSwitch = false;
unsigned long listenTime;
bool repeatSwitch = false;
bool firstRepeatSwitch, greenSwitch = false;
bool restarting, restartBool = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT_PULLUP);
  pinMode(13,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(3, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 
      
    sVal = !digitalRead(2);
    sVal2 = !digitalRead(3);
    tm = millis();

      if (sVal && !redBool[0]){
        redBool[0] = true;
        redBool[1] = !redBool[1];
        delay(10);
      }
      sVal = !digitalRead(2);
      sVal2 = !digitalRead(3);
      if(!sVal && redBool[0]){
        redBool[0] = false;
        delay(20);
        digitalWrite(11, redBool[1]);
        digitalWrite(10, LOW);
        if (onBool){
          onBool = false;
          repeatSwitch = true;
          arCounter = 0;
        }
        
        Serial.println("\n");
        for (int i = 0; i < 30; i++){
          Serial.println(recordingAr[i]);
        }
        prevTm = tm;
      }
    
      if (repeatSwitch){
        if (!firstRepeatSwitch && ((tm - prevTm) >= 2000)){
          firstRepeatSwitch = true;
          greenSwitch = !greenSwitch;
          prevTm = tm;
          digitalWrite(10,greenSwitch);
        }
    
        if (firstRepeatSwitch && ((tm - prevTm >= recordingAr[arCounter]))){
          greenSwitch = !greenSwitch;
          prevTm = tm;
          arCounter++;
          digitalWrite(10, greenSwitch);
          if (arCounter > numRecs){
            firstRepeatSwitch = false;
            arCounter = 0;
            digitalWrite(10, LOW);
            greenSwitch = false;
          }
        }
         
      }
    
      if (redBool[1]){
        repeatSwitch = false;
        if (sVal2 && !onBool){
          onBool = true;
          onSwitch = sVal2;
          listenTime = millis();
          numRecs = 0;
          arCounter = 0;
          for (int i = 0; i < 30; i++){
            recordingAr[i] = 0;
          }
        }
        
        if (onBool){
          if (onSwitch != sVal2){
            tm = millis();
            recordingAr[arCounter] = tm - listenTime;
            Serial.println(recordingAr[arCounter]);
            listenTime = tm;
            arCounter++;
            numRecs++;
            onSwitch = sVal2;
          }
    
          
        }
        delay(10);
        
      }
    
      if (sVal && sVal2){
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        delay(500);
        digitalWrite(10, HIGH);
        digitalWrite(11, HIGH);
        delay(500);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        delay(500);
        digitalWrite(10, HIGH);
        digitalWrite(11, HIGH);
        delay(500);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        delay(500);
        digitalWrite(10, HIGH);
        digitalWrite(11, HIGH);
        delay(500);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        repeatSwitch = false;
        redBool[0] = 0;
        redBool[1] = 0;
        restartBool = false;
        for (int i = 0; i < 30; i++){
            recordingAr[i] = 0;
          }
        
      }

    

  

  

}
  
  
  

   
  
