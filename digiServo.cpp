#include <Arduino.h>
#include <digiServo.h>
#include <string.h>

int ticks = 0;
float w = 0;
int prev = 0;
float Pc = 0.0, G = 0.0, P = 1.0, Xp = 0.0, Zp = 0.0, Xe = 0.0;
float varmeasq = 1373;
float varprocess = 10;



digiServo::digiServo(int DIR, int EN, int SA, int SB) {

	_dir = DIR;
	_en = EN;
	_sa = SA;
	_sb = SB;
	curAngle = 0;
	pinMode(_dir, OUTPUT);
	pinMode(_en, OUTPUT);
	pinMode(_sa, INPUT);
	pinMode(_sb, INPUT);
    ticks = 0;
 
    
		
}
void digiServo::angle(int a) { 
   
    if(curAngle != a) {
         th = 0;
    ang = abs(double(curAngle - a))/180*PI;
    
    if (a > curAngle) {
        while (th < ang) {       
            track(); 
          
                cclockwise(50);
            
        }
    
    } else {
        while (th > ang) {       
        track();
   
                clockwise(50);

    }
    }
    
    

    analogWrite(_en, 0);
    curAngle = a;
    
    }

}
void digiServo::clockwise(int sp) {
    digitalWrite(_dir, LOW);
    analogWrite(_en, sp);


}
void digiServo::cclockwise(int sp) {
    digitalWrite(_dir, HIGH);
    analogWrite(_en, sp);

}
void digiServo::track() {
    double tim1 = (millis());
    t1 = pulseIn(_sa, HIGH,200000);
    double tim2 = (millis());
    if(t1 != 0){//() && t1 < 3000 && timDiff < 20) {
        t1 = Kalmanfilter(t1, varprocess, varmeasq, t2);
        t2 = t1;
        th += w*(timDiff/1000);
        w = diff / (double(t1)) * 1000000 / 180 * PI;    
    } else {
        w = 0;
    }

    timDiff = tim2 - tim1;

    if(timDiff > 30) 
        timDiff = 0;
}
float digiServo::Kalmanfilter(float val, float varProcess, float varmeas, float prev) {
  Pc = P + varProcess;
  G = Pc / (Pc + varmeas);
  P = (1 - G) * Pc;
  Xp = prev;
  Zp = Xp;
  Xe = G * (val - Zp) + Xp; // Update
   if (double(Xe - val) / double(val) < .05 && Xe > 1400)
    return Xe;
  else
    return val;
}

int digiServo::toDec(bool b, bool a) {

  if (a && b) {
    return 2;
  } else if (!a & !b) {
    return 0;

  } else if (a && !b) {
    return 3;

  } else {
    return 1;
  }
}
int digiServo::trackTicks() {
	
	int a = digitalRead(_sa);
	int b = digitalRead(_sb);
	_prev = _cur;
	_cur = toDec(a,b);

	int diff = _prev - _cur;
    
    switch(diff) {
        case 1:
            ticks = ticks + 1;
            break;
        case -1:
            ticks = ticks - 1;
            break;
        case -3:
            ticks = ticks + 1;
            break;
        case 3:
            ticks = ticks - 1;
            break;
    }
	return ticks;

}