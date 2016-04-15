joyReport_t(numAxes){
    int16_t axis[numAxes];
    num_axes = numAxes;
}

void init(){
    Serial.begin(115200);
    delay(200);
}
void setJoyReport(int tabValue[]){
    for(uint8_t ind=0; ind<numAxes; ind++)
        axis[ind] = tabValue[ind];
}

void sendJoyReport(struct joyReport_t *report)
{
#ifndef DEBUG
    Serial.write((uint8_t *)report, sizeof(joyReport_t));
    #define DEBUG
#else

    // dump human readable output for debugging
    for (uint8_t ind=0; ind<numAxes; ind++) {
	Serial.print("axis[");
	Serial.print(ind);
	Serial.print("]= ");
	Serial.print(report->axis[ind]);
	Serial.print(" ");
    }
    Serial.println();

#endif
}