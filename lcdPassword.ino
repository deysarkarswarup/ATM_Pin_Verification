#include <LiquidCrystal.h> //include LCD library (standard library)
#include <Password.h> 
#include <Keypad.h> 
int attempt=0;
Password password = Password( "1234" );
int i=0;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal lcd (A0, A1, A2, A3, A4, A5); // pins of the LCD. (RS, E, D4, D5, D6, D7)
//LiquidCrystal lcd (0, 1, 2, 3, 4, 5); // pins of the LCD. (RS, E, D4, D5, D6, D7)

void setup()
{
  //analogWrite(10,20);
  lcd.begin(16, 2);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  lcd.setCursor(0, 0);
  lcd.print("Enter ur password:");
}

void loop()
{
  keypad.getKey();
}

//take care of some special events
void keypadEvent(KeypadEvent eKey)
{
  switch (keypad.getState())
  {
    
    case PRESSED:
    lcd.setCursor(i, 1);
    lcd.print("*");
    i++;
    //Serial.print("*");
    switch (eKey)
    {
      //* is to validate password   
      //# is to reset password attempt
      case '*': checkPassword();
        break;
      case '#': password.reset(); 
        break;
      default: password.append(eKey);
    }
  }
}

void checkPassword()
{
  i=0;
  if(attempt<2)
  {
    if (password.evaluate())
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Access granted");
      lcd.setCursor(0, 1);
      lcd.print("U r Welcome!");
    }
    else
    {
        password.reset();
        attempt++;
        int leftAttempt=3-attempt;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Wrong Password");
        lcd.setCursor(0, 1);
        lcd.print(leftAttempt);
        lcd.print(" Attempt left");
        //password.reset();
        delay(5000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter ur password:");
        loop();
    }
  }
    else if(password.evaluate())
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Access granted");
      lcd.setCursor(0, 1);
      lcd.print("U r Welcome!");
    }
  
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("U r a Cheater!"); 
    delay(5000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("wait for 10min"); 
    delay(600000);
    loop();
  }
}
