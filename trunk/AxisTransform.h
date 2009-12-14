//////////////////////////////////////////////////////////////////////////

//the purpose of this head  file is to achieve axis transformation from polar coordinates to Descartes coordinates; edited by xuaimei 
///2009-11-18 first version

//////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;


//implement

double CountDistance(double retime)
{
	const long  CV=299792458;
	double tmpretime;

	tmpretime = CV*(retime)/2;
	return tmpretime;
	
} 

//count longitudinal  theta and azimuth fiy
double CountAngle(double angle1, double angle2)
{
	double temAngle1 = .0f;
	double temAngle2 = .0f;
	temAngle1 = cosf(temAngle1)*cosf(temAngle1);
	temAngle2 = tanf(temAngle2)*tanf(temAngle2);
	
	return sqrtf(1+temAngle1*temAngle2);
}

//normalize the data


void NormalizeData(vector<double> &dx,vector<double> &dy, vector<double> &dz,int length)
{


	double mediumX=0.0;
	double mediumY =0.0;
	double mediumZ = 0.0;
	int i=0;
	mediumX=accumulate(dx.begin(),dx.end(),0.0)/length;
	mediumY= accumulate(dy.begin(),dy.end(),0.0)/length;
	mediumZ = accumulate(dz.begin(),dz.end(),0.0)/length;
	for(i=0;i<length;++i)
	{
		dx[i] = dx[i] - mediumX ;
		dy[i] = dy[i] - mediumY;
		dz[i] = dz[i] - mediumZ;
	
	}
	//使它们到原点的平均距离的平方是1
	double meandis=0;
	for(i=0;i<length;i++)
	{
		meandis+=(float)pow(dx[i]*dx[i]+dy[i]*dy[i]+dz[i]*dz[i],0.5);
	}
	meandis=meandis/length;
	for(i=0;i<length;i++)
	{
		dx[i]=dx[i]/meandis;
		dy[i]=dy[i]/meandis;
		dz[i]=dz[i]/meandis;
	}
	
	
}




