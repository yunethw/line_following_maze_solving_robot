//Ultrasonic sensor codes
float distance()
{
  prevdist = dist;
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);

  dist = duration / 2 * 0.03478;

  if(dist < 10 && prevdist >= 10)
  {
    lcdClear(1, 6, 7);
  }
  else if(dist < 100 && prevdist >= 100)
  {
    lcdClear(1, 7, 7);
  }

  lcd.setCursor(5,1);
  if(dist <= 400)
  {
    lcd.print(dist);
  }
  else
  {
    lcd.print("MAX");
  }
  
  return dist;
}