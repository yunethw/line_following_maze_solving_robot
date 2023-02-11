//all functions related to robot movement
void forward()
{
  digitalWrite(MotorL_R, LOW);
  digitalWrite(MotorR_R, LOW);
  digitalWrite(MotorL_F, HIGH);
  digitalWrite(MotorR_F, HIGH);
}

void left()
{
  digitalWrite(MotorL_R, LOW);
  digitalWrite(MotorR_R, LOW);
  digitalWrite(MotorL_F, LOW);  
  digitalWrite(MotorR_F, HIGH);
}

void right()
{
  digitalWrite(MotorL_R, LOW);
  digitalWrite(MotorR_R, LOW);
  digitalWrite(MotorR_F, LOW);  
  digitalWrite(MotorL_F, HIGH);
}

void stopBot()
{
  digitalWrite(MotorL_F, LOW);
  digitalWrite(MotorR_F, LOW);
  digitalWrite(MotorL_R, LOW);
  digitalWrite(MotorR_R, LOW);
  Rcount = 0;
  Lcount = 0;
}

void left90()
{
  Rcount = 0;
  Lcount = 0;
  while((Lcount/2) <= 6 && (Rcount/2) <= 6 && digitalRead(IRL) == 0)
  {
    digitalWrite(MotorR_F, HIGH);
    digitalWrite(MotorL_R, HIGH);
  }
  digitalWrite(MotorR_F, LOW);
  digitalWrite(MotorL_R, LOW);
  Rcount = 0;
  Lcount = 0;
}

void right90()
{
  Rcount = 0;
  Lcount = 0;
  while((Lcount/2) <= 6 && (Rcount/2) <= 6 && digitalRead(IRR) == 0)
  {
    digitalWrite(MotorR_R, HIGH);
    digitalWrite(MotorL_F, HIGH);
  }
  digitalWrite(MotorR_R, LOW);
  digitalWrite(MotorL_F, LOW);
  Rcount = 0;
  Lcount = 0;
}

void uTurn() 
{
  while (digitalRead(IRR) == 0) {
    digitalWrite(MotorL_F, HIGH);
    digitalWrite(MotorR_R, HIGH);
  }
  digitalWrite(MotorL_F, LOW);
  digitalWrite(MotorR_R, LOW);
  Lcount = 0;
  Rcount = 0;
}

void nudge(int steps) //move forward a bit by spefied amount of steps
{
  Rcount = 0;
  Lcount = 0;
  while ((Rcount / 2) <= steps && (Lcount / 2) <= steps) {
    digitalWrite(MotorR_F, HIGH);
    digitalWrite(MotorL_F, HIGH);
  }
  digitalWrite(MotorR_F, LOW);
  digitalWrite(MotorL_F, LOW);
  Rcount = 0;
  Lcount = 0;
}

void leftNudge(int steps) //turn left a bit by spefied amount of steps
{
  Rcount = 0;
  Lcount = 0;
  while ((Rcount / 2) <= steps && (Lcount / 2) <= steps) {
    digitalWrite(MotorR_F, HIGH);
    digitalWrite(MotorL_R, HIGH);
  }
  digitalWrite(MotorR_F, LOW);
  digitalWrite(MotorL_R, LOW);
  Rcount = 0;
  Lcount = 0;
}

void rightNudge(int steps) //turn right a bit by spefied amount of steps
{
  Rcount = 0;
  Lcount = 0;
  while ((Rcount / 2) <= steps && (Lcount / 2) <= steps) {
    digitalWrite(MotorR_R, HIGH);
    digitalWrite(MotorL_F, HIGH);
  }
  digitalWrite(MotorR_R, LOW);
  digitalWrite(MotorL_F, LOW);
  Rcount = 0;
  Lcount = 0;
}

void align() //align robot with any line
{
  int count = 0;

  while(count <= 6 && (digitalRead(IRL) == 1 || digitalRead(IRR) == 1))
  {
    while(digitalRead(GuideL) == 1 || digitalRead(IRL) == 1)
    {
      leftNudge(1);
      count++;
      delay(200);
    }
  
    while(digitalRead(GuideR) == 1 || digitalRead(IRR) == 1)
    {
      rightNudge(1);
      count++;
      delay(200);
    }
    delay(500);
  }
  Rcount = 0;
  Lcount = 0;
}

void onlyRight() //rotate only right wheel for alignment
{
  while(digitalRead(GuideR) == 0)
  {
    digitalWrite(MotorR_F, HIGH);
  }
  digitalWrite(MotorR_F, LOW);
  Rcount = 0;
  Lcount = 0;
}

void onlyLeft() //rotate only left wheel for alignment
{
  while(digitalRead(GuideL) == 0)
  {
    digitalWrite(MotorL_F, HIGH);
  }
  digitalWrite(MotorL_F, LOW);
  Rcount = 0;
  Lcount = 0;
}