/*
    FreeRTOS V6.0.0 - Copyright (C) 2009 Real Time Engineers Ltd.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Demo includes. */
#include "basic_io.h"
#include "stdio.h"
#include "stdlib.h"

#define uxTAM_COLA 19 //20 elementos
#define uxTAM_ELEM 4 //el tamanio se expresa en bytes, o sea 4 bytes

/* The task functions. */
void vTask_lectura_sensor( void *pvParameters );
void vTask_entrada_teclado( void *pvParameters );
void vTask_envio_de_dato( void *pvParameters );

/*-----------------------------------------------------------*/
xQueueHandle cola_de_datos;

int main( void )
{
	/* Init the semi-hosting. */
	//printf( "running main.c\n" );
	//Tracealyzer modo snapshot
	vTraceEnable(TRC_START);
	//Tracealyzer modo snapshot
	//vTraceEnable(TRC_INIT);

	/* creacion de la cola de datos */
	//QueueHandle_t cola_de_datos = xQueueCreate((UBaseType_t) uxQUEUE_LEN, (UBaseType_t) uxSIZE_ELEMENT);
	cola_de_datos = xQueueCreate( (unsigned portBASE_TYPE) uxTAM_COLA , (unsigned portBASE_TYPE) uxTAM_ELEM );


	/* creacion de las tareas */
	//LECTURA DE SENSOR
    if (cola_de_datos != NULL){
	xTaskCreate(	vTask_lectura_sensor,		/* Pointer to the function that implements the task. */
					"lectura_sensor",	            /* Text name for the task.  This is to facilitate debugging only. */
					240,		            /* Stack depth in words. */
					NULL,		            /* We are not using the task parameter. */
					2,			            /* This task will run at priority 1. */
					NULL );		            /* We are not using the task handle. */


	//ENTRADA DE TECLADO
	xTaskCreate( 	vTask_entrada_teclado,
				 	"entrada_teclado",
					240,
					NULL,
					3,
					NULL );


	//TRANSMISOR
	xTaskCreate( 	vTask_envio_de_dato, // puntero a la tarea
				 	"TX", // nombre descriptivo opcional
					240, // tamaño del stack de la tarea en palabras (1 palabra = 32bits = 4bytes )
					NULL, // puntero a  void, opcional para recibir parametros en la tarea
					1, // prioridad de la tarea
					NULL ); //identificador de la tarea utilizado para ser eliminada o para cambiar su priorirdad.

	/* Start the scheduler so our tasks start executing. */
	vTaskStartScheduler();
    }
	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
	for( ;; );
	return 0;
}
/*-----------------------------------------------------------*/

void vTask_lectura_sensor( void *pvParameters )
{
volatile unsigned short int usSensorValue ; // dato simulado
volatile char *pcOutput = (char *) pvPortMalloc(5+1+1+2*sizeof(char));//convertir dato a string
volatile unsigned long ul; // simular tiempo de adquisicon de dato
//xQueueHandle cola_de_datos = (xQueueHandle) (*pvParameters);
volatile char *cpElem;
TickType_t xLastWakeTime;
const TickType_t xFrequency = 100; //delay de 100ms - 1 tick = 1 ms

// Initialise the xLastWakeTime variable with the current time.
xLastWakeTime = xTaskGetTickCount();

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		usSensorValue = (unsigned short int) (rand() & 0x000000ff);
		/* Print out the name of this task. */
		sprintf(pcOutput, "[%03u %s]\n", usSensorValue, "deg.C"); //%05u indica que se imprimen 5 digitos de u
 		cpElem = pcOutput;

 		for(ul = 0; ul < 165000; ul++){
 		}

 		for(ul = 0; ul < 12; ul++){
			xQueueSend(cola_de_datos, cpElem++ , portMAX_DELAY);

 		}


		vTaskDelayUntil(&xLastWakeTime, xFrequency); //delay de xFrequency[ms]
	}

	vTaskDelete(NULL);

}
/*------------------------------------------------------------------------------------*/

void vTask_entrada_teclado( void *pvParameters )
{
	unsigned short int usRdelay = 0;
	unsigned short int usNcharacter = 0;
	//15 caracteres + fin de linea + fin de string
	char *pcOutput = (char *) pvPortMalloc(15+1+1*sizeof(char));//convertir dato a string
	char * cElem;
	volatile unsigned long ul; // simular tiempo de adquisicon de dato
	volatile unsigned long uk;
		/* As per most tasks, this task is implemented in an infinite loop. */
		for( ;; )
		{
			usNcharacter = (unsigned short int) (rand() & 0x0000000f);
			usNcharacter = (usNcharacter == 0) ? 1 : usNcharacter;

			for (ul = 0; ul < usNcharacter ; ul++)
			{

				*(pcOutput + ul) = (char) ('A' + (rand() % 25));

				//delay intencional para propositos de analisis
				for(uk = 0; uk < 15000; uk++){
				}
			}



			*(pcOutput + usNcharacter) = '\n';
			/* Print out the name of this task. */
			//sprintf(pcOutput, "%u\n", usSensorValue);
			cElem = pcOutput;
			for(ul = 0; ul < usNcharacter+1; ul++)
			{
				xQueueSend(cola_de_datos, cElem++, portMAX_DELAY);
			}
			//xQueueSend(cola_de_datos, &asd, portMAX_DELAY);
			//vPrintString(pcOutput);
			usRdelay = (unsigned short int) (rand() & 0x000000ff);
			vTaskDelay( usRdelay / portTICK_RATE_MS);
		}

		vTaskDelete(NULL);
}

/*-----------------------------------------------------------------------------------*/

void vTask_envio_de_dato( void *pvParameters )
{
	char *data = (char *) pvPortMalloc(2*sizeof(char));

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		xQueueReceive(cola_de_datos,data,portMAX_DELAY);
		data[1] = '\0';
		vPrintString(data);

		for(unsigned long uk = 0; uk < 11000; uk++){
		}
	}

	vTaskDelete(NULL);

}
/*----------------------------------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}
/*--------------------------------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}
/*----------------------------------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
}
/*---------------------------------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing. */
}


