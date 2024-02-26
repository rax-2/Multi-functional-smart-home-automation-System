//                    || श्री ||
const int gas_pin = A1;        // Analog pin for MQ2 gas sensor
const int fire_pin = A4;       // Fire sensor

const int ir_pin = 10;         // IR Sensor input pin
const int buzzer_pin = 5;      // Digital pin for buzzer
const int relay_pin = 3;       // Main Line Relay
const int switch_1_pin = 2;    // ESP 8266 switching 
const int switch_2_pin = 9;    // ESP 8266 switching 

const int switch_1_check = 7;  //Switch 2 Status
const int switch_2_check = 8;  //Switch 2 Status
 



void setup() {
  Serial.begin(9600);
  pinMode(ir_pin,INPUT);
  pinMode(buzzer_pin,OUTPUT);
  pinMode(relay_pin,OUTPUT);
  pinMode(switch_1_pin,OUTPUT);
  pinMode(switch_2_pin,OUTPUT);
  pinMode(switch_1_check,INPUT);
  pinMode(switch_2_check,INPUT);

  // switch 1 check

  if (digitalRead(switch_1_check) == LOW)
  {
    Serial.println("Switch 1 off");
    digitalWrite(switch_1_pin,HIGH);
    delay(2000);
    digitalWrite(switch_1_pin,LOW);
    delay(2000);
    digitalWrite(switch_1_pin,HIGH);
    delay(2000);
    digitalWrite(switch_1_pin,LOW);
    delay(2000);
  }
  else if (digitalRead(switch_1_check) == HIGH)
  {
    Serial.println("Switch 1 on");
    digitalWrite(switch_1_pin,LOW);
    delay(2000);
    digitalWrite(switch_1_pin,HIGH);
    delay(2000);
    digitalWrite(switch_1_pin,LOW);
    delay(2000);
    digitalWrite(switch_1_pin,HIGH);
    delay(2000);
  }

//  switch 2 check

  if (digitalRead(switch_2_check) == LOW)
  {
    Serial.println("Switch 2 off");
    digitalWrite(switch_2_pin,HIGH);
    delay(2000);
    digitalWrite(switch_2_pin,LOW);
    delay(2000);
    digitalWrite(switch_2_pin,HIGH);
    delay(2000);
    digitalWrite(switch_2_pin,LOW);
    delay(2000);
  }
  else if (digitalRead(switch_2_check) == HIGH)
  {
    Serial.println("Switch 2 on");
    digitalWrite(switch_2_pin,LOW);
    delay(2000);
    digitalWrite(switch_2_pin,HIGH);
    delay(2000);
    digitalWrite(switch_2_pin,LOW);
    delay(2000);
    digitalWrite(switch_2_pin,HIGH);
    delay(2000);
  }

//  relay check
for (int a = 0 ; a < 5 ; a++)
{
  digitalWrite(relay_pin,HIGH);
  delay(1000);
  digitalWrite(relay_pin,LOW);
  delay(1000);
}

//buzzer check
for (int a = 0 ; a < 38 ; a++)
{
  digitalWrite(buzzer_pin,HIGH);
  delay(80);
  digitalWrite(buzzer_pin,LOW);
  delay(80);
}


}

void loop() {
  Serial.println();
  Serial.print("Gas sensor value: ");
  Serial.println(analogRead(gas_pin));
  Serial.print("fire sensor value: ");
  Serial.println(analogRead(fire_pin));
  Serial.print("IR sensor value: ");
  Serial.println(digitalRead(ir_pin));
  delay(1000);
}
