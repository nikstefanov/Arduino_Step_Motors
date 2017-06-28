/**
Nikolay Stefanov
16 May 2017


*/


const int r_dir_pin = 7;
const int r_pul_pin = 4;

const int l_dir_pin = 6;
const int l_pul_pin = 3;

const int c_dir_pin = 5;
const int c_pul_pin = 2;

//const int stepsPerRevolution = 800;

const int button_start_pin = 30;
const int button_stop_pin = 31;
int b_start_state = 0;
int b_stop_state = 0;

int s_delay = 800;
int i_steps = 450;
float coef = 1.1;
int seconds = 0;
int i=0;
void setup() 
{
pinMode(r_dir_pin, OUTPUT);
pinMode(r_pul_pin, OUTPUT);
pinMode(l_dir_pin, OUTPUT);
pinMode(l_pul_pin, OUTPUT);
pinMode(c_dir_pin, OUTPUT);
pinMode(c_pul_pin, OUTPUT);
pinMode(button_start_pin, INPUT);
pinMode(button_stop_pin, INPUT); 

digitalWrite(r_dir_pin, HIGH);    // Change direction.
digitalWrite(l_dir_pin, HIGH);    // Change direction.
digitalWrite(c_dir_pin, HIGH);    // Change direction.
}

void loop() {
     make_step(r_pul_pin, 400);
     
}




void make_step(int pul_pin, int delaystep){
    digitalWrite(pul_pin, LOW);
    digitalWrite(pul_pin, HIGH);
    //delayMicroseconds(delaystep);
    delay(delaystep);
  
}
