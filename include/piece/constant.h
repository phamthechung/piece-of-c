/*
	math and physic constant
	define the world of matter
	edit by Pham The Chung
	create	Septemper 02 2010
	last	Septemper 11 2010
	description
	  + give defination of math and physic constants 
*/
/*
	to use constant_h, must pre-define at least LONG_SIZE in bits
*/
#ifndef __CONSTANT_H
#define __CONSTANT_VERSION	1 /*version*/

#define	ZERO	0
#define UNITY	1
#ifdef __GET_MATH_CONSTANT
/*22 digit*/
#define M_PI	3.14159265358979323846
/* 52 digit */
#define M_PI50	3.14159265358979323846264338327950288419716939937510 
/*37 digit*/
#define M_E		2.71828182845904523536028747135266249
#define M_SQRT_2	1.41421356237309504880168872420969807
#define M_SQRT_3	1.73205080756887729352744634150587236
#define M_SQRT_5	2.23606797749978969640917366873127623

#define M_GELFOND	23.14069263277926 /*e^pi*/
#endif /*MATH*/
/*physic constant*/
#ifdef	__GET_PHYSIC_CONSTANT
#define SYMBOL_MEAN	_ mean power
#define P_G	6.67428x10e-11 /*m^3kg^-1s^-2*/
#define	P_GM	398600.4418
#define P_C	299,792,458
#define	P_AVOGARO	6.0221415x10e23
#define P_Na	P_AVOGARO
#define P_R	8.314472
#define P_T	273.15
/*electron mass*/
#define P_ME	9.10938215x10e-31 /*kg*/
#define P_MP	1.672621637x10e-27 /*kg*/

#define P_E	1.602176487x10e-19 /*C*/
#define P_Ke	8.9875517873861764x10e9 /*N.m^2.C^-2*/
/*planck sector*/
#define P_HPLANCK	6.62606896x10e-34
#define	P_rHPLANCK	1.054571628x10e-34

#define P_LPLANCK	1.616252x10e-35

#define P_HPLANCK_UNIT	J.s
#define	P_LPLANCK_UNIT	m
#define P_TPLANCK_UNIT	s

#define	P_G_UNIT	m_3.kg_-1.s_-2
#define P_GM_UNIT	km_3.s_-2
#define P_C_UNIT	m.s_-1 /*m/s*/
#define P_AVOGARO_UNIT	mol_-1
#define P_R_UNIT	J.K_-1.mol_-1
#define	P_T_UNIT	K

#define P_WATER_DEN_0	999.8395 /*kg.m-3*/
#define P_WATER_DEN_30	995.6502
#define	P_WATER_DEN_N10	998.117
#define P_WATER_DEN_N20	993.547
#define P_WATER_DEN_4	999.9720

#define P_HYDROGEN_DEN	70.99 /*kg.m_-3 @20K*/
#define P_OXYGEN_DEN	1141 /*kg.m_-3*/
#define ONE_COULOMB	6.242x10e18 
#define	ELEMENTATY_CHARGE	1.602176487x10e-19 /*coulombs*/
#endif /*PHYSIC*/

#ifdef	__GET_PLANET_CONSTANT
/*
	earth
	information about solar system planet
*/
#define EARTH_E	0.01671123 /*ecentric*/
#define	EARTH_V	29.78 /*km/s*/
#define	EARTH_RADIUS	6371 /*km*/
#define EARTH_MASS	5.9736x10e24 /*kg*/
#define EARTH_AREA	510,072,000 /*km^2*/
#define EARTH_VOLUME	1.08321x10e12 /*km^3*/
/*two asis of orbit of earth*/
#define EARTH_APHELION	152098232 
#define EARTH_PERIHELION	147098290

#define LUNAR_MASS	7.3477x10e22 /*kg*/
#define LUNAR_E	0.0549
#define LUNAR_RADIUS	1735.1 /*km*/
#define LUNAR_VOLUME	2.1958x10e10 /*km3*/
#define LUNAR_V	1.022 /*km/s*/
#define LUNAR_EV	2.38 /*km/s escape velocity*/
#define	LUNAR_AREA	3.793x10e7 /*km^2*/
#define LUNAR_PERIGEE	363104 /*km*/
#define LUNAR_APOGEE	405696 /*km*/

#define MARS_APHELION	249209300 /*km*/
#define MARS_PERIHELION	206669000 /*km*/
#define MARS_E	0.093315 /*e=f/a*/
#define MARS_MASS	6.4185x10e23 /*kg*/
#define MARS_VOLUME	1.6318x10e11 /*km3*/
#define MARS_RADIUS	3396.2 /*km*/
#define MARS_ESCAPE_VELOCITY	5.027 /*km/s*/
#define MARS_V	24.077 /*km/s*/

#define JUPITER_APHELION	816520800 /*km*/
#define	JUPITER_PERIHELION	740573600
#define	JUPITER_E	0.048775
#define JUPITER_V	13.07 /*km/s*/

#define	URANUS_APHELION	3004419704 /*km*/
#define	URANUS_PERIHELION	2,748,938,461
#define	URANUS_E	0.044405586
#define	URANUS_MASS	8.6810x10e25 /*kg*/
#endif /*planet constant*/

/*============================================================================*/
/*	feature for program and compiler 	*/
/*============================================================================*/
#define CONST_LEN	64
#define	UNIT_LEN	32
/*this type use for static precision*/
#define TYPE_N_BITS	128
/*long size in bit, must define */
#ifndef LONG_SIZE 
#error	"no define LONG_SIZE"
#endif
/*constant of Physic that store in string type
for exactly value
*/
typedef struct {
	char value[CONST_LEN+1];
	char unit[UNIT_LEN+1];
}PHY_CONSTANT;
typedef struct {
	char *s; /*f(x)=sqr(x)+x+1*/
}M_FUNCTION;
/*tell how many size is detemine by type_n 128 bit type*/
typedef struct {
	int n;
	void *s; /*sequence of parameter*/
}PARAMETER;
/*x will resolve two times so define constant will be string*/
#ifndef STR
#define _STR(x)	# x
#define STR(x) _STR(x)
#endif

#ifdef INLINE
inline char *CPYVAL(char *dst,const char *s){
	int len=strlen(s);
	if(len<=CONST_LEN)
	return strncpy(dst,s,len);
	else return NULL;
}
#endif


#endif /*CONTANT*/