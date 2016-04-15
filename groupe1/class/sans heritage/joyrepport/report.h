#ifndef REPPORT_H_
#define REPPORT_H_

#include <Arduino.h>

class joyReport_t{
	public:
		joyReport_t(numAxes);
		void init();
		void setJoyReport(int tabValue[]);
		void sendJoyReport(struct joyReport_t *report);
	private:
		int16_t axis[];
		int num_axes
};

#endif