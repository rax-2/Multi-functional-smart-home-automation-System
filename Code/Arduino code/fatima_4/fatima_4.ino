//                    || श्री ||
const int gas_pin = A1;                  // Analog pin for MQ2 gas sensor
const int fire_pin = A4;                 // Fire sensor
const int ir_pin = 10;                   // IR Sensor input pin
const int buzzer_pin = 5;                // Digital pin for buzzer
const int relay_pin = 3;                 // Main Line Relay
const int switch_1_pin = 2;              // ESP 8266 switching
const int switch_2_pin = 9;              // ESP 8266 switching
const int switch_1_check = 7;            //Switch 2 Status
const int switch_2_check = 8;            //Switch 2 Status

int gas_threshold = 80;
int fire_threshold = 20;
int switch_1_state;
int switch_2_state;
int gas;
int fire;
int ir;

void setup()
{
  Serial.begin(9600);                    // Serial monitor setup
  pinMode(ir_pin, INPUT);                // IR Sensor setup for Input
  pinMode(buzzer_pin, OUTPUT);           // Buzzer Setup for output
  pinMode(relay_pin, OUTPUT);            // Main line Relay Setup Output
  pinMode(switch_1_pin, OUTPUT);         // Switch 1 pin for switching Output
  pinMode(switch_2_pin, OUTPUT);         // Switch 2 pin for switching output
  pinMode(switch_1_check, INPUT);        // Switch 1 status check input pin
  pinMode(switch_2_check, INPUT);        // Switch 2 status check input pin
  pinMode(LED_BUILTIN, OUTPUT);          // Board built in led setup for indecation
  // turn off switching
  digitalWrite(switch_1_pin, LOW);  
  digitalWrite(switch_1_pin, LOW);
}

void loop()
{
  digitalWrite(LED_BUILTIN,HIGH);
  // turn off switching
  digitalWrite(switch_1_pin, LOW);
  digitalWrite(switch_2_pin, LOW);

  // Read the analog value from the Gas sensor
  gas = analogRead(gas_pin);
  // Read the analog value from the Flame sensor
  fire = analogRead(fire_pin);
  // Read the value from the IR sensor
  ir = digitalRead(ir_pin);

  // Print data on the serial monitor
  Serial.println();
  Serial.print("Gas : ");
  Serial.println(gas);
  Serial.print("Flame: ");
  Serial.println(fire);
  Serial.print("IR: ");
  Serial.println(ir);
  Serial.print("Switch 1 and Switch 2 status: ");
  Serial.print(digitalRead(switch_1_check));
  Serial.print(" ");
  Serial.println(digitalRead(switch_2_check));
  Serial.print("Switch 1 and Switch 2 state: ");
  Serial.print(digitalRead(switch_1_pin));
  Serial.print(" ");
  Serial.println(digitalRead(switch_2_pin));

  // Check gas leakage
  if (gas > gas_threshold)
  {
    Serial.println("Gas Leakage");       // Gas leak message
    // Task for Gas leakage
    while (true)
    {
      gas = analogRead(gas_pin);         // gas status read
      Serial.print("Gas : ");
      Serial.println(gas);
      switch_1_state = digitalRead(switch_1_check);
      switch_2_state = digitalRead(switch_2_check);

      if (gas <= gas_threshold)          // End task when no Gas found
      {
        break;
      }
      // Swith 1 off when switch is on
      if (switch_1_state == 1)
      {
        digitalWrite(switch_1_pin, HIGH);
      }
      // Swith 2 off when switch is on
      if (switch_2_state == 1)
      {
        digitalWrite(switch_2_pin, HIGH);
      }

      digitalWrite(relay_pin, HIGH);     // Turn Off Main 220V~
      for (int a = 0; a < 40; a++)
      {
        digitalWrite(buzzer_pin, HIGH);  // Sound the buzzer
        delay(40);                       // Wait for 0.5 second
        digitalWrite(buzzer_pin, LOW);   // Stop the buzzer
        delay(70);                       // wait
      }
    }
  }
  // Check Fire
  else if (fire > fire_threshold)
  {
    Serial.println("Fire ");             // Fire message
    // Task for flame dected
    while (true)
    {
      fire = analogRead(fire_pin);       // flame status read
      Serial.print("Flame : ");
      Serial.println(fire);
      switch_1_state = digitalRead(switch_1_check);
      switch_2_state = digitalRead(switch_2_check);

      if (fire <= fire_threshold)        // End task when no Flame
      {
        break;
      }
       // Swith 1 off when switch is on
      if (switch_1_state == 1)
      {
        digitalWrite(switch_1_pin, HIGH);
      }
      // Swith 2 off when switch is on
      if (switch_2_state == 1)
      {
        digitalWrite(switch_2_pin, HIGH);
      }

      digitalWrite(relay_pin, HIGH);     // Turn Off Main 220V~
      for (int a = 0; a < 40; a++)
      {
        digitalWrite(buzzer_pin, HIGH);  // Sound the buzzer
        delay(40);                       // Wait for 0.5 second
        digitalWrite(buzzer_pin, LOW);   // Stop the buzzer
        delay(70);                       // wait
      }
    }
  }

  // When no Gas and Flame
  else if (gas <= gas_threshold && fire <= fire_threshold)
  {
    digitalWrite(relay_pin, LOW);        // Turn Off Main 220V~
    digitalWrite(buzzer_pin, LOW);       // Buzzer off
    // Check if IR Sensor get values
    if (ir == LOW)
    {
      for (int a = 0; a < 15; a++)
      {
        digitalWrite(buzzer_pin, HIGH);  // Buzzer on
        delay(200);                      // wait
        digitalWrite(buzzer_pin, LOW);   // Buzzer off
        delay(50);                       // wait
      }
    }
  }
  delay(30);                             // wait
  digitalWrite(LED_BUILTIN,LOW);
  delay(30);                             // wait

}
