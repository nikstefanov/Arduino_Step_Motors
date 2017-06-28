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
const int rele_air_pin = 52;      //Пин за реле въздух.

const int end_delay = 200;          //Забавяне между стъпките на централния двигател, в микросекунди.
                               // С увеличаване на стойността намаляват оборотите на вибрации.
const int start_delay = 760;   //Микросекунди при старт на централния двигател.

const int ratio = 150;            // с намаляне на стойноста забързваме (за скоростта на ляв и десен мотор )  
                                  //Отношение скорост на въртене на централния мотор към 
                                  //скорост на левия и десния мотор. Трбва да е цяло число.
const unsigned long 
  early_rele_air_off_ms = 2000;   //Предварение реле въздух в милисекунди (1000ms = 1s).
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
unsigned long start_time_ms = 0;

int mode = 0;
const int start_steps = 450;           //
const int mode_1_increase_steps = 15;
const int mode_1_decrease_delay = 40; //Микросекунди

int mode_1_delay = 0;
int mode_1_steps = 0;


int i = 0;

void setup() 
{
pinMode(r_dir_pin, OUTPUT);
pinMode(r_pul_pin, OUTPUT);
pinMode(l_dir_pin, OUTPUT);
pinMode(l_pul_pin, OUTPUT);
pinMode(c_dir_pin, OUTPUT);
pinMode(c_pul_pin, OUTPUT);
pinMode(rele_air_pin, OUTPUT);
pinMode(button_start_1_pin, INPUT);
pinMode(button_start_4_pin, INPUT);
pinMode(button_start_6_pin, INPUT);
pinMode(button_start_8_pin, INPUT);
pinMode(button_stop_pin, INPUT);
pinMode(r_sensor_pin, INPUT);
pinMode(l_sensor_pin, INPUT); 

digitalWrite(r_dir_pin, HIGH);    // Посока на въртене на десния мотор
digitalWrite(l_dir_pin, LOW);     // Посока на въртене на левия мотор
digitalWrite(c_dir_pin, LOW);     // Посока на въртене на централния мотор - обратно на часовниковата стрелка.

}






void loop()
{
  
  b_stop_state = digitalRead(button_stop_pin);
  if (b_stop_state == HIGH) {
    term_ms = 0;start_time_ms = 0;mode = 0;
     digitalWrite(rele_air_pin, LOW);
  }

  if (term_ms == 0){
      b_start_1_state = digitalRead(button_start_1_pin);
      if (b_start_1_state == HIGH) {term_ms=60000;}
  
      b_start_4_state = digitalRead(button_start_4_pin);
      if (b_start_4_state == HIGH) {term_ms=240000;}
  
      b_start_6_state = digitalRead(button_start_6_pin);
      if (b_start_6_state == HIGH) {term_ms=360000;}
  
      b_start_8_state = digitalRead(button_start_8_pin);
      if (b_start_8_state == HIGH) {term_ms=480000;}

      if(b_start_1_state == HIGH ||
          b_start_4_state == HIGH ||
          b_start_6_state == HIGH ||
          b_start_8_state == HIGH){
               mode = 1;
               mode_1_steps = start_steps;
               mode_1_delay = start_delay;
               digitalWrite(rele_air_pin, HIGH);
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
             start_time_ms = millis();
             i = 0;
         }
      }else{         
         if (millis() < start_time_ms + term_ms){
             make_step(c_pul_pin, end_delay);
             i++;
             if( /*int(millis())*/i % ratio == 0 ){
                 r_sensor_state = digitalRead(r_sensor_pin);
                 l_sensor_state = digitalRead(l_sensor_pin);
        
                 if(r_sensor_state == HIGH){s_direction = 1;}
                 if(l_sensor_state == HIGH){s_direction = 0;}
        
                 if(s_direction == 0){
                     make_step(l_pul_pin, 0);
                 }else{
                     make_step(r_pul_pin, 0);
                 }
              }
              if(millis() > start_time_ms + term_ms - early_rele_air_off_ms){digitalWrite(rele_air_pin, LOW);}
         }else{
              term_ms = 0;
              start_time_ms = 0;
              i = 0;
              digitalWrite(rele_air_pin, LOW);
         }
      }  
   }
}
void make_step(int pul_pin, int delaystep){
    digitalWrite(pul_pin, LOW);
    digitalWrite(pul_pin, HIGH);
    delayMicroseconds(delaystep);
  
}


