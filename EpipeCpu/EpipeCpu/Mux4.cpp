#include "Mux4.h"

void Mux4::into(input a0,input a1,input a2,input a3,input select){
	switch(select.value){
	case 0:
		out = a0;
		break;
	case 1:
		out = a1;
		break;
	case 2:
		out = a2;
		break;
	case 3:
		out = a3;
		break;
	default:
		printf("alub select error !!! \n");
	}
}
