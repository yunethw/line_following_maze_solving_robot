//path related functions
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