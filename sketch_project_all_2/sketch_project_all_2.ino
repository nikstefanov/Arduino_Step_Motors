 /**
Nikolay Stefanov
16 May 2017

*/

// Драйверите на всички мотори са ностроени на 400 стъпки на оборот - в таблиците е Default.

const int r_dir_pin = 7; //Пин DIR+ на десния мотор.
const int r_pul_pin = 4; //Пин PUL+ на десния мотор.

const int l_dir_pin = 6; //Пин DIR+ на левия мотор.
const int l_pul_pin = 3; //Пин PUL+ на левия мотор.

const int c_dir_pin = 5; //Пин DIR+ на централния мотор.
const int c_pul_pin = 2; //Пин PUL+ на централния мотор.

const int button_start_1_pin = 30; //Пин за бутон - програма 1 минута.
const int button_start_4_pin = 32; //Пин за бутон - програма 4 минута.
const int button_start_6_pin = 34; //Пин за бутон - програма 6 минута.
const int button_start_8_pin = 36; //Пин за бутон - програма 8 минута.
const int button_stop_pin = 31;    //Пин за бутон - стоп програма.

const int r_sensor_pin = 44;      //Пин за сензор запълнена ролка на десен мотор. 
const int l_sensor_pin = 42;      //Пин за сензор запълнена ролка на ляв мотор.

const int end_delay = 200;          //Забавяне между стъпките на централния двигател.
                                  //Според тестовете не може да е по-малко от 725 при 400 стъпки на оборот.
const int start_delay = 760;

const int ratio = 400;              //Отношение скорост на въртене на централния мотор към
                                  //скорост на левия и десния мотор. Трбва да е цяло число.
int s_delay = 0;

int b_start_1_state = 0;
int b_start_4_state = 0;
int b_start_6_state = 0;
int b_start_8_state = 0;
int b_stop_state = 0;

int r_sensor_state = 0;
int l_sensor_state = 0;

int s_direction = 0;

unsigned long term_ms = 0;
int seconds = 0;

int mode = 0;
const int start_steps = 450;
const int mode_1_increase_steps = 15;
const int mode_1_decrease_delay = 40;

int mode_1_delay = 0;
int mode_1_steps = 0;

int rounds_per_second = 0;

int i = 0;

void setup() 
{
pinMode(r_dir_pin, OUTPUT);
pinMode(r_pul_pin, OUTPUT);
pinMode(l_dir_pin, OUTPUT);
pinMode(l_pul_pin, OUTPUT);
pinMode(c_dir_pin, OUTPUT);
pinMode(c_pul_pin, OUTPUT);
pinMode(button_start_1_pin, INPUT);
pinMode(button_start_4_pin, INPUT);
pinMode(button_start_6_pin, INPUT);
pinMode(button_start_8_pin, INPUT);
pinMode(button_stop_pin, INPUT);
pinMode(r_sensor_pin, INPUT);
pinMode(l_sensor_pin, INPUT); 

digitalWrite(r_dir_pin, LOW);    // Посока на въртене на десния мотор - обратно на часовниковата стрелка.
digitalWrite(l_dir_pin, HIGH);     // Посока на въртене на левия мотор - по часовниковата стрелка.
digitalWrite(c_dir_pin, LOW);     // Посока на въртене на централния мотор - обратно на часовниковата стрелка.

rounds_per_second = 1000000/(end_delay + 19);
}






void loop()
{
  
  b_stop_state = digitalRead(button_stop_pin);
  if (b_stop_state == HIGH) {seconds=0;mode=0;}

  if (seconds == 0){
      b_start_1_state = digitalRead(button_start_1_pin);
      if (b_start_1_state == HIGH) {seconds=30;}
  
      b_start_4_state = digitalRead(button_start_4_pin);
      if (b_start_4_state == HIGH) {seconds=30;}
  
      b_start_6_state = digitalRead(button_start_6_pin);
      if (b_start_6_state == HIGH) {seconds=30;}
  
      b_start_8_state = digitalRead(button_start_8_pin);
      if (b_start_8_state == HIGH) {seconds=30;}

      if(b_start_1_state == HIGH ||
          b_start_4_state == HIGH ||
          b_start_6_state == HIGH ||
          b_start_8_state == HIGH){
               mode = 1;
               mode_1_steps = start_steps;
               mode_1_delay = start_delay;
          }
  }else{
      if (mode == 1){ //reaching needed rpm        
         for (i = 0; i < mode_1_steps; i++){
             make_step(c_pul_pin, mode_1_delay);     
         }
         if(mode_1_delay > end_delay){
             mode_1_steps += mode_1_increase_steps;
             mode_1_delay -= mode_1_decrease_delay;
         }else{
             mode = 0;  
         }
      }else{
         seconds--;
         for (i = 0; i < rounds_per_second; i++){
             //digitalWrite(c_pul_pin, LOW);
             //digitalWrite(c_pul_pin, HIGH);
             //delayMicroseconds(s_delay);
             make_step(c_pul_pin, end_delay);
             if( i % ratio == 0 ){
                 r_sensor_state = digitalRead(r_sensor_pin);
                 l_sensor_state = digitalRead(l_sensor_pin);
        
                 if(r_sensor_state == HIGH){s_direction = 1;}
                 if(l_sensor_state == HIGH){s_direction = 0;}
        
                 if(s_direction == 0){
                     //digitalWrite(r_pul_pin, LOW);
                     //digitalWrite(r_pul_pin, HIGH);
                     make_step(r_pul_pin, 0);
                 }else{
                     //digitalWrite(l_pul_pin, LOW);
                     //digitalWrite(l_pul_pin, HIGH);
                     make_step(l_pul_pin, 0);
                 }
              }      
         }
      }  
   }
}
void make_step(int pul_pin, int delaystep){
    digitalWrite(pul_pin, LOW);
    digitalWrite(pul_pin, HIGH);
    delayMicroseconds(delaystep);
  
}


