//all functions related to LCD screen
void lcdStartUp()
{
  lcd.setCursor(3,0);
  lcd.print(">>Wall-E<<");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("Starting Up...");
  buzz(1);
  delay(500);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.write(0);
  lcd.setCursor(5,0);
  lcd.print("Wall-E");
  lcd.setCursor(1,1);
  lcd.print("Push to start!");
}

void lcdBegin()
{
  lcd.clear();
  buzz(2);
  lcd.setCursor(5,0);
  lcd.print("Wall-E");
  delay(500);

  int lc = 2; int rc = 13;
  for(int i = 0; i < 3; i++)
  {
    lcd.setCursor(lc+i,0);
    lcd.print(">");
    lcd.setCursor(rc-i,0);
    lcd.print("<");
    delay(500);
  }

  // lcd.setCursor(0,1);
  // lcd.write(1); lcd.write(2);
  // lcd.setCursor(14,1);
  // lcd.write(1); lcd.write(2);
  lcd.setCursor(3,1);
  lcd.print("PROGRAM: 3");
  delay(1000);
  lcdClearLine(1);
  lcd.setCursor(0,1);
  lcd.print("P3");
  lcd.setCursor(4,1);
  lcd.write(0);
  lcd.setCursor(9,1);
  lcd.print("cm");
  lcd.write(0);
}

void lcdClearLine(int l)
{
  lcd.setCursor(0, l);
  for(int i = 0; i < 16; i++)
  {
    lcd.print(" ");
  }
}

void lcdClear(int line, int col1, int col2)
{
  lcd.setCursor(col1, line);
  for(int i = col1; i < (col2+1); i++)
  {
    lcd.print(" ");
  }
}