//Maze-E v3.1

//Define pin outputs
#define GuideL 8 //Left Guide IR
#define GuideR 11 //Right Guide IR
#define IRR 7 //Far Right IR
#define IRC 6 //Center IR
#define IRL 5 //Far Left IR
#define StartButton 1
//Left Motor pins
#define MotorL_F A3
#define MotorL_R A2
#define ENA 9 //Enabling and Speed Control
#define LeftSteps 3 //LM393 Optical Sensor
//Right Motor pins
#define MotorR_R 13
#define MotorR_F 12
#define ENB 10 //Enabling and Speed Control
#define RightSteps 2 //LM393 Optical Sensor

//constant values
#define LeftSpeed 90
#define RightSpeed 90

//variables
int l, c, r, gl, gr; //store sensor readings
int buttonState = 0;
bool isleft = false;
bool isright = false;
bool isforward = false;
bool check;

//step counter
volatile int Lcount = 0;
volatile int Rcount = 0;


void setup() {

  pinMode(GuideL, INPUT);
  pinMode(GuideR, INPUT);
  pinMode(IRL, INPUT);
  pinMode(IRR, INPUT);
  pinMode(IRC, INPUT);

  pinMode(MotorL_R, OUTPUT);
  pinMode(MotorL_F, OUTPUT);
  pinMode(MotorR_R, OUTPUT);
  pinMode(MotorR_F, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  pinMode(LeftSteps, INPUT_PULLUP);
  pinMode(RightSteps, INPUT_PULLUP);

  pinMode(StartButton, INPUT_PULLUP);


  analogWrite(ENA, LeftSpeed);
  analogWrite(ENB, RightSpeed);
  digitalWrite(MotorR_F, LOW);
  digitalWrite(MotorL_F, LOW);

  attachInterrupt(digitalPinToInterrupt(LeftSteps), LISR, RISING);
  attachInterrupt(digitalPinToInterrupt(RightSteps), RISR, RISING);

  holdForPush(); //wait for push button press
}

void loop() {
  l = digitalRead(IRL);
  c = digitalRead(IRC);
  r = digitalRead(IRR);
  gl = digitalRead(GuideL);
  gr = digitalRead(GuideR);  
  
  if((l == 0 && r == 0) && (c == 1 || c == 0 && (gl == 1 || gr == 1))) //follow path
  {
    check = true; //a check to make sure  line following procedure was executed
    if(gl == 0 && gr == 0) 
    {
      forward();
    }
    else if(gl == 1 && gr == 0)
    {
      left();
    }
    else if(gr == 1 && gl == 0)
    {
      right();
    }
  }
  else if(c == 0 && ((l == 1 && r == 0)||(r == 1 && l == 0 ))) //minor aligning 
  {
    stopBot();
    align();
  }
  else if((r == 1 || l == 1) && c == 1 && check == true) //junction
  {
    stopBot(); //stop bot when far left or right sensors detect a path

    check = false;

    //check if both left and right are available
    if(digitalRead(IRL) == 1){isleft = true;}
    if(digitalRead(IRR) == 1){isright = true;}

    nudge(1); //nudge a bit forward to make sure both sensors are within range to detect a path
    delay(500);

    //recheck if both left and right are available
    if(digitalRead(IRL) == 1){isleft = true;}
    if(digitalRead(IRR) == 1){isright = true;}

    //v3.1
    if(isleft == false && isright == false)//incase line was missed due to speed
    {
      //use previous readings to determine available path
      if(r == 1){isright == true;}
      if(l == 1){isleft == true;}
    }

    nudge(5); //align wheels with path to prepare for left or right 90 turn
    delay(200);

    //check if a center path is available
    if(digitalRead(IRL) == 1 || digitalRead(GuideL) == 1 || digitalRead(IRC) == 1 || digitalRead(GuideR) == 1 || digitalRead(IRR) == 1)
    {
      align(); //if center is available, use it to align
      isforward = true;
    }
    Rcount = 0;
    Lcount = 0;

    if(isleft) //left priority
    {
      left90(); //turn left by 90
      delay(500);
      if(nopath()) //if no path is detected nudge further
      {
        leftNudge(3);
        delay(300);
        if(nopath())
        {
          leftNudge(3);
          delay(300);
          if(nopath())
          {
            rightNudge(15);
          }
        }
      }
      align(); //align before proceeding
      check = false;
      isleft = false;
      isright = false;
      isforward = false;
      // previousMillis = millis(); //reset junction timer  
      return;
    }
    else if(isforward) 
    {
      check = false;
      isleft = false;
      isright = false;
      isforward = false;
      // previousMillis = millis(); //reset junction timer 
      return;
    }
    else if(isright)
    {
      right90(); //turn right by 90
      delay(500);
      if(nopath()) //if no path is detected nudge further
      {
        rightNudge(3);
        delay(300);
        if(nopath())
        {
          rightNudge(3);
          delay(30);
          if(nopath())
          {
            leftNudge(15);
          }
        }
      }
      align(); //align before proceeding
      check = false;
      isleft = false;
      isright = false;
      isforward = false;
      // previousMillis = millis();
      return;
    }
    else
    {
      //nopath();
    }
  }
  else if(c == 1 && check == false && (r == 1 || l == 1)) //major aligning 
  {
    stopBot();
    if(l == 1)
    {
      onlyRight();
    }
    else if(r == 1)
    {
      onlyLeft();
    }
  }
  else if(c == 0 && gl == 0 && gr == 0 && l == 0 && r == 0) //deadend
  {
    stopBot();
    delay(1000);
    uTurn();
    delay(500);
    if(nopath()) //to make sure line wasn't missed
    {
      leftNudge(5);
    }
    else
    {
      align();
    }
    check = false;  
  }
}

void holdForPush()
{
  while(buttonState == 0)
  {
    if(digitalRead(StartButton) == 0)
    {
      buttonState = 1;
    }
  }
}

bool nopath()
{
  if(digitalRead(IRL) == 0 && digitalRead(GuideL) == 0 && digitalRead(IRC) == 0 && digitalRead(GuideR) == 0 && digitalRead(IRR) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}  
