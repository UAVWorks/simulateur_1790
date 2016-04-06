#include <Potar.h>

void init(){
	int x = analogRead(Pin);
	Min = x;
	Max = x +1;
}

int update() {
	int x = analogRead(Pin);
	mapMinMax(x);
	Value = map(x,Min,Max,,);
	return Value;
}

void mapMinMax(int read){
	if(read<Min)
		Min = read;
	if(read>Max)
		Max = read;
}

