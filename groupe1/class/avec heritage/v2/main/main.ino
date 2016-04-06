#include <Capteur.h>
#include <Potar.h>

#define NUM_AXES    4         // 4 axes, X, Y, Z, etc

typedef struct joyReport_t {
    int16_t axis[NUM_AXES];
} joyReport_t;

joyReport_t joyReport;
Capteur* tabCapteur[NUM_AXES];

tabCapteur[0] = new Potar(0);
tabCapteur[1] = new Potar(1);
tabCapteur[2] = new Potar(2);
tabCapteur[3] = new Potar(3);

void setup(void);
void loop(void);
void sendJoyReport(joyReport_t *report);

void setup() 
{
    Serial.begin(115200);
    delay(200);

    for (uint8_t ind=0; ind<NUM_AXES; ind++) 
    {
      tabCapteur[ind]->init();
    }
    
}

void sendJoyReport(struct joyReport_t *report)
{
    Serial.write((uint8_t *)report, sizeof(joyReport_t));
}

void loop() 
{

    for (uint8_t ind=0; ind<NUM_AXES; ind++)
    {   
      joyReport.axis[ind] = tabCapteur[ind]->update();
    }
    
    sendJoyReport(&joyReport);

    delay(100);
}
