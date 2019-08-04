#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>


const int time_lapse = 10; //milliseconds

SoftwareSerial DFPlayerSerial(10, 11); // RX, TX

void advertise(int buzzer)
{
  int lapse = 60;
  for(int i = 0; i < 15; i++)
  {
    digitalWrite(buzzer, HIGH);
    delay(lapse);
    digitalWrite(buzzer, LOW);
    delay(lapse);
  }
}

void boom()
{
  mp3_play(1);
  mp3_next();
  delay(4500);
}

int buzzer = 2;
int button = 3;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
  DFPlayerSerial.begin(9600);
  mp3_set_serial(DFPlayerSerial);
  mp3_set_volume(300);

}
int read;
bool explode = false;
void loop() {
  if(! explode)
  {
    read = digitalRead(button);
    if(read == 0)
    {
      digitalWrite(13, HIGH);
      explode = true;
      advertise(buzzer);
      boom();
    }
    digitalWrite(buzzer, LOW);
    digitalWrite(13, LOW);

  }
  delay(time_lapse);

}
