const int xIn = 2;              // X output
const int yIn = 3;              // Y output

void setup() {
  Serial.begin(9600);
}

void loop() {
  // variables to read the pulse widths:
  int pulseX, pulseY,accelerationX, accelerationY;
 
  pulseX = pulseIn(xIn,HIGH);  // Read X pulse  
  accelerationX = ((pulseX / 10) - 500) * 8;
  
  pulseY = pulseIn(yIn,HIGH);  // Read Y pulse
  accelerationY = ((pulseY / 10) - 500) * 8;

  // Display result
  Serial.print(accelerationX);	       // Display X and Y values
  Serial.print("\t");
  Serial.println(accelerationY);
  Serial.print(pulseX);	       // Display X and Y values
  Serial.print("\t");
  Serial.println(pulsey);	       // Display X and Y values
  Serial.println();

  delay(200);
}
