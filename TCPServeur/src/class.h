#ifndef CLASS_H
#define CLASS_H
//CPP

class Resolution
{
private:
	int resX;
	int resY;

public:

	Resolution(int a = -1, int b = -1){ resX=a; resY=b;return; }
	~Resolution(){ return; }
	int getX()const{ return resX; };
	int getY()const{ return resY; };
	void setX(int a){ resX = a; };
	void setY(int a){ resY = a; };

	//Overloading
	Resolution operator+(const Resolution &b)const{ return Resolution(resX + b.getX(), resY + b.getY()); };
	Resolution operator-(const Resolution &b)const{ return Resolution(resX - b.getX(), resY - b.getY()); };
	Resolution operator*(const double factor)const{ return Resolution((int)(resX*factor), (int)(resY*factor)); };
	Resolution operator/(const double factor)const{ return Resolution((int)(resX / factor), (int)(resY / factor)); };

};
//
class ResolutionFPS
{
private:
	Resolution res;
	double fps;
public:

	ResolutionFPS(int a = -1, int b = -1, double c = -1) :res(a, b), fps(c){ return; }
	ResolutionFPS(Resolution a, double c = -1) :res(a), fps(c){ return; }
	~ResolutionFPS(){ return; }
	void setRes(Resolution a){ res.setX(a.getX());  res.setY(a.getY()); return; }
	void setRes(int a,int b){ res.setX(a);  res.setY(b); return; }
	void setFps(double a){ fps = a; return; }
	Resolution getRes()const{ return res; };
	double getFps()const{ return fps; };
	//Overloading
	ResolutionFPS operator+(const ResolutionFPS &b)const{ return ResolutionFPS(res + b.getRes(), fps + b.getFps()); };
	ResolutionFPS operator-(const ResolutionFPS &b)const{ return ResolutionFPS(res - b.getRes(), fps - b.getFps()); };
	ResolutionFPS operator*(const double factor)const{ return ResolutionFPS(res*factor, fps*factor); };
	ResolutionFPS operator/(const double factor)const{ return ResolutionFPS(res/factor, fps/factor); };

};

Resolution operator*(const double factor, const Resolution &b);
Resolution operator/(const double factor, const Resolution &b);
ResolutionFPS operator*(const double factor, const ResolutionFPS &b);
ResolutionFPS operator/(const double factor, const ResolutionFPS &b);

#endif


//#ifndef CLASS_H
//#define CLASS_H
//
//class Resolution
//{
//private:
//
//public:
//	int resX;
//	int resY;
//	Resolution(int a=-1 , int b=-1 ):resX(a),resY(b){return;}
//	~Resolution(){return;}
//
//};
//
//class ResolutionFPS
//{
//private:
//
//public:
//	Resolution res;
//	double fps;
//	ResolutionFPS(int a=-1 , int b=-1 , double c=-1):res(a,b),fps(c){return;}
//	~ResolutionFPS(){return;}
//	void set_Res(Resolution a){ res.resX=a.resX; res.resY=a.resY; return;}
//	void set_fps(double a){fps=a; return;}
//
//};
//
//#endif


