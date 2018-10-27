#ifndef CLASS_H
#define CLASS_H

class Resolution
{
private:

public:
	int resX;
	int resY;
	Resolution(int a=-1 , int b=-1 ):resX(a),resY(b){return;}
	~Resolution(){return;}

};

class ResolutionFPS
{
private:

public:
	Resolution res;
	double fps;
	ResolutionFPS(int a=-1 , int b=-1 , double c=-1):res(a,b),fps(c){return;}
	~ResolutionFPS(){return;}
	void set_Res(Resolution a){ res.resX=a.resX; res.resY=a.resY; return;}
	void set_fps(double a){fps=a; return;}

};

#endif

