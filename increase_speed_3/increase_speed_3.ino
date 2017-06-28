/**
Nikolay Stefanov
26 May 2017

*/

// Драйверите на всички мотори са ностроени на 400 стъпки на оборот - в таблиците е Default.
const int steps_per_round = 400;

const int r_dir_pin = 7; //Пин DIR+ на десния мотор.
const int r_pul_pin = 4; //Пин PUL+ на десния мотор.

const int l_dir_pin = 6; //Пин DIR+ на левия мотор.
const int l_pul_pin = 3; //Пин PUL+ на левия мотор.

const int c_dir_pin = 5; //Пин DIR+ на централния мотор.
const int c_pul_pin = 2; //Пин PUL+ на централния мотор.

const int chislitel = 10;
const int znamenatel = 13;

int s_delay = 0;
int i_steps = 0;
int end_delay = 0;

const int start_rpm = 150;
const int end_rpm = 400;


void setup() 
{
pinMode(r_dir_pin, OUTPUT);
pinMode(r_pul_pin, OUTPUT);
pinMode(l_dir_pin, OUTPUT);
pinMode(l_pul_pin, OUTPUT);
pinMode(c_dir_pin, OUTPUT);
pinMode(c_pul_pin, OUTPUT);

digitalWrite(r_dir_pin, HIGH);    // Посока на въртене на десния мотор - обратно на часовниковата стрелка.
digitalWrite(l_dir_pin, LOW);     // Посока на въртене на левия мотор - по часовниковата стрелка.
digitalWrite(c_dir_pin, LOW);     // Посока на въртене на централния мотор - обратно на часовниковата стрелка.

s_delay = (int)(1000000.0 * 60.0 / (start_rpm * steps_per_round));
i_steps = start_rpm * steps_per_round / 60;
end_delay = (int)(1000000.0 * 60.0 / (end_rpm * steps_per_round));

}



void loop()
{
  for (int i = 0; i < i_steps; i++){
    digitalWrite(c_pul_pin, LOW);
    digitalWrite(c_pul_pin, HIGH);
    delayMicroseconds(s_delay);
  }
  if(s_delay > end_delay){
    s_delay = (s_delay * chislitel) / znamenatel;
    i_steps = (i_steps * znamenatel) / chislitel;
  }
  
}

