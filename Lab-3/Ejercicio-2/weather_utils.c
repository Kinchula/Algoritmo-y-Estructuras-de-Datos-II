#include <stdio.h>
#include <stdlib.h>
#include "weather.h"
#include "array_helpers.h"

int temp_hist_min(WeatherTable array) {
	int temperatura = array[0][0][0]._min_temp;
	for(unsigned int year = 0u; year < YEARS; year++) {
		for(unsigned int month = 0u; month < MONTHS; month++) {
			for(unsigned int days = 0u; days < DAYS; days++) {
				if(array[year][month][days]._min_temp < temperatura) {
					temperatura	= array[year][month][days]._min_temp;
				}	
			}
		}
	}
	return temperatura;
}

void temp_hist_max(WeatherTable array, int output[YEARS]) {

	for(unsigned int year = 0u; year < YEARS; year++) {
		int temperatura = array[year][0][0]._max_temp;
		for(unsigned int month = 0u; month < MONTHS; month++) {
			for(unsigned int days = 0u; days < DAYS; days++) {
				if(array[year][month][days]._max_temp > temperatura) {
					temperatura = array[year][month][days]._max_temp;
				}
			}
		}
		output[year] = temperatura;
	}
	
}

void prec_hist_max(WeatherTable array, month_t output[YEARS]) {
	for(unsigned int year = 0u; year < YEARS; year++) {
		unsigned int max_precip = 0u, mes_max_precip = 0u;
		for(unsigned int month = 0u; month < MONTHS; month++) {
			unsigned int precip_acumulada = 0u;
			for(unsigned int days = 0u; days < DAYS; days++) {	
				precip_acumulada += array[year][month][days]._rainfall;
			}
			if(precip_acumulada > max_precip) {
				mes_max_precip = month;
			}
		}
		output[year] = mes_max_precip;
	}
}
