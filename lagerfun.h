// lagerfun.h
#if !defined(_LAGERFUN422_)
#define _LAGERFUN422_

double LagerPolynom(const int& n, const double& alpha, const double& beta, const double& t)
{
	switch(n)
	{
	// 2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 0 : return 1.0; break;

	// (1-2*alpha*t)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 1 : return (1.0-2.0*alpha*t); break;

	// (1-4*alpha*t+2*alpha^2*t^2)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 2 : return (1.0-4.0*alpha*t+2.0*pow(alpha*t,2.0)); break;

	// (1-6*alpha*t+6*alpha^2*t^2-4/3*alpha^3*t^3)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 3 : return (1.0-6.0*alpha*t+6.0*pow(alpha*t,2.0)-4.0/3.0*pow(alpha*t,3.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-8*alpha*t+12*alpha^2*t^2-16/3*alpha^3*t^3+2/3*alpha^4*t^4)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 4 : return (1.0-8.0*alpha*t+12.0*pow(alpha*t,2.0)-16.0/3.0*pow(alpha*t,3.0)+2.0/3.0*pow(alpha*t,4.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-10*alpha*t+20*alpha^2*t^2-40/3*alpha^3*t^3+10/3*alpha^4*t^4-4/15*alpha^5*t^5)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 5 : return (1.0-10.0*alpha*t+20.0*pow(alpha*t,2.0)-40.0/3.0*pow(alpha*t,3.0)+10.0/3.0*pow(alpha*t,4.0)-4.0/15.0*pow(alpha*t,5.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-12*alpha*t+30*alpha^2*t^2-80/3*alpha^3*t^3+10*alpha^4*t^4-8/5*alpha^5*t^5+4/45*alpha^6*t^6)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 6 : return (1.0-12.0*alpha*t+30.0*pow(alpha*t,2.0)-80.0/3.0*pow(alpha*t,3.0)+10.0*pow(alpha*t,4.0)-8.0/5.0*pow(alpha*t,5.0)+4.0/45.0*pow(alpha*t,6.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-14*alpha*t+42*alpha^2*t^2-140/3*alpha^3*t^3+70/3*alpha^4*t^4-28/5*alpha^5*t^5+28/45*alpha^6*t^6-8/315*alpha^7*t^7)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 7 : return (1.0-14.0*alpha*t+42.0*pow(alpha*t,2.0)-140.0/3.0*pow(alpha*t,3.0)+70.0/3.0*pow(alpha*t,4.0)-28.0/5.0*pow(alpha*t,5.0)+28.0/45.0*pow(alpha*t,6.0)-8.0/315.0*pow(alpha*t,7.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-16*alpha*t+56*alpha^2*t^2-224/3*alpha^3*t^3+140/3*alpha^4*t^4-224/15*alpha^5*t^5+112/45*alpha^6*t^6-64/315*alpha^7*t^7+2/315*alpha^8*t^8)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 8 : return (1.0-16.0*alpha*t+56.0*pow(alpha*t,2.0)-224.0/3.0*pow(alpha*t,3.0)+140.0/3.0*pow(alpha*t,4.0)-224.0/15.0*pow(alpha*t,5.0)+112.0/45.0*pow(alpha*t,6.0)-64.0/315.0*pow(alpha*t,7.0)+2.0/315.0*pow(alpha*t,8.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-18*alpha*t+72*alpha^2*t^2-112*alpha^3*t^3+84*alpha^4*t^4-168/5*alpha^5*t^5+112/15*alpha^6*t^6-32/35*alpha^7*t^7+2/35*alpha^8*t^8-4/2835*alpha^9*t^9)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 9 : return (1.0-18.0*alpha*t+72.0*pow(alpha*t,2.0)-112.0*pow(alpha*t,3.0)+84.0*pow(alpha*t,4.0)-168.0/5.0*pow(alpha*t,5.0)+112.0/15.0*pow(alpha*t,6.0)-32.0/35.0*pow(alpha*t,7.0)+2.0/35.0*pow(alpha*t,8.0)-4.0/2835.0*pow(alpha*t,9.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-20*alpha*t+90*alpha^2*t^2-160*alpha^3*t^3+140*alpha^4*t^4-336/5*alpha^5*t^5+56/3*alpha^6*t^6-64/21*alpha^7*t^7+2/7*alpha^8*t^8-8/567*alpha^9*t^9+4/14175*alpha^10*t^10)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 10 : return (1.0-20.0*alpha*t+90.0*pow(alpha*t,2.0)-160.0*pow(alpha*t,3.0)+140.0*pow(alpha*t,4.0)-336.0/5.0*pow(alpha*t,5.0)+56.0/3.0*pow(alpha*t,6.0)-64.0/21.0*pow(alpha*t,7.0)+2.0/7.0*pow(alpha*t,8.0)-8.0/567.0*pow(alpha*t,9.0)+4.0/14175.0*pow(alpha*t,10.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-22*alpha*t+110*alpha^2*t^2-220*alpha^3*t^3+220*alpha^4*t^4-616/5*alpha^5*t^5+616/15*alpha^6*t^6-176/21*alpha^7*t^7+22/21*alpha^8*t^8-44/567*alpha^9*t^9+44/14175*alpha^10*t^10-8/155925*alpha^11*t^11)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 11 : return (1.0-22.0*alpha*t+110.0*pow(alpha*t,2.0)-220.0*pow(alpha*t,3.0)+220.0*pow(alpha*t,4.0)-616.0/5.0*pow(alpha*t,5.0)+616.0/15.0*pow(alpha*t,6.0)-176.0/21.0*pow(alpha*t,7.0)+22.0/21.0*pow(alpha*t,8.0)-44.0/567.0*pow(alpha*t,9.0)+44.0/14175.0*pow(alpha*t,10.0)-8.0/155925.0*pow(alpha*t,11.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-24*alpha*t+132*alpha^2*t^2-880/3*alpha^3*t^3+330*alpha^4*t^4-1056/5*alpha^5*t^5+1232/15*alpha^6*t^6-704/35*alpha^7*t^7+22/7*alpha^8*t^8-176/567*alpha^9*t^9+88/4725*alpha^10*t^10-32/51975*alpha^11*t^11+4/467775*alpha^12*t^12)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 12 : return (1.0-24.0*alpha*t+132.0*pow(alpha*t,2.0)-880.0/3.0*pow(alpha*t,3.0)+330.0*pow(alpha*t,4.0)-1056.0/5.0*pow(alpha*t,5.0)+1232.0/15.0*pow(alpha*t,6.0)-704.0/35.0*pow(alpha*t,7.0)+22.0/7.0*pow(alpha*t,8.0)-176.0/567.0*pow(alpha*t,9.0)+88.0/4725.0*pow(alpha*t,10.0)-32.0/51975.0*pow(alpha*t,11.0)+4.0/467775.0*pow(alpha*t,12.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-26*alpha*t+156*alpha^2*t^2-1144/3*alpha^3*t^3+1430/3*alpha^4*t^4-1716/5*alpha^5*t^5+2288/15*alpha^6*t^6-4576/105*alpha^7*t^7+286/35*alpha^8*t^8-572/567*alpha^9*t^9+1144/14175*alpha^10*t^10-208/51975*alpha^11*t^11+52/467775*alpha^12*t^12-8/6081075*alpha^13*t^13)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 13 : return (1.0-26.0*alpha*t+156.0*pow(alpha*t,2.0)-1144.0/3.0*pow(alpha*t,3.0)+1430.0/3.0*pow(alpha*t,4.0)-1716.0/5.0*pow(alpha*t,5.0)+2288.0/15.0*pow(alpha*t,6.0)-4576.0/105.0*pow(alpha*t,7.0)+286.0/35.0*pow(alpha*t,8.0)-572.0/567.0*pow(alpha*t,9.0)+1144.0/14175.0*pow(alpha*t,10.0)-208.0/51975.0*pow(alpha*t,11.0)+52.0/467775.0*pow(alpha*t,12.0)-8.0/6081075.0*pow(alpha*t,13.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-28*alpha*t+182*alpha^2*t^2-1456/3*alpha^3*t^3+2002/3*alpha^4*t^4-8008/15*alpha^5*t^5+4004/15*alpha^6*t^6-9152/105*alpha^7*t^7+286/15*alpha^8*t^8-1144/405*alpha^9*t^9+572/2025*alpha^10*t^10-416/22275*alpha^11*t^11+52/66825*alpha^12*t^12-16/868725*alpha^13*t^13+8/42567525*alpha^14*t^14)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 14 : return (1.0-28.0*alpha*t+182.0*pow(alpha*t,2.0)-1456.0/3.0*pow(alpha*t,3.0)+2002.0/3.0*pow(alpha*t,4.0)-8008.0/15.0*pow(alpha*t,5.0)+4004.0/15.0*pow(alpha*t,6.0)-9152.0/105.0*pow(alpha*t,7.0)+286.0/15.0*pow(alpha*t,8.0)-1144.0/405.0*pow(alpha*t,9.0)+572.0/2025.0*pow(alpha*t,10.0)-416.0/22275.0*pow(alpha*t,11.0)+52.0/66825.0*pow(alpha*t,12.0)-16.0/868725.0*pow(alpha*t,13.0)+8.0/42567525.0*pow(alpha*t,14.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-30*alpha*t+210*alpha^2*t^2-1820/3*alpha^3*t^3+910*alpha^4*t^4-4004/5*alpha^5*t^5+4004/9*alpha^6*t^6-1144/7*alpha^7*t^7+286/7*alpha^8*t^8-572/81*alpha^9*t^9+572/675*alpha^10*t^10-104/1485*alpha^11*t^11+52/13365*alpha^12*t^12-8/57915*alpha^13*t^13+8/2837835*alpha^14*t^14-16/638512875*alpha^15*t^15)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 15 : return (1.0-30.0*alpha*t+210.0*pow(alpha*t,2.0)-1820.0/3.0*pow(alpha*t,3.0)+910.0*pow(alpha*t,4.0)-4004.0/5.0*pow(alpha*t,5.0)+4004.0/9.0*pow(alpha*t,6.0)-1144.0/7.0*pow(alpha*t,7.0)+286.0/7.0*pow(alpha*t,8.0)-572.0/81.0*pow(alpha*t,9.0)+572.0/675.0*pow(alpha*t,10.0)-104.0/1485.0*pow(alpha*t,11.0)+52.0/13365.0*pow(alpha*t,12.0)-8.0/57915.0*pow(alpha*t,13.0)+8.0/2837835.0*pow(alpha*t,14.0)-16.0/638512875.0*pow(alpha*t,15.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-32*alpha*t+240*alpha^2*t^2-2240/3*alpha^3*t^3+3640/3*alpha^4*t^4-5824/5*alpha^5*t^5+32032/45*alpha^6*t^6-18304/63*alpha^7*t^7+572/7*alpha^8*t^8-9152/567*alpha^9*t^9+4576/2025*alpha^10*t^10-1664/7425*alpha^11*t^11+208/13365*alpha^12*t^12-128/173745*alpha^13*t^13+64/2837835*alpha^14*t^14-256/638512875*alpha^15*t^15+2/638512875*alpha^16*t^16)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 16 : return (1.0-32.0*alpha*t+240.0*pow(alpha*t,2.0)-2240.0/3.0*pow(alpha*t,3.0)+3640.0/3.0*pow(alpha*t,4.0)-5824.0/5.0*pow(alpha*t,5.0)+32032.0/45.0*pow(alpha*t,6.0)-18304.0/63.0*pow(alpha*t,7.0)+572.0/7.0*pow(alpha*t,8.0)-9152.0/567.0*pow(alpha*t,9.0)+4576.0/2025.0*pow(alpha*t,10.0)-1664.0/7425.0*pow(alpha*t,11.0)+208.0/13365.0*pow(alpha*t,12.0)-128.0/173745.0*pow(alpha*t,13.0)+64.0/2837835.0*pow(alpha*t,14.0)-256.0/638512875.0*pow(alpha*t,15.0)+2.0/638512875.0*pow(alpha*t,16.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-34*alpha*t+272*alpha^2*t^2-2720/3*alpha^3*t^3+4760/3*alpha^4*t^4-24752/15*alpha^5*t^5+49504/45*alpha^6*t^6-155584/315*alpha^7*t^7+9724/63*alpha^8*t^8-19448/567*alpha^9*t^9+77792/14175*alpha^10*t^10-14144/22275*alpha^11*t^11+3536/66825*alpha^12*t^12-544/173745*alpha^13*t^13+1088/8513505*alpha^14*t^14-2176/638512875*alpha^15*t^15+34/638512875*alpha^16*t^16-4/10854718875*alpha^17*t^17)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 17 : return (1.0-34.0*alpha*t+272.0*pow(alpha*t,2.0)-2720.0/3.0*pow(alpha*t,3.0)+4760.0/3.0*pow(alpha*t,4.0)-24752.0/15.0*pow(alpha*t,5.0)+49504.0/45.0*pow(alpha*t,6.0)-155584.0/315.0*pow(alpha*t,7.0)+9724.0/63.0*pow(alpha*t,8.0)-19448.0/567.0*pow(alpha*t,9.0)+77792.0/14175.0*pow(alpha*t,10.0)-14144.0/22275.0*pow(alpha*t,11.0)+3536.0/66825.0*pow(alpha*t,12.0)-544.0/173745.0*pow(alpha*t,13.0)+1088.0/8513505.0*pow(alpha*t,14.0)-2176.0/638512875.0*pow(alpha*t,15.0)+34.0/638512875.0*pow(alpha*t,16.0)-4.0/10854718875.0*pow(alpha*t,17.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-36*alpha*t+306*alpha^2*t^2-1088*alpha^3*t^3+2040*alpha^4*t^4-11424/5*alpha^5*t^5+24752/15*alpha^6*t^6-28288/35*alpha^7*t^7+9724/35*alpha^8*t^8-38896/567*alpha^9*t^9+19448/1575*alpha^10*t^10-28288/17325*alpha^11*t^11+3536/22275*alpha^12*t^12-1088/96525*alpha^13*t^13+544/945945*alpha^14*t^14-4352/212837625*alpha^15*t^15+34/70945875*alpha^16*t^16-8/1206079875*alpha^17*t^17+4/97692469875*alpha^18*t^18)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 18 : return (1.0-36.0*alpha*t+306.0*pow(alpha*t,2.0)-1088.0*pow(alpha*t,3.0)+2040.0*pow(alpha*t,4.0)-11424.0/5.0*pow(alpha*t,5.0)+24752.0/15.0*pow(alpha*t,6.0)-28288.0/35.0*pow(alpha*t,7.0)+9724.0/35.0*pow(alpha*t,8.0)-38896.0/567.0*pow(alpha*t,9.0)+19448.0/1575.0*pow(alpha*t,10.0)-28288.0/17325.0*pow(alpha*t,11.0)+3536.0/22275.0*pow(alpha*t,12.0)-1088.0/96525.0*pow(alpha*t,13.0)+544.0/945945.0*pow(alpha*t,14.0)-4352.0/212837625.0*pow(alpha*t,15.0)+34.0/70945875.0*pow(alpha*t,16.0)-8.0/1206079875.0*pow(alpha*t,17.0)+4.0/97692469875.0*pow(alpha*t,18.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-38*alpha*t+342*alpha^2*t^2-1292*alpha^3*t^3+2584*alpha^4*t^4-15504/5*alpha^5*t^5+36176/15*alpha^6*t^6-134368/105*alpha^7*t^7+16796/35*alpha^8*t^8-369512/2835*alpha^9*t^9+369512/14175*alpha^10*t^10-67184/17325*alpha^11*t^11+67184/155925*alpha^12*t^12-10336/289575*alpha^13*t^13+10336/4729725*alpha^14*t^14-20672/212837625*alpha^15*t^15+646/212837625*alpha^16*t^16-76/1206079875*alpha^17*t^17+76/97692469875*alpha^18*t^18-8/1856156927625*alpha^19*t^19)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 19 : return (1.0-38.0*alpha*t+342.0*pow(alpha*t,2.0)-1292.0*pow(alpha*t,3.0)+2584.0*pow(alpha*t,4.0)-15504.0/5.0*pow(alpha*t,5.0)+36176.0/15.0*pow(alpha*t,6.0)-134368.0/105.0*pow(alpha*t,7.0)+16796.0/35.0*pow(alpha*t,8.0)-369512.0/2835.0*pow(alpha*t,9.0)+369512.0/14175.0*pow(alpha*t,10.0)-67184.0/17325.0*pow(alpha*t,11.0)+67184.0/155925.0*pow(alpha*t,12.0)-10336.0/289575.0*pow(alpha*t,13.0)+10336.0/4729725.0*pow(alpha*t,14.0)-20672.0/212837625.0*pow(alpha*t,15.0)+646.0/212837625.0*pow(alpha*t,16.0)-76.0/1206079875.0*pow(alpha*t,17.0)+76.0/97692469875.0*pow(alpha*t,18.0)-8.0/1856156927625.0*pow(alpha*t,19.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-40*alpha*t+380*alpha^2*t^2-1520*alpha^3*t^3+3230*alpha^4*t^4-20672/5*alpha^5*t^5+10336/3*alpha^6*t^6-41344/21*alpha^7*t^7+16796/21*alpha^8*t^8-134368/567*alpha^9*t^9+739024/14175*alpha^10*t^10-268736/31185*alpha^11*t^11+33592/31185*alpha^12*t^12-41344/405405*alpha^13*t^13+20672/2837835*alpha^14*t^14-82688/212837625*alpha^15*t^15+646/42567525*alpha^16*t^16-304/723647925*alpha^17*t^17+152/19538493975*alpha^18*t^18-32/371231385525*alpha^19*t^19+4/9280784638125*alpha^20*t^20)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
//	case 20 : return (1.0-40.0*alpha*t+380.0*pow(alpha*t,2.0)-1520.0*pow(alpha*t,3.0)+3230.0*pow(alpha*t,4.0)-20672.0/5.0*pow(alpha*t,5.0)+10336.0/3.0*pow(alpha*t,6.0)-41344.0/21.0*pow(alpha*t,7.0)+16796.0/21.0*pow(alpha*t,8.0)-134368.0/567.0*pow(alpha*t,9.0)+739024.0/14175.0*pow(alpha*t,10.0)-268736.0/31185.0*pow(alpha*t,11.0)+33592.0/31185.0*pow(alpha*t,12.0)-41344.0/405405.0*pow(alpha*t,13.0)+20672.0/2837835.0*pow(alpha*t,14.0)-82688.0/212837625.0*pow(alpha*t,15.0)+646.0/42567525.0*pow(alpha*t,16.0)-304.0/723647925.0*pow(alpha*t,17.0)+152.0/19538493975.0*pow(alpha*t,18.0)-32.0/371231385525.0*pow(alpha*t,19.0)+4.0/9280784638125.0*pow(alpha*t,20.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	}
//	fprintf(stderr, "Error using LagerPolynom() :  order is too large\n");
	return 0;
}

#endif