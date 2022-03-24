//insert whatever Arduino pins #'s are used for each Soleniods should be wired from acsending from leftmost to right:
#define Solenoid_1 2
#define Solenoid_2 3
#define Solenoid_3 4
#define Solenoid_4 5
#define Solenoid_5 6
#define Solenoid_6 7
#define Solenoid_7 8
#define Sequence_Triggerpin 9
#define Final_Triggerpin 10

class Poofers{
  private:
    byte Solenoid_pin1;
    byte Solenoid_pin2;
    byte Solenoid_pin3;
    byte Solenoid_pin4;
    byte Solenoid_pin5;
    byte Solenoid_pin6;
    byte Solenoid_pin7;     
  public:
    Poofers(byte Solenoid_pin1,byte Solenoid_pin2,byte Solenoid_pin3,byte Solenoid_pin4,byte Solenoid_pin5,byte Solenoid_pin6,byte Solenoid_pin7){
      this->Solenoid_pin1 = Solenoid_pin1;
      this->Solenoid_pin2 = Solenoid_pin2;
      this->Solenoid_pin3 = Solenoid_pin3;
      this->Solenoid_pin4 = Solenoid_pin4;
      this->Solenoid_pin5 = Solenoid_pin5;
      this->Solenoid_pin6 = Solenoid_pin6;
      this->Solenoid_pin7 = Solenoid_pin7;
      initialize();}
  void initialize(){
    pinMode (Solenoid_pin1,OUTPUT);
    digitalWrite(Solenoid_pin1,LOW);
    pinMode (Solenoid_pin2,OUTPUT);
    digitalWrite(Solenoid_pin2,LOW);
    pinMode (Solenoid_pin3,OUTPUT);
    digitalWrite(Solenoid_pin3,LOW);
    pinMode (Solenoid_pin4,OUTPUT);
    digitalWrite(Solenoid_pin4,LOW);
    pinMode (Solenoid_pin5,OUTPUT);
    digitalWrite(Solenoid_pin5,LOW);
    pinMode (Solenoid_pin6,OUTPUT);
    digitalWrite(Solenoid_pin6,LOW);
    pinMode (Solenoid_pin7,OUTPUT);
    digitalWrite(Solenoid_pin7,LOW);}
  void Select_open(byte poofer){
    if (poofer == 1){
      digitalWrite(Solenoid_pin1,HIGH);}
    else if (poofer == 2){
      digitalWrite(Solenoid_pin2,HIGH);}
    else if (poofer == 3){
      digitalWrite(Solenoid_pin3,HIGH);}
    else if (poofer == 4){
      digitalWrite(Solenoid_pin4,HIGH);}
    else if (poofer == 5){
      digitalWrite(Solenoid_pin5,HIGH);}
    else if (poofer == 6){
      digitalWrite(Solenoid_pin6,HIGH);}
    else if (poofer == 7){
      digitalWrite(Solenoid_pin7,HIGH);}}
  void Select_close(byte poofer){
    if (poofer == 1){
      digitalWrite(Solenoid_pin1,LOW);}
    else if (poofer == 2){
      digitalWrite(Solenoid_pin2,LOW);}
    else if (poofer == 3){
      digitalWrite(Solenoid_pin3,LOW);}
    else if (poofer == 4){
      digitalWrite(Solenoid_pin4,LOW);}
    else if (poofer == 5){
      digitalWrite(Solenoid_pin5,LOW);}
    else if (poofer == 6){
      digitalWrite(Solenoid_pin6,LOW);}
    else if (poofer == 7){
      digitalWrite(Solenoid_pin7,LOW);}}
  void close_all(){
    for (int P=1; P<=7; P++){
      Select_close(P);}}
  void open_all(){
    for (int P=1; P<=7; P++){
      Select_open(P);}}   
      };
 
Poofers poofers (Solenoid_1,Solenoid_2,Solenoid_3,Solenoid_4,Solenoid_5,Solenoid_6,Solenoid_7);

class Supervisor{
  private:
    byte Sequence_Trigger;
    byte Final_Trigger;    
  public:
    Supervisor(byte Sequence_Trigger,byte Final_Trigger){
      this->Sequence_Trigger = Sequence_Trigger;
      this->Final_Trigger = Final_Trigger;
      initialize();}
  void initialize(){
    pinMode (Sequence_Trigger,INPUT);
    pinMode (Final_Trigger,INPUT);
    digitalWrite(Sequence_Trigger,LOW);
    digitalWrite(Final_Trigger,LOW);}
  bool Commands_Sequence(){
    int Is_spinning = digitalRead(Sequence_Trigger);
    if (Is_spinning == HIGH){
//      Serial.println("Sequence Command detected");
      return true;}
    else{
      return false;}}
  bool Commands_Finale(){
    int Has_stopped = digitalRead(Final_Trigger);
    if (Has_stopped == HIGH){
//      Serial.println("Finale Command detected");
      return true;}
    else{
      return false;}} };
      
Supervisor supervisor (Sequence_Triggerpin,Final_Triggerpin);

byte index{0};         // index to keep track of which Soleniods turn it is to fire

byte Sequence_selection{0};  // setting to change flame pattern while wheel is in motion
byte Sequence_list_end {5};

byte Current_array_size{7};    // saved patterns and info required for controll flow
byte num_of_arrays {1};
int Left_Right [] {1,2,3,4,5,6,7}; 
int Right_Left [] {7,6,5,4,3,2,1};
int Single_Alternate [] {4,3,5,2,6,1,7};

int Center_out_1 [] {4,5,6,7};
int Center_out_2 [] {4,3,2,1};
int Closing_in_1 [] {7,6,5,4};
int Closing_in_2 [] {1,2,3,4};
int Double_Alternate_1 [] {3,1,2,4};
int Double_Alternate_2 [] {5,7,6,4};
int *array_ptr_1 {Left_Right};
int *array_ptr_2 {Center_out_2};

int Sequence_burst {500};   // Change to alter flame burst size while wheel spins.
int Finale_burst {1000};  // Change to alter flame burst size during finale.


void setup() {
//  Serial.begin(9600);
}

void loop() {

  if (supervisor.Commands_Sequence()){
    if (num_of_arrays == 1){
      Sequence(array_ptr_1[index]);}
    else if(num_of_arrays == 2){
      Sequence(array_ptr_1[index],array_ptr_2[index]);}}

  else if (supervisor.Commands_Finale()){
    Finale();} 
    
  else {
    poofers.close_all();
//    Serial.println("No signal detected. Poofers IDLE.");
}
  }



void Change_pattern(byte Sequence_selection){ 
  if (Sequence_selection == 0){  
      num_of_arrays = 1;
      array_ptr_1 = Left_Right;
      Current_array_size = sizeof(Left_Right)/sizeof(int);}
  else if (Sequence_selection == 1){
      num_of_arrays = 1;
      array_ptr_1 = Right_Left;
      Current_array_size = sizeof(Right_Left)/sizeof(int);}
  else if (Sequence_selection == 2){
      num_of_arrays = 2;
      array_ptr_1 = Center_out_1;
      array_ptr_2 = Center_out_2;
      Current_array_size = sizeof(Center_out_1)/sizeof(int);}
  else if (Sequence_selection == 3){
      num_of_arrays = 2;
      array_ptr_1 = Closing_in_1;
      array_ptr_2 = Closing_in_2;
      Current_array_size = sizeof(Closing_in_1)/sizeof(int);}
  else if (Sequence_selection == 4){  
      num_of_arrays = 1;
      array_ptr_1 = Single_Alternate;
      Current_array_size = sizeof(Single_Alternate)/sizeof(int);}
  else if (Sequence_selection == 5){
      num_of_arrays = 2;
      array_ptr_1 = Double_Alternate_1;
      array_ptr_2 = Double_Alternate_2;
      Current_array_size = sizeof(Double_Alternate_1)/sizeof(int);}}

void Finale(){
  poofers.open_all();
  delay(Finale_burst);
  poofers.close_all();}

  
void Sequence(byte poofer){
  poofers.Select_open(poofer);
  delay(Sequence_burst);
  poofers.Select_close(poofer);
  index ++;
    if (index >= Current_array_size){ 
      index = 0;
      Change_pattern(random(0,Sequence_list_end));}}

void Sequence(byte poofer_1, byte poofer_2){
  poofers.Select_open(poofer_1);
  poofers.Select_open(poofer_2);
  delay(Sequence_burst);
  poofers.Select_close(poofer_1);
  poofers.Select_close(poofer_2);
  index ++;
    if (index >= Current_array_size){
      index = 0;
      Change_pattern(random(0,Sequence_list_end));}}






 
  
