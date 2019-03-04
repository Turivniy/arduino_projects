/******************************************************************************

                            Looks like it works
                          mail: turivniy@gmail.com

*******************************************************************************/

int ButPin = 7;                    // Подключаем кнопку к контакту D7
int value = 0;
int value1 = 0;
int pos = 0;
int flag = 0;                      // флаг состояния
int regim = 0;                     // Переключалка
int analogValue = 0;

int state = LOW;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers



const int analogPin = A0;        // аналоговый вывод для потенциометра
const int thresholdVerh = 775;   // произвольный порог для показаний потенциометра
const int thresholdNiz = 59;     // произвольный порог для показаний потенциометра

// ====Подключаем мотор ====//
int dir1PinB = 3;                  // Контакт D3
int dir2PinB = 4;                  // Контакт D4   
int speedPinB = 6;                 // Контакт D6
int EN = 2;                        // Контакт D2

void setup()
{
  Serial.begin(9600);

  analogWrite(speedPinB, 120);            
  pinMode(ButPin, INPUT_PULLUP);                              
         
  //==== Подключаем контакты мотора ====// 
  pinMode(dir1PinB, OUTPUT); 
  pinMode(dir2PinB, OUTPUT);
  pinMode(speedPinB, OUTPUT);
  pinMode(EN, OUTPUT); 
  digitalWrite(EN, HIGH);

   //==== Подключаем контакты  датчиков ====//
  pinMode(analogPin, INPUT);
 }


void loop()
{   
  analogValue = analogRead(analogPin);
  /*
  Serial.print("ANALOG POTENTIOMETER: ");
  Serial.print(analogValue);
  Serial.print("\n"); 

  

  Serial.print("STATE: ");
  Serial.print(state);
  Serial.print("\n");
  */

  reading = digitalRead(ButPin);
  
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;
    time = millis();    
    }

  digitalWrite (dir1PinB, LOW);
  digitalWrite (dir2PinB, LOW);
  
  if ((analogValue >= thresholdVerh) && (state == LOW)){
      Serial.print("UP motor");

      while (analogValue >= thresholdNiz){
        Serial.print("UP POTENTIOMETER: ");
        Serial.print(analogValue);
        Serial.print("\n");
        
        digitalWrite (dir1PinB, HIGH);
        digitalWrite (dir2PinB, LOW);
        analogValue = analogRead(analogPin);
        }
    }
  
  if((analogValue <= thresholdNiz) && (state == HIGH)){
      Serial.print("DOWN motor");


      while (analogValue <= thresholdVerh){
        Serial.print("DOWN POTENTIOMETER: ");
        Serial.print(analogValue);
        Serial.print("\n");
        
        digitalWrite (dir1PinB, LOW);
        digitalWrite (dir2PinB, HIGH);
        analogValue = analogRead(analogPin);
      }
    }
    
  if((analogValue > thresholdNiz) && (analogValue < thresholdVerh)){
      Serial.print("MIDDLE DOWN motor");

      while (analogValue >= thresholdNiz){
        Serial.print("MIDDLE UP POTENTIOMETER: ");
        Serial.print(analogValue);
        Serial.print("\n");
        
        digitalWrite (dir1PinB, HIGH);
        digitalWrite (dir2PinB, LOW);
        analogValue = analogRead(analogPin);
      }
    }

  previous = reading;
}
