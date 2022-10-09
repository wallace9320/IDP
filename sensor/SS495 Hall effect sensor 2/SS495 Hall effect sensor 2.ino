float Ref = analogRead(A0);
//int countmag = 0;
//int countnonmag = 0;


void setup() {
  
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
  
  while (millis() < 7500) {
  Ref = (Ref + analogRead(A0))/2; 
  delay(100);
  //Serial.println(Ref); 
}
  

  Serial.print("Reference Value: ");
  Serial.println(Ref);
  digitalWrite(2, HIGH);
}

void loop() {
  
  float average = analogRead(A0);

  for (int i=0; i < 250; i++) {
  
  average = (average + analogRead(A0))/2;
  //Serial.println(average); 
  delay(40);
}

  if (abs(average - Ref) > 4) {
    Serial.print("Magnetic, value = " );
    Serial.println(average);
    digitalWrite(4, HIGH);
    delay(1000);                       
    digitalWrite(4, LOW);
    //countmag += 1;

}
  else {
    Serial.print("Nonmagnetic, value =");
    Serial.println(average);
    digitalWrite(7, HIGH);
    delay(1000);                       
    digitalWrite(7, LOW);
    //countnonmag +=1;
  }
  //delay(3000);
  
  /*Serial.print("Count:");
  Serial.print(countmag);
  Serial.print(",");
  Serial.println(countnonmag);*/
}
