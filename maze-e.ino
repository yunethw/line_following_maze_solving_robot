//Wall-E v3.1
//v1.0 Line following with a lot of bugs
//v2.0 Refined junction decision making. Takes correct turns
//v3.0 Refined code and removed distance measurement to improve performance. Much smoother traveling. 
//v3.1 Added an aditional check to improve junction path detection which was missed due to speed after v3.0

#pragma region Definitions
#define GuideL 8 //Left Guide IR
#define GuideR 11 //Right Guide IR
#define IRR 7 //Far Right IR
#define IRC 6 //Center IR
#define IRL 5 //Far Left IR

#define StartButton 1

//Left Motor
#define MotorL_F A3
#define MotorL_R A2
#define ENA 9 //Enabling and Speed Control
#define LeftSpeed 90
#define LeftSteps 3 //LM393 Optical Sensor

//Right Motor
#define MotorR_R 13
#define MotorR_F 12
#define ENB 10 //Enabling and Speed Control
#define RightSpeed 90
#define RightSteps 2 //LM393 Optical Sensor
#pragma endregion

//step counter
volatile int Lcount = 0;
volatile int Rcount = 0;
int l, c, r, gl, gr; //store sensor readings
int buttonState = 0;
int dist, prevdist;
unsigned long duration;
bool isleft = false;
bool isright = false;
bool isforward = false;
bool check;
const long junction_interval = 1000;
unsigned long previousMillis = 0;

void setup() {
  #pragma region pinModes
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
  #pragma endregion

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

    // if(millis() - previousMillis < junction_interval) //make sure it's not a misalignment
    // {
    //   buzz(7);
    //   align(); 
    //   return;
    // }

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
