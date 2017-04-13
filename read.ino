/*
 * Read X/Y delta displacements from Optical Mouse sensor (compatible with ADNS2610)
 */
int led = 13;
int sck = 3;
int sdio = 2;
 
void mwrite(int reg, int data)
{
  int io;
  int i;
  pinMode(sdio, OUTPUT);
  pinMode(sck, OUTPUT);
  for (i =0; i < 8; i++)
  {
    if (reg & 0x80)
      io = HIGH;
    else
      io = LOW;
    reg <<= 1;
    digitalWrite(sck, LOW);
    digitalWrite(sdio, io);
    //delayMicroseconds(10);
    del();
    digitalWrite(sck, HIGH);
    //delayMicroseconds(10);
    del();
  }
  digitalWrite(sdio, HIGH);
  //delayMicroseconds(20);
  pinMode(sdio, INPUT);
  delayMicroseconds(150);
  for (i =0; i < 8; i++)
  {
    digitalWrite(sck, LOW);
    //delayMicroseconds(1);
    if (data & 0x80)
      io = HIGH;
    else
      io = LOW;
    data <<= 1;
    digitalWrite(sdio, io);
    del();
    digitalWrite(sck, HIGH);
    //delayMicroseconds(1);
    del();
    data <<= 1;
    data += io;
  }
  pinMode(sck, OUTPUT);
  digitalWrite(sck, HIGH);
}
 
void setup() {
  pinMode(led, OUTPUT);
  pinMode(sck, OUTPUT);
  digitalWrite(sck, HIGH);
  pinMode(sdio, OUTPUT);
  digitalWrite(sdio, HIGH);
  Serial.begin(9600);
 
  pinMode(sck, OUTPUT);
  digitalWrite(sck, HIGH);
  pinMode(sdio, OUTPUT);
  digitalWrite(sdio, HIGH);
 
  delay(1000);
  int reg = 0x80;
  int data = 0x01;
 
  mwrite(reg,data);
  delay(1000);
}
 
void del()
{
  delayMicroseconds(10);
}
 
int x = 0;
void loop() {
  pinMode(sck, OUTPUT);
  digitalWrite(sck, HIGH);
  pinMode(sdio, OUTPUT);
  digitalWrite(sdio, HIGH);
 
  digitalWrite(led, HIGH); 
  delay(500);            
  digitalWrite(led, LOW);   
  delay(500);
  int reg = 0x11;
  int reg = 0x03;
  int reg = 0x08;
  int data = 0;
  int io;
  int i;
  pinMode(sdio, OUTPUT);
  pinMode(sck, OUTPUT);
  for (i =0; i < 8; i++)
  {
    if (reg & 0x80)
      io = HIGH;
    else
      io = LOW;
    reg <<= 1;
    digitalWrite(sck, LOW);
    digitalWrite(sdio, io);
    //delayMicroseconds(10);
    del();
    digitalWrite(sck, HIGH);
    //delayMicroseconds(10);
    del();
  }
  digitalWrite(sdio, HIGH);
  //delayMicroseconds(20);
  pinMode(sdio, INPUT);
  delayMicroseconds(150);
  for (i =0; i < 8; i++)
  {
    digitalWrite(sck, LOW);
    //delayMicroseconds(1);
    del();
    digitalWrite(sck, HIGH);
    io = digitalRead(sdio);
    //delayMicroseconds(1);
    del();
    data <<= 1;
    data += io;
  }
  pinMode(sck, OUTPUT);
  digitalWrite(sck, HIGH);
  delay(100);
  Serial.print("x=");
  Serial.println( data);
#if 0
  if (data & 0x80)
  {
    Serial.print( "S");
    x = 0;
  }
  else
    Serial.print( " ");
  if (data & 0x40)
  {
    //Serial.print( " ");
    //else
    //Serial.print( "*");
    data &= 0x3F;
    Serial.print(data,16);
    //Serial.print(data>>4);
    Serial.print( ",");
    //Serial.print(data&0xf);
    x++;
    if (x >= 18)
    {
      Serial.println();
      x = 0;
    }
  }
#endif
 
  reg = 0x02; 
  data = 0;
  pinMode(sdio, OUTPUT);
  pinMode(sck, OUTPUT);
  for (i =0; i < 8; i++)
  {
    if (reg & 0x80)
      io = HIGH;
    else
      io = LOW;
    reg <<= 1;
    digitalWrite(sck, LOW);
    digitalWrite(sdio, io);
    //delayMicroseconds(10);
    del();
    digitalWrite(sck, HIGH);
    //delayMicroseconds(10);
    del();
  }
  digitalWrite(sdio, HIGH);
  //delayMicroseconds(20);
  pinMode(sdio, INPUT);
  delayMicroseconds(150);
  for (i =0; i < 8; i++)
  {
    digitalWrite(sck, LOW);
    //delayMicroseconds(1);
    del();
    digitalWrite(sck, HIGH);
    io = digitalRead(sdio);
    //delayMicroseconds(1);
    del();
    data <<= 1;
    data += io;
  }
  pinMode(sck, OUTPUT);
  digitalWrite(sck, HIGH);
  delay(100);
  Serial.print("y=");
  Serial.println(data);
}
