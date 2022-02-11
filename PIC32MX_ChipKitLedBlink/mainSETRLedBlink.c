/*
 * Rodrigo Santos , nº mec 89180
 * Rui Santos, nº mec 89293
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

int TASK_TICK_PERIOD; // TICK TASK PERIOD
int TMAN_TICK;        // TMAN TICK COUNTER
int TMAN_N_TASKS;     // NUMBER OF TMAN TASKS
TaskHandle_t TICK_HANDLER; // TASK TICK HANDLER

/* Control the load task execution time (# of iterations)*/
/* Each unit corresponds to approx 50 ms*/
#define INTERF_WORKLOAD          ( 20)

/* Priorities of the demo application tasks (high numb. -> high prio.) */
#define TASK_TICK_PRIORITY ( tskIDLE_PRIORITY + 4 )

/* Task Structure */
struct TASK {
   int period;            // task period
   char name;             // task name
   int priority;          // task priority
   int activations;       // number of activations
   int phase;             // task phase
   int deadline;          // task deadline
   int deadline_misses;   // number of deadline misses
   int ready;             // task executed on current period
   int precedence[5];     // task precedence chain
   TaskHandle_t handler;  // task Handler
};

struct TASK TASKS[6];     // Tasks array
int task_id;              // id for initialization

/*
 * Prototypes
 */
void task_work(void *pvParam);
void TMAN_Close(void);
void TMAN_TaskAdd(char name);
void TMAN_TaskRegisterAttributes(char name, int priority, int period, int phase, int deadline, int precedence_constraints[]);
void TMAN_TaskWaitPeriod(void);
void TMAN_TaskStats(void);
void task_tick_work(void *pvParam);
void task_manager(void);
void taskModifyPeriod(char name, int period);
void taskModifyPhase(char name, int phase);

void TMAN_Init(int TMAN_TICK_PERIOD_VALUE, int N_TASKS)
{

    /* Welcome message*/
    printf("**********************************************\n\r");
    printf("  TMAN - Task Manager framework for FreeRTOS  \n\r");
    printf("**********************************************\n\r");
    
    /* ID para Inicialização */
    task_id = 0;
    
    /* Inicialização do Tick */
    TMAN_TICK = 0;
    TASK_TICK_PERIOD = TMAN_TICK_PERIOD_VALUE;
    
    /* NUMBER OF TASKS TO MANAGE */
    TMAN_N_TASKS = N_TASKS;
    
    /* Inicialização da tabela de Tasks */
    malloc(sizeof TASKS);

    /* Tick Start */
    xTaskCreate( task_tick_work, ( const signed char * const ) "TICK_TASK", configMINIMAL_STACK_SIZE, NULL, TASK_TICK_PRIORITY, &TICK_HANDLER );

}

void taskModifyPeriod(char name, int period){
    
    for(int j = 0; j < TMAN_N_TASKS; j++){
        if (TASKS[j].name == name){
            TASKS[j].period = period;
        }
    }
    
}

void taskModifyPhase(char name, int phase){
    
    for(int j = 0; j < TMAN_N_TASKS; j++){
        if (TASKS[j].name == name){
            TASKS[j].phase = phase;
        }
    }
    
}

void TMAN_Close(void)
{
    /* DELETE TASKS AND EXIT */
    
    for(int i = 0; i < TMAN_N_TASKS; i++){
        vTaskDelete(TASKS[i].handler);
    }
    
    vTaskDelete(TICK_HANDLER);
    vTaskEndScheduler();
    
    return 0;
}

void TMAN_TaskAdd(char name)
{
    /* Create the tasks defined within this file. */
    
    TASKS[task_id].name = name;
    TASKS[task_id].deadline_misses = 0;
    TASKS[task_id].ready = 0;
    TASKS[task_id].activations = 0;
    char task_name[6] = "task";
    task_name[4] = name;
    xTaskCreate( task_work, ( const signed char * const ) task_name, configMINIMAL_STACK_SIZE, (void *)&TASKS[task_id], tskIDLE_PRIORITY, &(TASKS[task_id].handler));
    vTaskSuspend((TASKS[task_id].handler));
    
    task_id++;
    
}

void TMAN_TaskRegisterAttributes(char name, int priority, int period, int phase, int deadline, int precedence_constraints[])
{
    
    for(int j = 0; j < TMAN_N_TASKS; j++){
        if (TASKS[j].name == name){
            TASKS[j].period = period;
            TASKS[j].phase = phase;
            TASKS[j].deadline = deadline;
            TASKS[j].priority = priority;
            vTaskPrioritySet( TASKS[j].handler, TASKS[j].priority );
            for (int i = 0; i<5; i++){
                TASKS[j].precedence[i] = precedence_constraints[i];
            }
        }
    }
}

void TMAN_TaskWaitPeriod(void)
{
    vTaskSuspend(NULL);
}

void TMAN_TaskStats(void)
{
    for(int i = 0; i<6; i++){
        
        printf("TASK (%c) NUMBER OF ACTIVATIONS = (%d)\n\r", TASKS[i].name, TASKS[i].activations);
        printf("TASK (%c) DEADLINE MISSES = (%d)\n\r", TASKS[i].name, TASKS[i].deadline_misses);
        
    }
}

void task_manager(void){
    
    int task_to_resume = 0;
        for (task_to_resume = 0; task_to_resume<TMAN_N_TASKS; task_to_resume++){
            if ((TMAN_TICK % TASKS[task_to_resume].period) == TASKS[task_to_resume].phase) { 
                TASKS[task_to_resume].ready += 1;
                TASKS[task_to_resume].activations += 1;
            }
        }
        
        for (int task = 0; task < TMAN_N_TASKS; task++){
            int dont_executable = 0;
            if (TASKS[task].ready > 0) {
                    for (int i = 0; i<5; i++){
                        if (TASKS[task].precedence[i]!= -1){      
                            if (TASKS[TASKS[task].precedence[i]].ready > 0){ 
                                dont_executable++;
                            }
                        }
                    }
                    if (dont_executable == 0){
                        vTaskResume((TASKS[task].handler));
                    }
            }
            
            if (((TMAN_TICK % TASKS[task].period) == (TASKS[task].deadline) + TASKS[task].phase) &&  (TASKS[task].ready > 0)){
                printf(" --------- TASK (%c) DEADLINE MISS! \n\r", TASKS[task].name);
                TASKS[task].deadline_misses += 1;
            }
        }
    
}

void task_tick_work(void *pvParam)
{
    
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = TASK_TICK_PERIOD;
    xLastWakeTime = xTaskGetTickCount();
    
    for(;;){
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
        TMAN_TaskStats();
        
        TMAN_TICK = TMAN_TICK+1;
        //printf("TMAN_TICK = %d\n\r", TMAN_TICK);
        
        // TASK HANDLING
        task_manager();
    }
}

void task_work(void *pvParam)
{

    struct TASK *working_task;
    working_task =(struct TASK *)pvParam;
    
    int i;
    int j;
    int IMAXCOUNT = 9999;
    //int JMAXCOUNT = 99999999;
    
    for(;;){
                
        for(i=0; i<IMAXCOUNT; i++){
            /*for(j=0; j<JMAXCOUNT; j++){
                
            }*/
        }
        
        printf("%c, %d \n\r", working_task->name, TMAN_TICK);
        
        working_task->ready -= 1;
        TMAN_TaskWaitPeriod();
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
    
    TMAN_Init(300, 6);

    TMAN_TaskAdd('A');
    TMAN_TaskAdd('B');
    TMAN_TaskAdd('C');
    TMAN_TaskAdd('D');
    TMAN_TaskAdd('E');
    TMAN_TaskAdd('F');
    
    int a_precedences[] = {5,-1,-1,-1,-1}; 
    int b_precedences[] = {-1,-1,-1,-1,-1}; 
    int c_precedences[] = {-1,-1,-1,-1,-1}; 
    int d_precedences[] = {-1,-1,-1,-1,-1};
    int e_precedences[] = {-1,-1,-1,-1,-1};
    int f_precedences[] = {-1,-1,-1,-1,-1}; 

    TMAN_TaskRegisterAttributes('A', tskIDLE_PRIORITY + 3, 2, 0, 2, a_precedences);
    TMAN_TaskRegisterAttributes('B', tskIDLE_PRIORITY + 3, 1, 0, 1, b_precedences);
    TMAN_TaskRegisterAttributes('C', tskIDLE_PRIORITY + 2, 3, 0, 3, c_precedences);
    TMAN_TaskRegisterAttributes('D', tskIDLE_PRIORITY + 2, 3, 1, 3, d_precedences);
    TMAN_TaskRegisterAttributes('E', tskIDLE_PRIORITY + 1, 5, 0, 5, e_precedences);
    TMAN_TaskRegisterAttributes('F', tskIDLE_PRIORITY + 1, 5, 2, 5, f_precedences);
    
    vTaskStartScheduler();
    
    TMAN_Close();
	
}

