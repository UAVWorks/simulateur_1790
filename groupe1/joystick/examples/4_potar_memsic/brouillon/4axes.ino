#define NUM_AXES    4         // 4 axes, X, Y, Z, etc

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

    for (uint8_t ind=0; ind<NUM_AXES; ind++) 
    {
    joyReport.axis[ind] = ind*1000;
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

    for (uint8_t ind=0; ind<NUM_AXES; ind++)
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
