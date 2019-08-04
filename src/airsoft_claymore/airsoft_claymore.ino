#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>

SoftwareSerial DFPlayerSerial(10, 11); // RX, TX

void readCountdown(int manualbt, int okbt, int &cd)
{
  int read_ok, read_manual_current, read_manual_prev;
  int count = 0;
  read_manual_prev = 1;
  read_ok = digitalRead(okbt);
  while(read_ok == 1)
  {
    read_manual_current = digitalRead(manualbt);
    Serial.println(read_manual_current);
    read_ok = digitalRead(okbt);
    if(read_manual_current == 0 && read_manual_prev == 1)
    {
      count+=10;
    }
    read_manual_prev = read_manual_current;
  }
  Serial.println("HE salido del bucle");
  cd = count;
}

void advertise(int buzzer)
{
  int lapse = 1000;
  digitalWrite(buzzer, HIGH);
  delay(lapse);
  digitalWrite(buzzer, LOW);
}

void boom()
{
  mp3_play(1);
  mp3_next();
  delay(4500);
}

const int TimeLapse = 10; //milliseconds
const int Buzzer = 2;
const int ButtonManualControl = 3;
const int ButtonOk = 5;

void setup() {
  Serial.begin(9600);
  
  pinMode(Buzzer, OUTPUT);
  pinMode(ButtonManualControl, INPUT);
  pinMode(ButtonOk, INPUT);
  
  DFPlayerSerial.begin(9600);
  mp3_set_serial(DFPlayerSerial);
  mp3_set_volume(300);

}

int read_manual;
bool explode = false;
void loop() {
  
  if(! explode)
  {
    read_manual = digitalRead(ButtonManualControl);
    if(read_manual == 0)
    {
      advertise(Buzzer);
      digitalWrite(13, HIGH);
      int countdown;
      readCountdown(ButtonManualControl, ButtonOk, countdown);
      Serial.println(countdown);
      delay(countdown * 1000);
      Serial.println("Explota la bomba");
      boom();
      explode = true;
    }
    digitalWrite(13, LOW);

  }
  delay(TimeLapse);

}
