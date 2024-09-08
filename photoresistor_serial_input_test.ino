//By Alexandros Tourloukis
//August 15, 2024
void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
}

void loop() {
  // Read analog values from pins A0, A1, A2, and A3
  int valueA0 = analogRead(A0);
  int valueA1 = analogRead(A1);
  int valueA2 = analogRead(A2);
  int valueA3 = analogRead(A3);

  // Print the values to the Serial Monitor
  Serial.print("A0: ");
  Serial.print(valueA0);
  Serial.print(" | A1: ");
  Serial.print(valueA1);
  Serial.print(" | A2: ");
  Serial.print(valueA2);
  Serial.print(" | A3: ");
  Serial.println(valueA3);

  // Wait for 1 second
  delay(1000);
}

