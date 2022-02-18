// ymacros0.h
#define Y0(t) (1 + m_par[0]*(t))
#define LINEAR_MODEL 0
#define PARAMCOUNT0 1
#define DY0DPAR0(t) (t)
#define D2Y0DPAR0(t) (0)
#define TYPE0INIT1PAR0 0

// ymacros1.h
#define Y1(t) (m_par[0]*exp(-m_par[2]*(t)/m_par[1])/m_par[1])
#define WEIGHT_LAPLACE_FIRST_ORDER_MODEL 1
#define PARAMCOUNT1 3

#define DY1DPAR0(t) (exp(-m_par[2]*(t)/m_par[1])/m_par[1])
#define DY1DPAR1(t) (m_par[0]*m_par[2]*(t)/pow(m_par[1],3)*exp(-m_par[2]*(t)/m_par[1])-m_par[0]*exp(-m_par[2]*(t)/m_par[1])/pow(m_par[1],2))
#define DY1DPAR2(t) (-m_par[0]*(t)/pow(m_par[1],2)*exp(-m_par[2]*(t)/m_par[1]))

#define D2Y1DPAR0(t) (1)
#define D2Y1DPAR1(t) (-4*m_par[0]*m_par[2]*(t)/pow(m_par[1],4)*exp(-m_par[2]*(t)/m_par[1])+m_par[0]*pow(m_par[2],2)*pow((t),2)/pow(m_par[1],5)*exp(-m_par[2]*(t)/m_par[1])+2*m_par[0]*exp(-m_par[2]*(t)/m_par[1])/pow(m_par[1],3))
#define D2Y1DPAR2(t) (m_par[0]*pow((t)^2)/pow(m_par[1],3)*exp(-m_par[2]*(t)/m_par[1]))

#define TYPE1INIT1PAR0 8.5
#define TYPE1INIT1PAR1 5.8
#define TYPE1INIT1PAR2 1.0

#define TYPE1INIT2PAR0 8.0
#define TYPE1INIT2PAR1 3.0
#define TYPE1INIT2PAR2 1.0

// ymacros2.h
#define Y2(t) (m_par[0]*(-1.0/m_par[2]*exp(-m_par[2]*(t)/m_par[1])+1/m_par[2]))
#define TRANSITORY_LAPLACE_FIRST_ORDER_MODEL 2

#define PARAMCOUNT2 3

#define DY2DPAR0(t) (-1.0/m_par[2]*exp(-m_par[2]*(t)/m_par[1])+1.0/m_par[2])
#define DY2DPAR1(t) (-m_par[0]*(t)/pow(m_par[1],2)*exp(-m_par[2]*(t)/m_par[1]))
#define DY2DPAR2(t) (m_par[0]*(1/pow(m_par[2],2)*exp(-m_par[2]*(t)/m_par[1])+1/m_par[2]*(t)/m_par[1]*exp(-m_par[2]*(t)/m_par[1])-1/pow(m_par[2],2)))

#define D2Y2DPAR0(t) (0.1)
#define D2Y2DPAR1(t) (2*m_par[0]*(t)/pow(m_par[1],3)*exp(-m_par[2]*(t)/m_par[1])-m_par[0]*pow((t),2)/pow(m_par[1],4)*m_par[2]*exp(-m_par[2]*(t)/m_par[1]))
#define D2Y2DPAR2(t) (m_par[0]*(-2/pow(m_par[2],3)*exp(-m_par[2]*(t)/m_par[1])-2/pow(m_par[2],2)*(t)/m_par[1]*exp(-m_par[2]*(t)/m_par[1])-1/m_par[2]*pow((t),2)/pow(m_par[1],2)*exp(-m_par[2]*(t)/m_par[1])+2/pow(m_par[2],3)))


#define TYPE2INIT1PAR0 7.4
#define TYPE2INIT1PAR1 3.6
#define TYPE2INIT1PAR2 1.0

#define TYPE2INIT2PAR0 5.0
#define TYPE2INIT2PAR1 3.0
#define TYPE2INIT2PAR2 1.0

// ymacros3.h
#define Y3(t) (1*cos(m_par[0]*(t)-m_par[1]))
#define COS_GARMONIC_MODEL 3


#define PARAMCOUNT3 2

#define DY3DPAR0(t) (-sin(m_par[0]*(t)-m_par[1])*(t))
#define DY3DPAR1(t) (sin(m_par[0]*(t)-m_par[1]))

#define D2Y3DPAR0(t) (-cos(m_par[0]*(t)-m_par[1])*(t)^2)
#define D2Y3DPAR1(t) (-cos(m_par[0]*(t)-m_par[1]))
#define TYPE3INIT1PAR0 1
#define TYPE3INIT1PAR1 1

#define TYPE3INIT2PAR0 10
#define TYPE3INIT2PAR1 0


