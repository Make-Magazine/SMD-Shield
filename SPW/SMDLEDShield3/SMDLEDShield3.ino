
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
int frames = 6;
int i = 0;
int waitCount = 0;
int waitCycles = 85;

byte columns[] = {
  0b01111111, 0b10111111, 0b11011111, 0b11101111,
  0b11110111, 0b11111011, 0b11111101, 0b11111110
};

byte sequence[][8] = {
{255,129,129,129,129,129,129,255} , 
{0,126,66,66,66,66,126,0} , 
{0,0,60,36,36,60,0,0} , 
{0,0,0,24,24,0,0,0} , 
{0,0,60,36,36,60,0,0} , 
{0,126,66,66,66,66,126,0} 
};

void setup() {
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
}

void loop() {
  if (i == frames) {
    i = 0;
  }
  while (waitCount < waitCycles) {
    waitCount++;
    for (int j =0; j < 8; j++) {
      digitalWrite(latchPin, 0);
      shiftOut(dataPin, clockPin, 0); 
      shiftOut(dataPin, clockPin, 255);
      digitalWrite(latchPin, 1);
      digitalWrite(latchPin, 0);
      shiftOut(dataPin, clockPin, sequence[i][j]); 
      shiftOut(dataPin, clockPin, columns[j]);
      digitalWrite(latchPin, 1);
    }
  }
  i++;
}

void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);
  for (int k=7; k>=0; k--)  {
    digitalWrite(myClockPin, 0);
    if (myDataOut & (1 << k)) {
      digitalWrite(myDataPin, 1);
    } else {	
      digitalWrite(myDataPin, 0);
    }
    digitalWrite(myClockPin, 1);
    digitalWrite(myDataPin, 0);
  }
  digitalWrite(myClockPin, 0);
}
