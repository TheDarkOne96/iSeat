
#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8); 
const int button_seat_1=2;//check if seat in car
const int button_seat_2=3;//check child on seat
const int motion=5;//read from motion sensor
const int led_red=10;//red led
const int led_yellow=11;//yellow led
const int led_blue=12;//blue led
const int sms1=7;
const int sms2=8;
const int micro=6;
const int OBD=4;
const int mono=9;
const int button_stop=13;//green led
const int AOUTpin_mono=0;
const int AOUTpin_temp=2;
int calibrationTime = 30;

void setup() {
  Serial.begin(9600);
  SIM900.begin(19200);
  pinMode(motion, INPUT);
  pinMode(micro, INPUT);
  pinMode(button_seat_1, INPUT);
  pinMode(button_seat_2, INPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(button_stop, INPUT);
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
int button0_data=0;//save the value of ODE
int button1_data=0;//save the value read from button 1
int button2_data=0;//save the value read from button 2
int read_micro=0;//save the value recieved from the microphone
int read_temp=0;//save the value recieved from the tempruture sensor
int checks;// when the car detect a child it will try varify if the kid is in the car
int read_motion=0;
int read_mono=0;
//int get_micro();


void loop() {
  button1_data=digitalRead(button_seat_1);
  button1_data=1;
  if(button1_data==1){//that means the seat is in the car
      button0_data=digitalRead(OBD);
      //button0_data=0;
         Serial.println("seat in car");
         delay(2000);
      if(button0_data==0){//that means the car is off
           Serial.println("car off");
           delay(2000);
         read_micro=get_micro();
            Serial.println("state: ");       
            Serial.println(read_micro);
            delay(2000);
        // read_motion=function_motion();
        button2_data=digitalRead(button_seat_2);
        read_motion=get_motion();
        //button2_data=1;
        //if((read_motion>=x)||(read_micro==y)||(button2_data==1)){
        if((read_micro==1)||(button2_data==1)||(read_motion==1)){
            checks=0;
             //button2_data=1;
            for(int i=0;i<24;i++){
                 read_micro=get_micro();
                 Serial.println ("mic states: ");//
                 Serial.println (read_micro);//
                 button2_data=digitalRead(button_seat_2);
                 //button2_data=0;
                 if(button2_data==1){Serial.println("button detected");}
                 read_motion=get_motion();
                 //if((read_motion>=x)||(read_micro>=y)||(button2_data==1)){checks++;}
                 if((read_micro==1)||(button2_data==1)||(read_motion==1)){checks++;}
                 delay(10000);//delay 10 seconds
            }
            Serial.println("detected count: "); 
            Serial.println(checks); 
            delay(6000);
            if(checks>7){
                Serial.println (" ");//
                Serial.println (" ");//
                Serial.print ("temp: ");//
                Serial.print (get_temp());//
                delay(3000);
                Serial.println (" ");//
                Serial.print ("Monoxide value: ");//
                Serial.print (analogRead(AOUTpin_mono));//
                delay(3000);
            if((get_temp()>=35)||(get_mono()==1)){ //if values form the sensor are greater than set values child is in danger
                // function_emargancy();
                read_temp=get_temp();
                read_mono=get_mono();
                function_emargancy(read_temp, read_mono);
                Serial.println("child in danger");
                delay(3000); 
                }
            else{
                  //function_normal();
                  function_normal();
                  Serial.println("exectue function normal");
                  delay(3000); 
                  }
      }
        }
        }
  
      else {//excute senario if car is on
        Serial.println("car on");
        delay(2000);
         Serial.println (" ");//

        //if(get_temp()>35){while(1){Serial.println("danger");}}
        //else{while(1){Serial.println("safe");}}
        // read_gas=function_gas();
        // read_temp=function_micro();
        if((get_temp()>=40)||(get_mono()==1)){ //if values form the sensor are greater than set values child is in danger
        // function_emargancy();
                read_temp=get_temp();
                read_mono=get_mono();
                function_emargancy(read_temp, read_mono);
          Serial.println("child in danger");
                delay(3000); 
        }
        else{Serial.println("child safe");
}
      }
  }
        //else {delay(240,00);}//it will wait 4 mintues before checking on the car state
  

  }





//Functions 

int get_micro(){//done
  int count=0;
  int val;
for(int i=0;i<500;i++){
    val =digitalRead(micro);
  //Serial.println (val);//remove later
  // when the sensor detects a signal above the threshold value, LED flashes
  if (val==HIGH) {
    digitalWrite(led_blue, HIGH);
    count++;
  }
  else {
    digitalWrite(led_blue, LOW);
  }
}
if (count>0){return 1;}
else{return 0;}
}

int get_mono(){//done
 int limit;
int value;
value= analogRead(AOUTpin_mono);//reads the analaog value from the CO sensor's AOUT pin
limit= digitalRead(mono);//reads the digital value from the CO sensor's DOUT pin
Serial.print("CO value: ");
Serial.println(value);//prints the CO value
Serial.print("Limit: ");
Serial.print(limit);//prints the limit reached as either LOW or HIGH (above or underneath)
delay(100);
if (limit == HIGH){
digitalWrite(led_blue, HIGH);//if limit has been reached, LED turns on as status indicator
}
else{
digitalWrite(led_blue, LOW);//if threshold not reached, LED remains off
}
if(limit==1){return 1;}
else{return 0;}
}


int get_temp(){//done
  int temp;
  int temp_f;
temp = analogRead(AOUTpin_temp);
 Serial.print("RAW DATA: ");
Serial.print (temp);
Serial.println(" ");
  //converts raw data into degrees celsius and prints it out
   //500mV/1024=.48828125
  temp= temp * 0.48828125;
  Serial.print("CELSIUS: ");
  Serial.print(temp);
  Serial.println("*C ");
  //converts celsius into fahrenheit 
  temp_f = temp *9 / 5;
  temp_f = temp_f + 32;
  Serial.print("FAHRENHEIT: ");
  Serial.print(temp_f);
  Serial.println("*F");
  delay(1000);
  return temp;
  }

  

 int get_motion(){
delay(2000);
int var = digitalRead(motion);
int count=0;
for(int x=0; x<=20;x++){
  if(var==HIGH){
  count++;
  var=digitalRead(motion);
}
}
if(count>0){
  Serial.println("Motion Detected"); return 1;
} else   Serial.println("No Motion Detected"); return 0;
 }



void Send_emergency(int temp, int limit){
    // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+971507050059\""); 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Your child is in danger");
  SIM900.print("temperture: " );
  SIM900.println(temp ); 
  SIM900.print("Monoxide level " );
  if(limit==1){ SIM900.println("over limit " );}
  else {SIM900.println("normal" );}
  SIM900.println("Police will be informed after 1:30 minutes form recieveing this massage");
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
}


void Send_normal(){
    // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+971507050059\""); 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Your child is in danger");
  SIM900.println("Police will be informed after 3:00 minutes form recieveing this massage");
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
}



void Send_police(int temp, int limit){
    // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+971507050059\""); 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("The child of Mr. Omar is in danger");
  SIM900.print("temperture: " );
  SIM900.println(temp ); 
  SIM900.print("Monoxide level " );
  if(limit==1){ SIM900.println("over limit " );}
  else {SIM900.println("normal" );}
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
}


void function_emargancy(int temp, int limit){
  digitalWrite(led_red, HIGH);
  int waiting=0;
Send_emergency ( temp,  limit);
for (int i=0; i<30,000; i++){
  if(digitalRead(button_stop)==1){
    i=1000000;
    waiting=1;
  }
}
if(waiting==0){
Send_police( temp,  limit);
while(waiting==0){
      if(digitalRead(button_stop)==1){
    //i=1000000;
    waiting=1;
      }
}
}
  digitalWrite(led_red, LOW);
}

void function_normal(){
  digitalWrite(led_red, HIGH);
  int waiting=0;
Send_normal();
for (int i=0; i<30,000; i++){
  if(digitalRead(button_stop)==1){
    i=1000000;
    waiting=1;
  }
}
if(waiting==0){
Send_police( 0,  0);
while(waiting==0){
      if(digitalRead(button_stop)==1){
    //i=1000000;
    waiting=1;
      }
}
}
  digitalWrite(led_red, LOW);
}


