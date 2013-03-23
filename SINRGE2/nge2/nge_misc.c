//#include "nge_debug_log.h"
#include "nge_misc.h"
#include <time.h>

//һЩ���õĹ�������
//����һ��min---max�ĸ�����
float rand_float(float min, float max)
{
	static int g_seed ;
	static int inited = 0;
	if(inited == 0){
		g_seed = time(NULL);
		inited = 1;
	}
	g_seed=214013*g_seed+2531011;
	return min+(g_seed>>16)*(1.0f/65535.0f)*(max-min);
}

//����һ��(min,max)������
int rand_int(int min, int max)
{
	static int g_seed ;
	static int inited = 0;
	if(inited == 0){
		g_seed = time(NULL);
		inited = 1;
	}
	g_seed=214013*g_seed+2531011;
	return min+(g_seed ^ g_seed>>15)%(max-min+1);
}
