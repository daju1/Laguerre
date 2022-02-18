#if !defined(_Y_MACRO_FUN_256_)
#define _Y_MACRO_FUN_256_

#include "ymacroses.h"

/*double operator^(double a, double b)
{
	double c;
	c=pow(a,b);
	return c;
}*/


// макрос для переопределения в классе модели 
// функции ModelSignalSecondDerivative

double
AllInitPar(int type,int npar,int init)
{
	double InitPar;
	switch(type)
	{
	case 0 : 
		switch(init)
		{
		case 1:
			switch(npar)
			{
			case 0:InitPar=TYPE0INIT1PAR0;break;
			} break;
		} break;
	case 1 : 
		switch(init)
		{
		case 1:
			switch(npar)
			{
			case 0:InitPar=TYPE1INIT1PAR0;break;
			case 1:InitPar=TYPE1INIT1PAR1;break;
			case 2:InitPar=TYPE1INIT1PAR2;break;
			} break;
		case 2:
			switch(npar)
			{
			case 0:InitPar=TYPE1INIT2PAR0;break;
			case 1:InitPar=TYPE1INIT2PAR1;break;
			case 2:InitPar=TYPE1INIT2PAR2;break;
			} break;
		} break;
	case 2 : 
		switch(init)
		{
		case 1:
			switch(npar)
			{
			case 0:InitPar=TYPE2INIT1PAR0;break;
			case 1:InitPar=TYPE2INIT1PAR1;break;
			case 2:InitPar=TYPE2INIT1PAR2;break;
			} break;
		case 2:
			switch(npar)
			{
			case 0:InitPar=TYPE2INIT2PAR0;break;
			case 1:InitPar=TYPE2INIT2PAR1;break;
			case 2:InitPar=TYPE2INIT2PAR2;break;
			} break;
		} break;
	case 3 : 
		switch(init)
		{
		case 1:
			switch(npar)
			{
			case 0:InitPar=TYPE3INIT1PAR0;break;
			case 1:InitPar=TYPE3INIT1PAR1;break;
			} break;
		case 2:
			switch(npar)
			{
			case 0:InitPar=TYPE3INIT2PAR0;break;
			case 1:InitPar=TYPE3INIT2PAR1;break;
			} break;
		} break;
	}
	return InitPar;
};
int
AllParamCount(int _type)
{
	int ParamCount;
	switch(_type)
	{
	case 0 : ParamCount = PARAMCOUNT0; break;
	case 1 : ParamCount = PARAMCOUNT1; break;
	case 2 : ParamCount = PARAMCOUNT2; break;
	case 3 : ParamCount = PARAMCOUNT3; break;
	}
	return ParamCount;
}
#endif