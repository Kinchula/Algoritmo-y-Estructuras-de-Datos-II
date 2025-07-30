#ifndef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include "weather.h"
#include "array_helpers.h"

int temp_hist_min(WeatherTable array);
/*
*	Dado un arreglo del tipo WeatherTable, 
*	analiza el archivo y obtiene la menor temperatura historica registrada.
*	
*	La función retorna la menor temperatura registrada como número entero.
*/

void temp_hist_max(WeatherTable a, int output[YEARS]);
/*
*	Dado un arreglo del tipo WeatherTable tomado como parámetro, el procedimiento registra
*	para cada año la mayo temperatura registrada.
*	El procedimiento retornara en el arreglo de tipo entero, la mayor temperatura
*	registrada por año.
*/

void prec_hist_max(WeatherTable a, month_t output[YEARS]);
/*
*	El procedimiento toma un arreglo del tipo WeatherTable, y para cada año
*	registrara el mes en el que hubo la mayor cantidad de precipitaciones.
*/
#endif
