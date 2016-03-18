#define NUM_AXES     2        // 6 axes, X, Y, Z, etc
#define YIN          3         // Y output
#define XIN          2         // X output

typedef struct joyReport_t {
    int16_t axis[NUM_AXES];
} joyReport_t;

joyReport_t joyReport;

int valeur_Min[NUM_AXES];
int valeur_Max[NUM_AXES];
void setup(void);
void loop(void);
void sendJoyReport(joyReport_t *report);

void setup() 
{
    Serial.begin(115200);
    delay(200);
  
}

void sendJoyReport(struct joyReport_t *report)
{
#ifndef DEBUG
    Serial.write((uint8_t *)report, sizeof(joyReport_t));
    #define DEBUG
#else

    // dump human readable output for debugging
    for (uint8_t ind=0; ind<NUM_AXES; ind++) {
	Serial.print("axis[");
	Serial.print(ind);
	Serial.print("]= ");
	Serial.print(report->axis[ind]);
	Serial.print(" ");
    }
    Serial.println();

#endif
}

void loop() 
{
  int pulseX, pulseY,accelerationX, accelerationY;
        pulseX = pulseIn(XIN,HIGH);  // Read X pulse
        accelerationX = ((pulseX / 10) - 500) * 8;

        if (accelerationX< valeur_Min[0])
        {
          valeur_Min[0] = accelerationX;
        }
        if (accelerationX > valeur_Max[0])
        {
          valeur_Max[0] = accelerationX;
        }
      pulseY = pulseIn(YIN,HIGH);  // Read Y pulse
        accelerationY = ((pulseY / 10) - 500) * 8;

        if (accelerationY < valeur_Min[1])
        {
          valeur_Min[1] = accelerationY ;
        }
        if (accelerationY > valeur_Max[1])
        {
          valeur_Max[1] = accelerationY;
        }
 
    joyReport.axis[0] =map(accelerationX, valeur_Min[0], valeur_Max[0], -32768,32767 );
    joyReport.axis[1] =map(accelerationY, valeur_Min[1], valeur_Max[1], -32768,32767 );
    
        sendJoyReport(&joyReport);
}

