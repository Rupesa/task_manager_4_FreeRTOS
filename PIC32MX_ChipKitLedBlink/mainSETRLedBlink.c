/*
 * Rodrigo Santos , n� mec 89180
 * Rui Santos, n� mec 89293
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

int TASK_TICK_PERIOD;// TICK TASK PERIOD
int TMAN_TICK;       // TASK MANAGER TICK COUNTER
int TMAN_N_TASKS;    // NUMBER OF TMAN TASKS

/* Control the load task execution time (# of iterations)*/
/* Each unit corresponds to approx 50 ms*/
#define INTERF_WORKLOAD          ( 20)

/* Priorities of the demo application tasks (high numb. -> high prio.) */
#define TASK_A_PRIORITY	 ( tskIDLE_PRIORITY + 1 )
#define TASK_B_PRIORITY	 ( tskIDLE_PRIORITY + 1 )
#define TASK_C_PRIORITY  ( tskIDLE_PRIORITY + 1 )
#define TASK_D_PRIORITY  ( tskIDLE_PRIORITY + 1 )
#define TASK_E_PRIORITY  ( tskIDLE_PRIORITY + 1 )
#define TASK_F_PRIORITY  ( tskIDLE_PRIORITY + 1 )
#define TASK_TICK_PRIORITY ( tskIDLE_PRIORITY + 2 )

/* Task Structure */
struct TASK {
   int period;            // task period
   char name;             // task name
   int priority;          // task priority
   int activations;       // number of activations
   int phase;             // task phase
   int deadline;          // task deadline
   int deadline_misses;   // number of deadline misses
   int ready;          // task executed on current period
   int precedence[6];      // task precedence chain
   int goingToExecute;    // flag to signal that task is going to execute this tick
   TaskHandle_t handler;  // task Handler
};

struct TASK TASKS[6];

/*
 * Prototypes and tasks
 */
void task_work(void *pvParam);
void TMAN_Close(void);
void TMAN_TaskAdd(char name);
void TMAN_TaskRegisterAttributes(char name, int period, int phase, int deadline, int precedence_constraints[]);
void TMAN_TaskWaitPeriod(void *pvParam);
void TMAN_TaskStats(void);
void task_tick_work(void *pvParam);
void task_manager(void);

void TMAN_Init(int TMAN_TICK_PERIOD_VALUE, int N_TASKS)
{

    /* Welcome message*/
    printf("**********************************************\n\r");
    printf("  TMAN - Task Manager framework for FreeRTOS  \n\r");
    printf("**********************************************\n\r");
    
    /* Inicializa��o do Tick */
    TMAN_TICK = 0;
    TASK_TICK_PERIOD = TMAN_TICK_PERIOD_VALUE;
    
    /* NUMBER OF TASKS TO MANAGE */
    TMAN_N_TASKS = N_TASKS;
    
    /* Inicializa��o da tabela de Tasks */
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
    /* Create the tasks defined within this file. */
    if (name == 'A'){
        TASKS[0].name = 'A';
        TASKS[0].deadline_misses = 0;
        TASKS[0].ready = 0;
        TASKS[0].goingToExecute = 0;
        TASKS[0].activations = 0;
        xTaskCreate( task_work, ( const signed char * const ) "task_A", configMINIMAL_STACK_SIZE, (void *)&TASKS[0], TASK_A_PRIORITY, &(TASKS[0].handler));
        vTaskSuspend((TASKS[0].handler));
    }
    if (name == 'B'){
        TASKS[1].name = 'B';
        TASKS[1].deadline_misses = 0;
        TASKS[1].ready = 0;
        TASKS[1].goingToExecute = 0;
        TASKS[1].activations = 0;
        xTaskCreate( task_work, ( const signed char * const ) "task_B", configMINIMAL_STACK_SIZE, (void *)&TASKS[1], TASK_B_PRIORITY, &(TASKS[1].handler) );
        vTaskSuspend((TASKS[1].handler));
    }
    if (name == 'C'){
        TASKS[2].name = 'C';
        TASKS[2].deadline_misses = 0;
        TASKS[2].ready = 0;
        TASKS[2].goingToExecute = 0;
        TASKS[2].activations = 0;
        xTaskCreate( task_work, ( const signed char * const ) "task_C", configMINIMAL_STACK_SIZE, (void *)&TASKS[2], TASK_C_PRIORITY, &(TASKS[2].handler) );
        vTaskSuspend((TASKS[2].handler));
    }
    if (name == 'D'){
        TASKS[3].name = 'D';
        TASKS[3].deadline_misses = 0;
        TASKS[3].ready = 0;
        TASKS[3].goingToExecute = 0;
        TASKS[3].activations = 0;
        xTaskCreate( task_work, ( const signed char * const ) "task_D", configMINIMAL_STACK_SIZE, (void *)&TASKS[3], TASK_D_PRIORITY, &(TASKS[3].handler) );
        vTaskSuspend((TASKS[3].handler));
    }
    if (name == 'E'){
        TASKS[4].name = 'E';
        TASKS[4].deadline_misses = 0;
        TASKS[4].ready = 0;
        TASKS[4].goingToExecute = 0;
        TASKS[4].activations = 0;
        xTaskCreate( task_work, ( const signed char * const ) "task_E", configMINIMAL_STACK_SIZE, (void *)&TASKS[4], TASK_E_PRIORITY, &(TASKS[4].handler) );
        vTaskSuspend((TASKS[4].handler));
    }
    if (name == 'F'){
        TASKS[5].name = 'F';
        TASKS[5].deadline_misses = 0;
        TASKS[5].ready = 0;
        TASKS[5].goingToExecute = 0;
        TASKS[5].activations = 0;
        xTaskCreate( task_work, ( const signed char * const ) "task_F", configMINIMAL_STACK_SIZE, (void *)&TASKS[5], TASK_F_PRIORITY, &(TASKS[5].handler) );
        vTaskSuspend((TASKS[5].handler));
    }
}

void TMAN_TaskRegisterAttributes(char name, int period, int phase, int deadline, int precedence_constraints[])
{
    if (name == 'A'){
        TASKS[0].period = period;
        TASKS[0].phase = phase;
        TASKS[0].deadline = deadline;
        for (int i = 0; i<6; i++){
            TASKS[0].precedence[i] = precedence_constraints[i];
        }
    }
    
    if (name == 'B'){
        TASKS[1].period = period;
        TASKS[1].phase = phase;
        TASKS[1].deadline = deadline;
        for (int i = 0; i<6; i++){
            TASKS[1].precedence[i] = precedence_constraints[i];
        }
    }
    
    if (name == 'C'){
        TASKS[2].period = period;
        TASKS[2].phase = phase;
        TASKS[2].deadline = deadline;
        for (int i = 0; i<6; i++){
            TASKS[2].precedence[i] = precedence_constraints[i];
        }
    }
    
    if (name == 'D'){
        TASKS[3].period = period;
        TASKS[3].phase = phase;
        TASKS[3].deadline = deadline;
        for (int i = 0; i<6; i++){
            TASKS[3].precedence[i] = precedence_constraints[i];
        }
    }
    
    if (name == 'E'){
        TASKS[4].period = period;
        TASKS[4].phase = phase;
        TASKS[4].deadline = deadline;
        for (int i = 0; i<6; i++){
            TASKS[4].precedence[i] = precedence_constraints[i];
        }
    }
    
    if (name == 'F'){
        TASKS[5].period = period;
        TASKS[5].phase = phase;
        TASKS[5].deadline = deadline;
        for (int i = 0; i<6; i++){
            TASKS[5].precedence[i] = precedence_constraints[i];
        }
    } 
}

void TMAN_TaskWaitPeriod(void *pvParam)
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
            //printf(" --------- TASK TO RESUME: (%d) \n\r", task_to_resume);
            if ((TMAN_TICK % TASKS[task_to_resume].period) == TASKS[task_to_resume].phase) { 
                TASKS[task_to_resume].ready += 1;
                TASKS[task_to_resume].activations += 1;
            }
        }
        
        for (int task = 0; task < TMAN_N_TASKS; task++){
            int dont_executable = 0;
            if (TASKS[task].ready > 0) {
                    for (int i = 0; i<6; i++){
                        //printf(" -- precedencia id: (%d) \n\r", TASKS[task].precedence[i]);
                        if (TASKS[task].precedence[i]!= -1){
                            //printf(" --------- Precedence exists \n\r");
                            if (TASKS[TASKS[task].precedence[i]].ready > 0){
                                //printf(" --------- INCREMENT EXECUTABLE \n\r");
                                dont_executable++;
                            }
                        }
                    }
                    if (dont_executable == 0){
                        vTaskResume((TASKS[task].handler));
                    }
            }
            /*
            printf("Resto de divisao: %d\n\r", (TMAN_TICK % TASKS[task_to_resume].period))
            printf("Deadline -1 (1): %d\n\r", (TASKS[task].deadline - 1))
            printf("Resto de divisao: %d\n\r", (TMAN_TICK % TASKS[task_to_resume].period)*/
            if (((TMAN_TICK % TASKS[task].period) == (TASKS[task].deadline - 1)) &&  (TASKS[task].ready > 0)){
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
        printf("TMAN_TICK = %d\n\r", TMAN_TICK);
        
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
    int IMAXCOUNT = 999999;
    int JMAXCOUNT = 99999999;
    
    for(;;){
        printf("%c, %d \n\r", working_task->name, TMAN_TICK);
                
        for(i=0; i<IMAXCOUNT; i++){
            /*for(j=0; j<JMAXCOUNT; j++){
                
            }*/
        }
        working_task->ready -= 1;
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
    
    TMAN_Init(500, 6);

    TMAN_TaskAdd('A');
    TMAN_TaskAdd('B');
    TMAN_TaskAdd('C');
    TMAN_TaskAdd('D');
    TMAN_TaskAdd('E');
    TMAN_TaskAdd('F');
    
    int a_precedences[] = {-1,-1,-1,-1,-1,-1}; 
    int b_precedences[] = {2,-1,-1,-1,-1,-1}; 
    int c_precedences[] = {5,-1,-1,-1,-1,-1}; 
    int d_precedences[] = {-1,-1,-1,-1,-1,-1};
    int e_precedences[] = {-1,-1,-1,-1,-1,-1};
    int f_precedences[] = {-1,-1,-1,-1,-1,-1}; 

    TMAN_TaskRegisterAttributes('A', 5, 2, 5, a_precedences);
    TMAN_TaskRegisterAttributes('B', 2, 0, 2, b_precedences);
    TMAN_TaskRegisterAttributes('C', 3, 0, 3, c_precedences);
    TMAN_TaskRegisterAttributes('D', 6, 1, 6, d_precedences);
    TMAN_TaskRegisterAttributes('E', 7, 1, 7, e_precedences);
    TMAN_TaskRegisterAttributes('F', 3, 0, 2, f_precedences);
    
    vTaskStartScheduler();
    
    TMAN_Close();
	
}

