#define NUM_AXES     6        // 6 axes, X, Y, Z, etc
#define NUM_POTAR    4
#define NUM_AXE_ACLM 2
#define YIN          3         // Y output
#define XIN          2         // X output

typedef struct joyReport_t {
    int16_t axis[NUM_AXES];
} joyReport_t;

joyReport_t joyReport;

int valeur_Min[NUM_POTAR];
int valeur_Max[NUM_POTAR];
int valeur_Min_Aclm[NUM_AXE_ACLM];
int valeur_Max_Aclm[NUM_AXE_ACLM];
void setup(void);
void loop(void);
void sendJoyReport(joyReport_t *report);

void setup() 
{
    Serial.begin(115200);
    delay(200);

    for (uint8_t ind=0; ind<NUM_POTAR; ind++) 
    {
      valeur_Min[ind] = analogRead(ind) ;
    valeur_Max[ind] = analogRead(ind)+1 ;
    }
    
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
      int pulseX, pulseY;
      pulseX = pulseIn(XIN,HIGH);  // Read X pulse
        if (pulseX < valeur_Min_Aclm[0])
        {
          valeur_Min_Aclm[0] = pulseX ;
        }
        if (pulseX > valeur_Max_Aclm[0])
        {
          valeur_Max_Aclm[0] = pulseX;
        }
      pulseY = pulseIn(YIN,HIGH);  // Read Y pulse
        if (pulseY < valeur_Min_Aclm[1])
        {
          valeur_Min_Aclm[1] = pulseY ;
        }
        if (pulseY > valeur_Max_Aclm[1])
        {
          valeur_Max_Aclm[1] = pulseY;
        }
 
    joyReport.axis[4] =map(pulseX, valeur_Min_Aclm[0], valeur_Max_Aclm[0], -32768,32767 );
    joyReport.axis[5] =map(pulseY, valeur_Min_Aclm[1], valeur_Max_Aclm[1], -32768,32767 );

    for (uint8_t ind=0; ind<NUM_POTAR; ind++)
    {
      int valeur_Potar = analogRead(ind);
    
      if ( valeur_Potar < valeur_Min[ind])
      {  
        valeur_Min[ind] = valeur_Potar ;
      }   
      if ( valeur_Potar > valeur_Max[ind])
      {
        valeur_Max[ind] = valeur_Potar ;
      }
    
      joyReport.axis[ind] =map(analogRead(ind), valeur_Min[ind], valeur_Max[ind], -32768,32767 );

    }
    
    sendJoyReport(&joyReport);

    delay(100);
}
