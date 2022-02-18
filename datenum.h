#if !defined(_DATENUM_FUN_22_)
#define _DATENUM_FUN_22_

double datenum(int y, int mo, int d, int h, int mi, int s)
{
	//cumsum([0;31;28;31;30;31;30;31;31;30;31;30;31])
	int cumdpm[13];
	cumdpm[0] = 0;
	cumdpm[1] = cumdpm[0] + 31;
	cumdpm[2] = cumdpm[1] + 28;
	cumdpm[3] = cumdpm[2] + 31;
	cumdpm[4] = cumdpm[3] + 30;
	cumdpm[5] = cumdpm[4] + 31;
	cumdpm[6] = cumdpm[5] + 30;
	cumdpm[7] = cumdpm[6] + 31;
	cumdpm[8] = cumdpm[7] + 31;
	cumdpm[9] = cumdpm[8] + 30;
	cumdpm[10] = cumdpm[9] + 31;
	cumdpm[11] = cumdpm[10] + 30;
	cumdpm[12] = cumdpm[11] + 31;
	int n;
	n = 365*y +                   // Convert year, month, day to date number
	  (int)ceil((double)y/4.0)-(int)ceil((double)y/100.0)+(int)ceil((double)y/400.0) + cumdpm[mo-1] + 
		((mo > 2) && ((y%4 == 0 && y%100 != 0) || y%400 == 0)) + d;
	double dn;
	int secs;
	if (h!=0 || mi!=0 || s!=0)
	{
		secs = (h*3600+mi*60+s);
		dn = (double)n + ((double)secs)/86400.0;
	}
	else
	{
		secs = 0;
		dn = (double)n;
	}
	return dn;
}
#endif