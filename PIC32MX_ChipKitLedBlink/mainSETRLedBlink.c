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
int TASK_A_PERIOD = 100;
int TASK_B_PERIOD = 50;
int TASK_C_PERIOD = 20;
#define TASK_A_PERIOD_MS 	( 3000 / portTICK_RATE_MS )
#define TASK_B_PERIOD_MS 	( 2000 / portTICK_RATE_MS )
#define TASK_C_PERIOD_MS 	( 1000 / portTICK_RATE_MS )
#define TASK_TICK_PERIOD_MS 	( 100 / portTICK_RATE_MS )

int TMAN_TICK;      // TASK MANAGER TICK COUNTER
/* Control the load task execution time (# of iterations)*/
/* Each unit corresponds to approx 50 ms*/
#define INTERF_WORKLOAD          ( 20)

/* Priorities of the demo application tasks (high numb. -> high prio.) */
#define TASK_A_PRIORITY	( tskIDLE_PRIORITY + 1 )
#define TASK_B_PRIORITY	    ( tskIDLE_PRIORITY + 1 )
#define TASK_C_PRIORITY  ( tskIDLE_PRIORITY + 1 )
#define TASK_TICK_PRIORITY ( tskIDLE_PRIORITY + 2 )

TaskHandle_t xHandleA;
TaskHandle_t xHandleB;
TaskHandle_t xHandleC;

/* Task Structure */
struct TASK {
   //TickType_t period;
   int period;
   char name;
   int priority;
};

struct TASK TASKS[6];

/*
 * Prototypes and tasks
 */
int getTicks(void);
void task_work(void *pvParam);
void TMAN_Close(void);
void TMAN_TaskAdd(char name);
void TMAN_TaskRegisterAttributes(char name, int period);
void TMAN_TaskWaitPeriod(void *pvParam);
void TMAN_TaskStats(void);
void task_tick_work(void *pvParam);


void TMAN_Init(void)
{

    /* Welcome message*/
    printf("**********************************************\n\r");
    printf("  TMAN - Task Manager framework for FreeRTOS \n\r");
    printf("**********************************************\n\r");
    
    /* Inicialização do Tick */
    TMAN_TICK = 0;
    
    /* Inicialização da tabela de Tasks */
    malloc(sizeof TASKS);
    /*TASKS[0].period = TASK_A_PERIOD_MS;
    TASKS[1].period = TASK_B_PERIOD_MS;    
    TASKS[2].period = TASK_C_PERIOD_MS;     */
    TASKS[0].period = TASK_A_PERIOD_MS;
    TASKS[1].period = TASK_B_PERIOD_MS;    
    TASKS[2].period = TASK_C_PERIOD_MS;
    /* Tick Start */
    xTaskCreate( task_tick_work, ( const signed char * const ) "TICK_TASK", configMINIMAL_STACK_SIZE, NULL, TASK_TICK_PRIORITY, NULL );
    
    //TMAN_Close();
}

void TMAN_Close(void)
{
    // exit
    return 0;
}

void TMAN_TaskAdd(char name)
{
    printf("TASK ADD \n\r");
    /* Create the tasks defined within this file. */
    if (name == 'A'){
        printf("CREATING A \n\r");
        TASKS[0].name = 'A';
        xTaskCreate( task_work, ( const signed char * const ) "task_A", configMINIMAL_STACK_SIZE, (void *)&TASKS[0], TASK_A_PRIORITY, xHandleA );
    }
    if (name == 'B'){
        printf("CREATING B \n\r");
        TASKS[0].name = 'B';
        xTaskCreate( task_work, ( const signed char * const ) "task_B", configMINIMAL_STACK_SIZE, (void *)&TASKS[1], TASK_B_PRIORITY, xHandleB );
    }
    if (name == 'C'){
        printf("CREATING C \n\r");
        TASKS[0].name = 'C';
        xTaskCreate( task_work, ( const signed char * const ) "task_C", configMINIMAL_STACK_SIZE, (void *)&TASKS[2], TASK_C_PRIORITY, xHandleC );
    }
    if (name == 'D'){
        printf("CREATING D \n\r");
        TASKS[0].name = 'D';
        xTaskCreate( task_work, ( const signed char * const ) "task_D", configMINIMAL_STACK_SIZE, (void *)&TASKS[3], TASK_C_PRIORITY, NULL );
    }
    if (name == 'E'){
        printf("CREATING E \n\r");
        TASKS[0].name = 'E';
        xTaskCreate( task_work, ( const signed char * const ) "task_E", configMINIMAL_STACK_SIZE, (void *)&TASKS[4], TASK_C_PRIORITY, NULL );
    }
    if (name == 'F'){
        printf("CREATING F \n\r");
        TASKS[0].name = 'F';
        xTaskCreate( task_work, ( const signed char * const ) "task_F", configMINIMAL_STACK_SIZE, (void *)&TASKS[5], TASK_C_PRIORITY, NULL );
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

void TMAN_TaskWaitPeriod(void *pvParam)
{
    /*struct TASK *working_task;
    working_task =(struct TASK *)pvParam;
    vTaskDelay();*/
    vTaskSuspend(NULL);
}

void TMAN_TaskStats(void)
{

}

void task_tick_work(void *pvParam)
{
    printf("TASK TICK WORK\n\r");
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = TASK_TICK_PERIOD_MS;
    xLastWakeTime = xTaskGetTickCount();
    
    for(;;){
        //rtos_tick = xTaskGetTickCount();
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
        
        TMAN_TICK = TMAN_TICK+1;
        if (TMAN_TICK % 3 == 0){
            vTaskResume(xHandleA);
        }
        if (TMAN_TICK % 3 == 1){
            vTaskResume(xHandleB);
        }
        if (TMAN_TICK % 3 == 2){
            vTaskResume(xHandleC);
        }
            // ACORAR TAREFA
        printf("RTOS_TICK = (%d)\n\r", xLastWakeTime);
        printf("TMAN_TICK = (%d)\n\r", TMAN_TICK);
    }
}


void task_work(void *pvParam)
{
    
    printf("TASK WORK\n\r");
    struct TASK *working_task;
    working_task =(struct TASK *)pvParam;
    
    int i;
    int j;
    int IMAXCOUNT = 99999999;
    int JMAXCOUNT = 99999999;
    
    /*TickType_t xLastWakeTime;
    const TickType_t xFrequency = TASK_A_PERIOD_MS;
    xLastWakeTime = xTaskGetTickCount();*/
    
    for(;;){
        //TMAN_TaskWaitPeriod(args ?); // Add args if needed
        printf("TASK (%c), TMAN_TICK = (%d) \n\r", working_task->name, TMAN_TICK);
                
        /*for(i=0; i<IMAXCOUNT; i++){
            for(j=0; j<JMAXCOUNT; j++){
                
            }
        }*/
        TMAN_TaskWaitPeriod((void *)&working_task);
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
    // Init UART and redirect stdin/stdot/stderr to UART
    if(UartInit(configPERIPHERAL_CLOCK_HZ, 115200) != UART_SUCCESS) {
        PORTAbits.RA3 = 1; // If Led active error initializing UART
        while(1);
    }

    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1*/
    
    TMAN_Init();
    
    printf("AFTER INIT!\n\r");

    TMAN_TaskAdd('A');
    TMAN_TaskAdd('B');
    TMAN_TaskAdd('C');

    //TMAN_TaskRegisterAttributes("A", (3000 / portTICK_RATE_MS));
    //TMAN_TaskRegisterAttributes("B", (2000 / portTICK_RATE_MS));
    //TMAN_TaskRegisterAttributes("C", (1000 / portTICK_RATE_MS));
    
    vTaskStartScheduler();
    
    TMAN_Close();
	
}

