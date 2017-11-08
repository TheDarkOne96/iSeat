const int button_seat_1=1;//check if seat in car
const int button_seat_2=2;//check child on seat
const int motion=3;//read from motion sensor
const int led_red=4;//red led
const int led_yellow=5;//yellow led
const int led_blue=6;//blue led
const int sms1=7;
const int sms2=8;
const int micro=10;
const int OBD=11;


void setup() {
  Serial.begin(9600);
  pinMode(motion, INPUT);
  pinMode(button_seat_1, INPUT);
  pinMode(button_seat_2, INPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(OBD, INPUT);
  digitalWrite(motion, LOW);
  
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000); //1 second
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
}
int button0_date=0;//save the value of ODE
int button1_data=0;//save the value read from button 1
int button2_data=0;//save the value read from button 2
int read_micro=0;//save the value recieved from the microphone
int read_temp=0;//save the value recieved from the tempruture sensor
int checks;// when the car detect a child it will try varify if the kid is in the car


void loop() {
  button1_data=digitalRead(button_seat_1);
  if(button1_data==1){//that means the seat is in the car
      button1_data=digitalRead(OBD);
      if(button0_data==0){//that means the car is off
        // read_micro=function_micro();
        // read_motion=function_motion();
        // button2_data=digitalRead(button_seat_2);
        //if((read_motion>=x)||(read_micro>=y)||(button2_data==1)){
            //checks=0;
            //for(int i=0;i<24;i++){
                 // read_micro=function_micro();
                 // read_temp=function_micro();
                 // button2_data=digitalRead(button_seat_2);
                 //if((read_temp>=x)||(read_micro>=y)||(button2_data==1)){checks++;}
                 //delay(10000)//delay 10 seconds
            //}
            //if(checks>7){
            //read_gas=function_gas();
            //read_temp=function_temp();
            //if((read_temp>=x)||(read_gas>=y)){ //if values form the sensor are greater than set values child is in danger
                // function_emargancy();}
            //else{
                  //function_normal();
                  //}
      //}
  }
      else {//excute senario if 
        // read_gas=function_gas();
        // read_temp=function_micro();
        //if((read_temp>=x)||(read_gas>=y)){ //if values form the sensor are greater than set values child is in danger
        // function_emargancy();}
      }
  }
  else {delay(240,00);}//it will wait 4 mintues before checking on the car state
  }
}
