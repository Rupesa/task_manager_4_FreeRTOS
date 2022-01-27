/*
 * Paulo Pedreiras, Sept/2021
 *
 * FREERTOS demo for ChipKit MAX32 board
 * - Creates two periodic tasks
 * - One toggles Led LD4, other is a long (interfering)task that 
 *      activates LD5 when executing 
 * - When the interfering task has higher priority interference becomes visible
 *      - LD4 does not blink at the right rate
 *
 * Environment:
 * - MPLAB X IDE v5.45
 * - XC32 V2.50
 * - FreeRTOS V202107.00
 *
 *
 */

/* Standard includes. */
#include <stdio.h>
#include <string.h>

#include <xc.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"


/* App includes */
#include "../UART/uart.h"

/* Set the tasks' period (in system ticks) */
int TASK_A_PERIOD = 0;
int TASK_B_PERIOD = 0;
int TASK_C_PERIOD = 0;

int tick = 0;
int rtos_tick_counter;
int TMAN_TICK;
/* Control the load task execution time (# of iterations)*/
/* Each unit corresponds to approx 50 ms*/
#define INTERF_WORKLOAD          ( 20)

/* Priorities of the demo application tasks (high numb. -> high prio.) */
#define TASK_A_PRIORITY	( tskIDLE_PRIORITY + 5 )
#define TASK_B_PRIORITY	    ( tskIDLE_PRIORITY + 5 )
#define TASK_C_PRIORITY  ( tskIDLE_PRIORITY + 5 )
#define TASK_TICK_PRIORITY 99

/*
 * Prototypes and tasks
 */
int getTicks(void);
void task_work(void *pvParam);
void TMAN_Close(void);
void TMAN_TaskAdd(char name);
void TMAN_TaskRegisterAttributes(char name, int period);
void TMAN_TaskWaitPeriod(char name);
void TMAN_TaskStats(void);
void task_tick_work(void *pvParam);


void TMAN_Init(void)
{

    /* Welcome message*/
    printf("\n\n *********************************************\n\r");
    printf("   TMAN - Task Manager framework for FreeRTOS \n\r");
    printf("*********************************************\n\r");
    
    rtos_tick_counter = 0;
    TMAN_TICK = 0;
    xTaskCreate( task_tick_work, ( const signed char * const ) "TICK_TASK", configMINIMAL_STACK_SIZE, NULL, TASK_TICK_PRIORITY, NULL );
    
    /*TMAN_TaskAdd("A");
    TMAN_TaskAdd("B");
    TMAN_TaskAdd("C");

    TMAN_TaskRegisterAttributes("A", (3000 / portTICK_RATE_MS));
    TMAN_TaskRegisterAttributes("B", (2000 / portTICK_RATE_MS));
    TMAN_TaskRegisterAttributes("C", (1000 / portTICK_RATE_MS));*/
    
    TMAN_Close();
}

void TMAN_Close(void)
{
    // exit
    return 0;
}

void TMAN_TaskAdd(char name)
{

    /* Create the tasks defined within this file. */
    if (name == "A"){
        xTaskCreate( task_work, ( const signed char * const ) name, configMINIMAL_STACK_SIZE, NULL, TASK_A_PRIORITY, NULL );
    }
    if (name == "B"){
        xTaskCreate( task_work, ( const signed char * const ) name, configMINIMAL_STACK_SIZE, NULL, TASK_B_PRIORITY, NULL );
    }
    if (name == "C"){
        xTaskCreate( task_work, ( const signed char * const ) name, configMINIMAL_STACK_SIZE, NULL, TASK_C_PRIORITY, NULL );
    }
	
    
}

void TMAN_TaskRegisterAttributes(char name, int period)
{
    if (name == "A"){
        TASK_A_PERIOD = period;
    }
    
    if (name == "B"){
        TASK_B_PERIOD = period;
    }
    
    if (name == "C"){
        TASK_C_PERIOD = period;
    }
    
}

void TMAN_TaskWaitPeriod(char name)
{
    if (name == "A"){
        vTaskDelay(TASK_A_PERIOD);
    }
    
    if (name == "B"){
        vTaskDelay(TASK_B_PERIOD);
    }
    
    if (name == "C"){
        vTaskDelay(TASK_C_PERIOD);
    }
}

void TMAN_TaskStats(void)
{

}


void task_tick_work(void *pvParam)
{
    
    int current_tick = xTaskGetTickCount();
    int rtos_tick;
    
    for(;;){
        rtos_tick = xTaskGetTickCount();
        if (rtos_tick > current_tick)
        {
            current_tick = rtos_tick;
            rtos_tick_counter = rtos_tick_counter +1;
        }
        
        if (rtos_tick_counter == 20)
        {
            TMAN_TICK = TMAN_TICK+1;
            rtos_tick_counter = 0;
            // ACORAR TAREFA
            sprintf("RTOS_TICK = (%d)\n\r", current_tick);
            sprintf("TMAN_TICK = (%d)\n\r", TMAN_TICK);
        }
    }
    
    
}


void task_work(void *pvParam)
{
    
    /*for(;;){
        TMAN_TaskWaitPeriod(args ?); // Add args if needed
        GET_TICKS
        print ?Task Name? and ?Ticks?
        for(i=0; i<IMAXCOUNT; i++)
        for(j=0; j<JMAXCOUNT; j++)
        do_some_computation_to_consume_time;
        OTHER_STUFF (if needed)
        TMAN_TaskWaitPeriod()
    }*/

    int iTaskTicks = 0;
    uint8_t mesg[80];
    
    for(;;) {
        PORTAbits.RA3 = !PORTAbits.RA3;
        sprintf(mesg,"Task LedFlash (job %d)\n\r",iTaskTicks++);
        PrintStr(mesg);
        //vTaskDelay(LED_FLASH_PERIOD_MS);        
    }
}

void pvInterfTask(void *pvParam)
{
    
    volatile uint32_t counter1, counter2;
    float x=100.1;
            
    for(;;) {
        PORTCbits.RC1 = 1;        
        PrintStr("Interfering task release ...");
        
        /* Workload. In this case just spend CPU time ...*/        
        for(counter1=0; counter1 < INTERF_WORKLOAD; counter1++ )
            for(counter2=0; counter2 < 0x10200; counter2++ )
            x=x/3;                

        PrintStr("and termination!\n\r");
        PORTCbits.RC1 = 0;        
        
        //vTaskDelay(INTERF_PERIOD_MS);         
    }
}


/*
 * Create the demo tasks then start the scheduler.
 */
int mainSetrLedBlink( void )
{
    
    // Set RA3 (LD4) and RC1 (LD5) as outputs
    TRISAbits.TRISA3 = 0;
    TRISCbits.TRISC1 = 0;
    PORTAbits.RA3 = 0;
    PORTCbits.RC1 = 0;

	// Init UART and redirect stdin/stdot/stderr to UART
    if(UartInit(configPERIPHERAL_CLOCK_HZ, 115200) != UART_SUCCESS) {
        PORTAbits.RA3 = 1; // If Led active error initializing UART
        while(1);
    }

     __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1*/
    

    /* Finally start the scheduler. */
    TMAN_Init();
	vTaskStartScheduler();

	/* Will only reach here if there is insufficient heap available to start
	the scheduler. */
	
}

