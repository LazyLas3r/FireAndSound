//insert whatever Arduino pins #'s are used for each Soleniods should be wired from acsending from left to right:
#define Solenoid_1 2
#define Solenoid_2 3
#define Solenoid_3 4
#define Solenoid_4 5
#define Solenoid_5 6
#define Solenoid_6 7
#define Solenoid_7 8
#define Wheel_Sensor 9
#define Sequence_button 10

// binary input pins for triggering sound board. This version of the script is for the sound board in "Intergrated Mode 0"
// Dip switches on sound board should be set to (0,0,0)
#define s1 A0 
#define s2 A1
#define s3 A2
#define s4 A3
#define s5 A4
#define s6 A5

 
class Sound_Trigger{
  private:
    byte Pin_1; 
    byte Pin_2;
    byte Pin_3;
    byte Pin_4;
    byte Pin_5;
    byte Pin_6;
    byte Pin_7;
    byte Pin_8;   
  public:
    Sound_Trigger(byte Pin_1,byte Pin_2,byte Pin_3,byte Pin_4,byte Pin_5,byte Pin_6){
      this->Pin_1 = Pin_1;
      this->Pin_2 = Pin_2;
      this->Pin_3 = Pin_3;
      this->Pin_4 = Pin_4;
      this->Pin_5 = Pin_5;
      this->Pin_6 = Pin_6;
      initialize();}
  void initialize(){
    pinMode (Pin_1,OUTPUT);
    digitalWrite(Pin_1,HIGH);
    pinMode (Pin_2,OUTPUT);
    digitalWrite(Pin_2,HIGH);
    pinMode (Pin_3,OUTPUT);
    digitalWrite(Pin_3,HIGH);
    pinMode (Pin_4,OUTPUT);
    digitalWrite(Pin_4,HIGH);
    pinMode (Pin_5,OUTPUT);
    digitalWrite(Pin_5,HIGH);
    pinMode (Pin_6,OUTPUT);
    digitalWrite(Pin_6,HIGH);}
  
  void Play_Sound(byte Track_num, int Duration){   
   if(Track_num==1){
      digitalWrite(Pin_1,LOW);
        delay(Duration);
      digitalWrite(Pin_1,HIGH);}
    else if(Track_num==2){
      digitalWrite(Pin_2,LOW);
        delay(Duration);
      digitalWrite(Pin_2,HIGH);}
    else if(Track_num==3){
      digitalWrite(Pin_1,LOW);
      digitalWrite(Pin_2,LOW);
        delay(Duration);
      digitalWrite(Pin_1,HIGH);
      digitalWrite(Pin_2,HIGH);}
    else if(Track_num==4){
      digitalWrite(Pin_3,LOW);
        delay(Duration);
      digitalWrite(Pin_3,HIGH);}
    else if(Track_num==5){
      digitalWrite(Pin_1,LOW);
      digitalWrite(Pin_3,LOW);
        delay(Duration);
      digitalWrite(Pin_1,HIGH);
      digitalWrite(Pin_3,HIGH);}
    else if(Track_num==6){
      digitalWrite(Pin_2,LOW);
      digitalWrite(Pin_3,LOW);
        delay(Duration);
      digitalWrite(Pin_2,HIGH);
      digitalWrite(Pin_3,HIGH);}    
    else if(Track_num==7){   
      digitalWrite(Pin_1,LOW);
      digitalWrite(Pin_2,LOW);
      digitalWrite(Pin_3,LOW);
        delay(Duration);
      digitalWrite(Pin_1,HIGH);
      digitalWrite(Pin_2,HIGH);
      digitalWrite(Pin_3,HIGH);} 
    else if(Track_num==8){
      digitalWrite(Pin_4,LOW);
        delay(Duration);
      digitalWrite(Pin_4,HIGH);}   
    else if(Track_num==9){
      digitalWrite(Pin_1,LOW);
      digitalWrite(Pin_4,LOW);
        delay(Duration);
      digitalWrite(Pin_1,HIGH);
      digitalWrite(Pin_4,HIGH);} 
    else if(Track_num==10){
      digitalWrite(Pin_2,LOW);
      digitalWrite(Pin_4,LOW);
        delay(Duration);
      digitalWrite(Pin_2,HIGH);
      digitalWrite(Pin_4,HIGH);} 
    else if(Track_num==11){   
      digitalWrite(Pin_1,LOW);
      digitalWrite(Pin_2,LOW);
      digitalWrite(Pin_4,LOW);
        delay(Duration);
      digitalWrite(Pin_1,HIGH);
      digitalWrite(Pin_2,HIGH);
      digitalWrite(Pin_4,HIGH);} 
    else if(Track_num==12){
      digitalWrite(Pin_3,LOW);
      digitalWrite(Pin_4,LOW);
        delay(Duration);
      digitalWrite(Pin_3,HIGH);
      digitalWrite(Pin_4,HIGH);}}   };   
      
Sound_Trigger Sound_byte (s1,s2,s3,s4,s5,s6);

class Poofer{
  private:
    byte Solenoid_pin;    
  public:
    Poofer(byte Solenoid_pin){
      this->Solenoid_pin = Solenoid_pin;
      initialize();}
  void initialize(){
    pinMode (Solenoid_pin,OUTPUT);
    digitalWrite(Solenoid_pin,LOW);}
  void Solenoid_open(){
    digitalWrite(Solenoid_pin,HIGH);}
  void Solenoid_close(){
    digitalWrite(Solenoid_pin,LOW);}
  void burst(int stay_open){
    Solenoid_open();
    delay(stay_open);
    Solenoid_close();}};
 
Poofer poof_1 (Solenoid_1);
Poofer poof_2 (Solenoid_2);
Poofer poof_3 (Solenoid_3);
Poofer poof_4 (Solenoid_4);
Poofer poof_5 (Solenoid_5);
Poofer poof_6 (Solenoid_6);
Poofer poof_7 (Solenoid_7);

int Train_Crash = 2;
int Moving_Train = 1;

int Train_Crash_Len = 10000;
int Moving_Train_Len = 7000;

byte Wheel_state {HIGH};    
byte Wheel_counter {0};    // keeping track of how far the wheel is spinning and if the wheel has come to a stop
byte Prev_Wheel_counter{0};

byte minimum_spin {5}; // minimum rotation of wheel before finale will trigger when wheel comes to a stop
byte index{0};         // index to keep track of which Soleniods turn it is to fire


unsigned long  previousMillis {0};  
unsigned long lastDebounceTime = 0;  // smoothing for Wheel_counter and indexing. May have to be adjusted up for optimal solenoid operation
unsigned long debounceDelay = 500;

byte Sequence_selection{0};  // setting to change flame pattern while wheel is in motion
byte Sequence_list_end {3};
byte Finale_selection {0};
byte Finale_list_end {1};

byte Current_array_size{7};    // saved patterns and info required for controll flow
byte num_of_arrays {1};
int Left_Right [] {1,2,3,4,5,6,7}; 
int Right_Left [] {7,6,5,4,3,2,1};
int Center_out_1 [] {4,5,6,7};
int Center_out_2 [] {4,3,2,1};
int Closing_in_1 [] {7,6,5,4};
int Closing_in_2 [] {1,2,3,4};
int *array_ptr_1 {Left_Right};
int *array_ptr_2 {Center_out_2};

int reset_delay {2000};   // Change to alter time between wheel stopping and reset.
int finale_delay {600};  // Change to alter time between wheel stopping and finale. 
int short_burst {250};   // Change to alter flame burst size while wheel spins.
int long_burst {1000};  // Change to alter flame burst size during finale.


void setup() {
//  Serial.begin(9600);
  pinMode (Wheel_Sensor,INPUT);
  digitalWrite(Wheel_Sensor,HIGH);
  pinMode (Sequence_button,INPUT);
  digitalWrite(Sequence_button,HIGH);}



void loop() {
  unsigned long currentMillis = millis();  // timer 
  Wheel_state = digitalRead(Wheel_Sensor); 
  byte S_button = digitalRead(Sequence_button); 


  if (currentMillis - lastDebounceTime > debounceDelay && S_button == LOW && Wheel_counter == 0){
    Sequence_selection ++;
    if (Sequence_selection > Sequence_list_end){
      Sequence_selection = 0;}
    previousMillis = currentMillis;
    Change_pattern(Sequence_selection);
    delay(500);}


  if (currentMillis - lastDebounceTime > debounceDelay && Wheel_state == LOW){
    Wheel_counter ++;
    previousMillis = currentMillis;
    Serial.print("Wheel_counter:  ");
    Serial.println(Wheel_counter);

   if (Wheel_counter > 0){
    digitalWrite(s1,LOW);}
    
    if (num_of_arrays == 1){
      Sequence(array_ptr_1[index]);}
    else if(num_of_arrays == 2){
      Sequence(array_ptr_1[index],array_ptr_2[index]);}}

             
  if (currentMillis - previousMillis >= finale_delay && Wheel_counter >= minimum_spin && Wheel_counter == Prev_Wheel_counter) {
      previousMillis = currentMillis;
      digitalWrite(s1,HIGH);
      Finale();
      Wheel_counter = 0;
      index = 0;
      Serial.println("Finale fired. Counters reset.");
      delay(500);}

  if (currentMillis - previousMillis >= reset_delay && Wheel_counter == Prev_Wheel_counter && Wheel_counter >0){
      Wheel_counter = 0;
      digitalWrite(s1,HIGH);
      previousMillis = currentMillis;
      index = 0;
      Serial.println("Idle time elapsed. Counters reset. ");
      delay(500);}
      
    Prev_Wheel_counter = Wheel_counter;}


void Change_pattern(byte Sequence_selection){ 
  if (Sequence_selection == 0){  
      num_of_arrays = 1;
      array_ptr_1 = Left_Right;
      Current_array_size = sizeof(Left_Right)/sizeof(int);
      Serial.println("Sequence changed to: Left to Right");}

  else if (Sequence_selection == 1){
      num_of_arrays = 1;
      array_ptr_1 = Right_Left;
      Current_array_size = sizeof(Right_Left)/sizeof(int);
      Serial.println("Sequence changed to: Right to Left");}

  else if (Sequence_selection == 2){
      num_of_arrays = 2;
      array_ptr_1 = Center_out_1;
      array_ptr_2 = Center_out_2;
      Current_array_size = sizeof(Center_out_1)/sizeof(int);
      Serial.println("Sequence changed to: Center going outwards");}

  else if (Sequence_selection == 3){
      num_of_arrays = 2;
      array_ptr_1 = Closing_in_1;
      array_ptr_2 = Closing_in_2;
      Current_array_size = sizeof(Closing_in_1)/sizeof(int);
      Serial.println("Sequence changed to: Closing to center");}  }

void Finale(){
    poof_1.Solenoid_open();
    poof_2.Solenoid_open();
    poof_3.Solenoid_open();
    poof_4.Solenoid_open();
    poof_5.Solenoid_open();
    poof_6.Solenoid_open();
    poof_7.Solenoid_open();
    delay(long_burst);
    Close_all();
  Sound_byte.Play_Sound(Train_Crash,Train_Crash_Len); }

void Close_all(){
  poof_1.Solenoid_close();
  poof_2.Solenoid_close();
  poof_3.Solenoid_close();
  poof_4.Solenoid_close();
  poof_5.Solenoid_close();
  poof_6.Solenoid_close();
  poof_7.Solenoid_close();}
  
void Select_open(byte poofer){
  if (poofer == 1){
    poof_1.Solenoid_open();}
  if (poofer == 2){
    poof_2.Solenoid_open();}
  if (poofer == 3){
    poof_3.Solenoid_open();}
  if (poofer == 4){
    poof_4.Solenoid_open();}
  if (poofer == 5){
    poof_5.Solenoid_open();}
  if (poofer == 6){
    poof_6.Solenoid_open();}
  if (poofer == 7){
    poof_7.Solenoid_open();}}

void Select_close(byte poofer){
  if (poofer == 1){
    poof_1.Solenoid_close();}
  if (poofer == 2){
    poof_2.Solenoid_close();}
  if (poofer == 3){
    poof_3.Solenoid_close();}
  if (poofer == 4){
    poof_4.Solenoid_close();}
  if (poofer == 5){
    poof_5.Solenoid_close();}
  if (poofer == 6){
    poof_6.Solenoid_close();}
  if (poofer == 7){
    poof_7.Solenoid_close();}}

void Sequence(byte poofer){
  Close_all();
  Select_open(poofer);
  delay(short_burst);
  Select_close(poofer);
  index ++;
    if (index >= Current_array_size){ index = 0;}}

void Sequence(byte poofer_1, byte poofer_2){
  Close_all();
  Select_open(poofer_1);
  Select_open(poofer_2);
  delay(short_burst);
  Select_close(poofer_1);
  Select_close(poofer_2);
  index ++;
    if (index >= Current_array_size){ index = 0;}}






 
  
