void setup()
{
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
}

const int LOCKED = 1;
const int WAITFORCLICKONE = 2;
const int WAITFORCLICKTWO = 3;
const int CHECKING = 4;
const int UNLOCKED = 5;

int btnOneHandled = 0;
int btnTwoHandled = 0;
  
int code[] = {1, 1};
int codeTry[2];

int state = LOCKED;

void loop()
{
  int sensor = digitalRead(13);
  int btnOne = digitalRead(12);
  int btnTwo = digitalRead(8);
  
  if(btnOne == LOW) {
    btnOneHandled = 0;
  }
  if(btnTwo == LOW) {
    btnTwoHandled = 0;
  }
  
  switch(state) {
    case LOCKED:
    
      digitalWrite(7, HIGH);
    
      if(sensor == HIGH) {
        digitalWrite(7, LOW);
        state = WAITFORCLICKONE;
      }
      break;
    
    case WAITFORCLICKONE:
    
      digitalWrite(4, HIGH);
    
      if((btnOne == HIGH) && (!btnOneHandled)) {
         btnOneHandled = 1;
         codeTry[0] = 1;
         digitalWrite(4, LOW);
         delay(200);
         state = WAITFORCLICKTWO;
      }
      if((btnTwo == HIGH) && (!btnTwoHandled)) {
         btnTwoHandled = 1;
         codeTry[0] = 2;
         digitalWrite(4, LOW);
         delay(200);
         state = WAITFORCLICKTWO;
      }
      break;
    
    case WAITFORCLICKTWO:
         
      digitalWrite(4, HIGH);
    
      if((btnOne == HIGH) && (!btnOneHandled)) {
         btnOneHandled = 1;
         codeTry[1] = 1;
         digitalWrite(4, LOW);
         delay(200);
         digitalWrite(4, HIGH);
         delay(200);
         digitalWrite(4, LOW);
         state = CHECKING;
      }
      if((btnTwo == HIGH) && (!btnTwoHandled)) {
         btnTwoHandled = 1;
         codeTry[1] = 2;
         digitalWrite(4, LOW);
         delay(200);
         digitalWrite(4, HIGH);
         delay(200);
         digitalWrite(4, LOW);
         state = CHECKING;
      }
      break;
    
    case CHECKING:
    
      if((code[0] == codeTry[0]) && (code[1] == codeTry[1])) {
         digitalWrite(2, HIGH);
         state = UNLOCKED;  
      } else {
         digitalWrite(7, HIGH);
         delay(200);
         digitalWrite(7, LOW);
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
