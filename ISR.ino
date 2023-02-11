//Interrupt Service Routines to measure wheel rotation
void LISR()
{
  if(digitalRead(3) > 0)
  {
    Lcount++;
  }
}

void RISR()
{
  if(digitalRead(2) > 0)
  {
    Rcount++;
  }
}