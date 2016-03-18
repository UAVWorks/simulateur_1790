const int xIn = 2;              // X output
const int yIn = 3;              // Y output

void setup() {
  Serial.begin(9600);
}

void loop() {
  // variables to read the pulse widths:
  int pulseX, pulseY;
 
  pulseX = pulseIn(xIn,HIGH);  // Read X pulse  
  pulseY = pulseIn(yIn,HIGH);  // Read Y pulse

  // Display result
  Serial.print(pulseX);	       // Display X and Y values
  Serial.print("\t");
  Serial.println(pulseY);

  delay(200);
}
