#include <LiquidCrystal_I2C.h>
#define BLANK_LINE "                " //16 spaces

typedef LiquidCrystal_I2C LC;

void goToLCDLine(LC& lcd, int n); //subsequent output begins at the nth line

LC lcd(0x3f, 16, 2); //a 16x2 display with the hardware address of 0x3f
//if this doesn't work, try changing 0x3f into 0x27

void setup() {
  lcd.begin();
  lcd.backlight();
  goToLCDLine(lcd, 0); //this is actually a no-op here.
  lcd.print("Hello, world!");
}

void loop() {
  goToLCDLine(lcd, 1);
  lcd.print((millis() / 1000) % 15);
}

void goToLCDLine(LC& lcd, int n)
{
  lcd.setCursor(0, n); //set the cursor at the 0th character at the nth line
  lcd.print(BLANK_LINE); //print the blank line; characters on the screen will
  //remain unless overwritten.
  lcd.setCursor(0, n); //put the cursor back in place.
  return;
}
