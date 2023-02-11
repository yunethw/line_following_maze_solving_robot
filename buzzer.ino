//buzzer tones for different scenarios
void buzz(int type)
{
  switch (type) {
  case 1: //start beep
    tone(BuzzerPin,3000, 100);
    delay(200);
    tone(BuzzerPin,3000, 100);
    delay(200);
    tone(BuzzerPin,3000, 150);
    break;

  case 2: //run beep
    tone(BuzzerPin,3000, 100);
    delay(200);
    tone(BuzzerPin,3000, 100);
    delay(200);
    break;
    
  case 3: //Junction
    for(int c=0;c<3;c++)
    {
      tone(BuzzerPin,3500, 300);
      delay(400);      
    }
    break;
    
  case 4: //Deadend
    tone(BuzzerPin,3000, 1000);
    break;

  case 5: //obstacle detected
    tone(BuzzerPin,3000,1000);
    break;

  case 6: //nopath
    tone(BuzzerPin,3000,200);
    delay(300);
    tone(BuzzerPin,3000,200);
    break;

  case 7: //beep
    tone(BuzzerPin,3000,200);
    break;
  }
}
