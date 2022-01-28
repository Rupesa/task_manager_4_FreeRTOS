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

#define TASK_TICK_PERIOD_MS 	( 100 / portTICK_RATE_MS )

int TASK_TICK_PERIOD;
int TMAN_TICK;      // TASK MANAGER TICK COUNTER

/* Control the load task execution time (# of iterations)*/
/* Each unit corresponds to approx 50 ms*/
#define INTERF_WORKLOAD          ( 20)

/* Priorities of the demo application tasks (high numb. -> high prio.) */
#define TASK_A_PRIORITY	( tskIDLE_PRIORITY + 1 )
#define TASK_B_PRIORITY	 ( tskIDLE_PRIORITY + 1 )
#define TASK_C_PRIORITY  ( tskIDLE_PRIORITY + 1 )
#define TASK_D_PRIORITY  ( tskIDLE_PRIORITY + 1 )
#define TASK_E_PRIORITY  ( tskIDLE_PRIORITY + 1 )
#define TASK_F_PRIORITY  ( tskIDLE_PRIORITY + 1 )
#define TASK_TICK_PRIORITY ( tskIDLE_PRIORITY + 2 )

/* Task Structure */
struct TASK {
   //TickType_t period;
   int period;
   char name;
   int priority;
   int tick_counter;
   TaskHandle_t handler;
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


void TMAN_Init(int TMAN_TICK_PERIOD_VALUE)
{

    /* Welcome message*/
    printf("**********************************************\n\r");
    printf("  TMAN - Task Manager framework for FreeRTOS  \n\r");
    printf("**********************************************\n\r");
    
    /* Inicialização do Tick */
    TMAN_TICK = 0;
    TASK_TICK_PERIOD = TMAN_TICK_PERIOD_VALUE;
    
    /* Inicialização da tabela de Tasks */
    malloc(sizeof TASKS);

    /* Tick Start */
    xTaskCreate( task_tick_work, ( const signed char * const ) "TICK_TASK", configMINIMAL_STACK_SIZE, NULL, TASK_TICK_PRIORITY, NULL );
    

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
        TASKS[0].tick_counter = 1;
        xTaskCreate( task_work, ( const signed char * const ) "task_A", configMINIMAL_STACK_SIZE, (void *)&TASKS[0], TASK_A_PRIORITY, &(TASKS[0].handler));
        vTaskSuspend((TASKS[0].handler));
    }
    if (name == 'B'){
        printf("CREATING B \n\r");
        TASKS[1].name = 'B';
        TASKS[1].tick_counter = 1;
        xTaskCreate( task_work, ( const signed char * const ) "task_B", configMINIMAL_STACK_SIZE, (void *)&TASKS[1], TASK_B_PRIORITY, &(TASKS[1].handler) );
        vTaskSuspend((TASKS[1].handler));
    }
    if (name == 'C'){
        printf("CREATING C \n\r");
        TASKS[2].name = 'C';
        TASKS[2].tick_counter = 1;
        xTaskCreate( task_work, ( const signed char * const ) "task_C", configMINIMAL_STACK_SIZE, (void *)&TASKS[2], TASK_C_PRIORITY, &(TASKS[2].handler) );
        vTaskSuspend((TASKS[2].handler));
    }
    if (name == 'D'){
        printf("CREATING D \n\r");
        TASKS[3].name = 'D';
        TASKS[3].tick_counter = 1;
        xTaskCreate( task_work, ( const signed char * const ) "task_D", configMINIMAL_STACK_SIZE, (void *)&TASKS[3], TASK_D_PRIORITY, &(TASKS[3].handler) );
        vTaskSuspend((TASKS[3].handler));
    }
    if (name == 'E'){
        printf("CREATING E \n\r");
        TASKS[4].name = 'E';
        TASKS[4].tick_counter = 1;
        xTaskCreate( task_work, ( const signed char * const ) "task_E", configMINIMAL_STACK_SIZE, (void *)&TASKS[4], TASK_E_PRIORITY, &(TASKS[4].handler) );
        vTaskSuspend((TASKS[4].handler));
    }
    if (name == 'F'){
        printf("CREATING F \n\r");
        TASKS[5].name = 'F';
        TASKS[5].tick_counter = 1;
        xTaskCreate( task_work, ( const signed char * const ) "task_F", configMINIMAL_STACK_SIZE, (void *)&TASKS[5], TASK_F_PRIORITY, &(TASKS[5].handler) );
        vTaskSuspend((TASKS[5].handler));
    }
	
}

void TMAN_TaskRegisterAttributes(char name, int period)
{
    if (name == 'A'){
        TASKS[0].period = period;
    }
    
    if (name == 'B'){
        TASKS[1].period = period;
    }
    
    if (name == 'C'){
        TASKS[2].period = period;
    }
    
    if (name == 'D'){
        TASKS[3].period = period;
    }
    
    if (name == 'E'){
        TASKS[4].period = period;
    }
    
    if (name == 'F'){
        TASKS[5].period = period;
    }
    
    
}

void TMAN_TaskWaitPeriod(void *pvParam)
{
    vTaskSuspend(NULL);
}

void TMAN_TaskStats(void)
{

}

void task_tick_work(void *pvParam)
{
    printf("TASK TICK WORK\n\r");
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = TASK_TICK_PERIOD;
    xLastWakeTime = xTaskGetTickCount();
    
    for(;;){
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
        
        TMAN_TICK = TMAN_TICK+1;
        printf("RTOS_TICK = (%d)\n\r", xLastWakeTime);
        printf("TMAN_TICK = (%d)\n\r", TMAN_TICK);
        
        // ACORAR TAREFA
        int task_to_resume = 0;
        for (task_to_resume = 0; task_to_resume<6; task_to_resume++){
            //printf(" --------- TASK TO RESUME: (%d) \n\r", task_to_resume);
            if (TASKS[task_to_resume].tick_counter == TASKS[task_to_resume].period){
                printf(" --------- TASK (%c) TICK_COUNTER: (%d) \n\r",TASKS[task_to_resume].name, TASKS[task_to_resume].tick_counter);
                vTaskResume((TASKS[task_to_resume].handler));
                TASKS[task_to_resume].tick_counter =1;
                break;
            }
            else{
                //printf(" --------- INCREMENT COUNTER \n\r", task_to_resume);
                TASKS[task_to_resume].tick_counter++;
            }
        }
    }
}


void task_work(void *pvParam)
{

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
    
    TMAN_Init(100);
    
    printf("AFTER INIT!\n\r");

    TMAN_TaskAdd('A');
    TMAN_TaskAdd('B');
    TMAN_TaskAdd('C');
    TMAN_TaskAdd('D');
    TMAN_TaskAdd('E');
    TMAN_TaskAdd('F');

    TMAN_TaskRegisterAttributes('A', 5);
    TMAN_TaskRegisterAttributes('B', 2);
    TMAN_TaskRegisterAttributes('C', 3);
    TMAN_TaskRegisterAttributes('D', 6);
    TMAN_TaskRegisterAttributes('E', 7);
    TMAN_TaskRegisterAttributes('F', 3);
    
    vTaskStartScheduler();
    
    TMAN_Close();
	
}

