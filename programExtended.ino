void setup()
{
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
}

const int LOCKED = 1;
const int WAITFORCLICK = 2;
const int CHECKING = 3;
const int UNLOCKED = 4;

int btnOneHandled = 0;
int btnTwoHandled = 0;
int btnThreeHandled = 0;
  
int code[] = {1, 2, 3, 1, 2, 3, 1, 2, 3};
int codeTry[9];
int arraySize = 9;
int arrayStart = 0;
int correct = 0;

unsigned long startTime = 0;
int state = LOCKED;

void loop()
{
  int sensor = digitalRead(13);
  int btnOne = digitalRead(12);
  int btnTwo = digitalRead(8);
  int btnThree = digitalRead(11);
  
  if(btnOne == LOW) {
    btnOneHandled = 0;
  }
  if(btnTwo == LOW) {
    btnTwoHandled = 0;
  }
  if(btnThree == LOW) {
    btnThreeHandled = 0;
  }
  
  switch(state) {
    case LOCKED:
    
      digitalWrite(7, HIGH);
    
      if(sensor == HIGH) {
        digitalWrite(7, LOW);
        startTime = millis();
        arrayStart = 0;
        state = WAITFORCLICK;
      }
      break;
    
    case WAITFORCLICK:
    
      digitalWrite(4, HIGH);
      
      if(arrayStart < arraySize) {
      
        if((btnOne == HIGH) && (!btnOneHandled)) {
           btnOneHandled = 1;
           startTime = millis();
           codeTry[arrayStart] = 1;
           arrayStart = ++arrayStart;
           digitalWrite(4, LOW);
           delay(200);
        }
        else if((btnTwo == HIGH) && (!btnTwoHandled)) {
           btnTwoHandled = 1;
           startTime = millis();
           codeTry[arrayStart] = 2;
           arrayStart = ++arrayStart;
           digitalWrite(4, LOW);
           delay(200);
        }
        
        else if((btnThree == HIGH) && (!btnThreeHandled)) {
           btnThreeHandled = 1;
           startTime = millis();
           codeTry[arrayStart] = 3;
           arrayStart = ++arrayStart;
           digitalWrite(4, LOW);
           delay(200);
        }

        if(millis() - startTime > 5000) {
           digitalWrite(4, LOW);
           state = LOCKED;
        }
      } else {
           digitalWrite(4, LOW);
           state = CHECKING;
        }
    break;
    
    case CHECKING:
      correct = 0;
      for(int i = 0; i < arraySize; i++) {
          if(code[i] == codeTry[i]) {
			correct = ++correct;
            codeTry[i] = (char)0;
          }
      }
      if(correct == arraySize) {
        digitalWrite(2, HIGH);
        state = UNLOCKED;  
      } else {
        digitalWrite(7, HIGH);
        delay(200);
        digitalWrite(7, LOW);
        delay(200);
        digitalWrite(7, HIGH);
        delay(200);
        digitalWrite(7, LOW);
        delay(200);
        digitalWrite(7, HIGH);
        delay(200);
        digitalWrite(7, LOW);
        delay(200);
        state = LOCKED; 
      }
      break;
         
    case UNLOCKED:
       
      delay(5000);
      digitalWrite(2, LOW);
      state = LOCKED;
	  break;
  }
  	
}
