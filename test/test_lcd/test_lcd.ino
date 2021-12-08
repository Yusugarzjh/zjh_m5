
const int output2 = 2;
const int output3 = 3;
void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output2, OUTPUT);
  pinMode(output3, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output2, LOW);
  digitalWrite(output3, LOW);

}

void loop(){
  digitalWrite(output2, LOW);
  delay(1000);
   digitalWrite(output2, 1);
     delay(1000);

}
