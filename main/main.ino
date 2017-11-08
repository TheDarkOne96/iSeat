const int button_seat_1=1;//check if seat in car
const int button_seat_2=2;//check child on seat
const int motion=3;//read from motion sensor
const int led_red=4;//red led
const int led_yellow=5;//yellow led
const int led_blue=6;//blue led
void setup() {
  Serial.begin(9600);
  pinMode(motion, INPUT);
  pinMode(button_seat_1, INPUT);
  pinMode(button_seat_1, INPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_blue, OUTPUT);
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

void loop() {

 

}
