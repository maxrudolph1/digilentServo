#ifndef MyServo_h
#define MyServo_h

#include <Arduino.h>

class digiServo
{
  public:
	digiServo(int DIR, int EN, int SA, int SB);
	void angle(int a);
    int trackTicks();
	void clockwise(int sp);
	void cclockwise(int sp);
    void track();
	int curAngle;
	int ticks = 0;
    float w = 0;
    float prev = 0;
    float Pc = 0.0, G = 0.0, P = 1.0, Xp = 0.0, Zp = 0.0, Xe = 0.0;
    float varmeasq = 1373;
    float varprocess = 10;
    float th = 0;
    unsigned long t1;
    unsigned long t2;
    float timDiff = 0;
    float ang = 0;
	
  private:
	int _dir;
	int _en;
	int _sa;
	int _sb;
	int _prev = 0;
	int _cur = 0;

    double diff = 1.137;
	int toDec(bool b, bool a);
    float Kalmanfilter(float val, float varProcess, float varmeas, float prev);


};

#endif