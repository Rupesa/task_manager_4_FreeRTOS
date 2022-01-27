#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-USB-II_STARTER_KIT.mk)" "nbproject/Makefile-local-USB-II_STARTER_KIT.mk"
include nbproject/Makefile-local-USB-II_STARTER_KIT.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=USB-II_STARTER_KIT
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/RTOSDemoChipKitLedBlink.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/RTOSDemoChipKitLedBlink.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../../Source/portable/MPLAB/PIC32MX/port.c ../../../Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Source/queue.c ../../../Source/tasks.c ../../../Source/list.c ../../../Source/timers.c ../../../Source/portable/MemMang/heap_4.c ../main.c ../ConfigPerformance.c ../mainSETRLedBlink.c ../../UART/uart.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/332309696/port.o ${OBJECTDIR}/_ext/332309696/port_asm.o ${OBJECTDIR}/_ext/449926602/queue.o ${OBJECTDIR}/_ext/449926602/tasks.o ${OBJECTDIR}/_ext/449926602/list.o ${OBJECTDIR}/_ext/449926602/timers.o ${OBJECTDIR}/_ext/1884096877/heap_4.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/ConfigPerformance.o ${OBJECTDIR}/_ext/1472/mainSETRLedBlink.o ${OBJECTDIR}/_ext/1852901230/uart.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/332309696/port.o.d ${OBJECTDIR}/_ext/332309696/port_asm.o.d ${OBJECTDIR}/_ext/449926602/queue.o.d ${OBJECTDIR}/_ext/449926602/tasks.o.d ${OBJECTDIR}/_ext/449926602/list.o.d ${OBJECTDIR}/_ext/449926602/timers.o.d ${OBJECTDIR}/_ext/1884096877/heap_4.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/ConfigPerformance.o.d ${OBJECTDIR}/_ext/1472/mainSETRLedBlink.o.d ${OBJECTDIR}/_ext/1852901230/uart.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/332309696/port.o ${OBJECTDIR}/_ext/332309696/port_asm.o ${OBJECTDIR}/_ext/449926602/queue.o ${OBJECTDIR}/_ext/449926602/tasks.o ${OBJECTDIR}/_ext/449926602/list.o ${OBJECTDIR}/_ext/449926602/timers.o ${OBJECTDIR}/_ext/1884096877/heap_4.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/ConfigPerformance.o ${OBJECTDIR}/_ext/1472/mainSETRLedBlink.o ${OBJECTDIR}/_ext/1852901230/uart.o

# Source Files
SOURCEFILES=../../../Source/portable/MPLAB/PIC32MX/port.c ../../../Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Source/queue.c ../../../Source/tasks.c ../../../Source/list.c ../../../Source/timers.c ../../../Source/portable/MemMang/heap_4.c ../main.c ../ConfigPerformance.c ../mainSETRLedBlink.c ../../UART/uart.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-USB-II_STARTER_KIT.mk ${DISTDIR}/RTOSDemoChipKitLedBlink.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/332309696/port_asm.o: ../../../Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/USB-II_STARTER_KIT/24c3890220c0be1224840a101e89487d84a74956 .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/332309696" 
	@${RM} ${OBJECTDIR}/_ext/332309696/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/332309696/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/332309696/port_asm.o.ok ${OBJECTDIR}/_ext/332309696/port_asm.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/332309696/port_asm.o.d"  -o ${OBJECTDIR}/_ext/332309696/port_asm.o ../../../Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/332309696/port_asm.o.asm.d",--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1 -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../ 
	@${FIXDEPS} "${OBJECTDIR}/_ext/332309696/port_asm.o.d" "${OBJECTDIR}/_ext/332309696/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/332309696/port_asm.o: ../../../Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/USB-II_STARTER_KIT/cbba8a73d8f88f42bdbbd98bc156b672835e23d9 .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/332309696" 
	@${RM} ${OBJECTDIR}/_ext/332309696/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/332309696/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/332309696/port_asm.o.ok ${OBJECTDIR}/_ext/332309696/port_asm.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/332309696/port_asm.o.d"  -o ${OBJECTDIR}/_ext/332309696/port_asm.o ../../../Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/332309696/port_asm.o.asm.d",--gdwarf-2 -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../ 
	@${FIXDEPS} "${OBJECTDIR}/_ext/332309696/port_asm.o.d" "${OBJECTDIR}/_ext/332309696/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/332309696/port.o: ../../../Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/USB-II_STARTER_KIT/29434fd49abba53397c962dafbef9ae2fd5d7156 .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/332309696" 
	@${RM} ${OBJECTDIR}/_ext/332309696/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/332309696/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/332309696/port.o.d" -o ${OBJECTDIR}/_ext/332309696/port.o ../../../Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/449926602/queue.o: ../../../Source/queue.c  .generated_files/flags/USB-II_STARTER_KIT/5bf3976628063e5180e8bfec5b340124eab99b01 .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/449926602" 
	@${RM} ${OBJECTDIR}/_ext/449926602/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/449926602/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/449926602/queue.o.d" -o ${OBJECTDIR}/_ext/449926602/queue.o ../../../Source/queue.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/449926602/tasks.o: ../../../Source/tasks.c  .generated_files/flags/USB-II_STARTER_KIT/ff8d34150e6a9ea48725be4cec9d2610863608a4 .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/449926602" 
	@${RM} ${OBJECTDIR}/_ext/449926602/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/449926602/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/449926602/tasks.o.d" -o ${OBJECTDIR}/_ext/449926602/tasks.o ../../../Source/tasks.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/449926602/list.o: ../../../Source/list.c  .generated_files/flags/USB-II_STARTER_KIT/28e8fb6b89bd08efd6c3f06578fbee05b7397b04 .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/449926602" 
	@${RM} ${OBJECTDIR}/_ext/449926602/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/449926602/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/449926602/list.o.d" -o ${OBJECTDIR}/_ext/449926602/list.o ../../../Source/list.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/449926602/timers.o: ../../../Source/timers.c  .generated_files/flags/USB-II_STARTER_KIT/40346eec75ebccc765bfb1fd088d7046d0d6f19f .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/449926602" 
	@${RM} ${OBJECTDIR}/_ext/449926602/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/449926602/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/449926602/timers.o.d" -o ${OBJECTDIR}/_ext/449926602/timers.o ../../../Source/timers.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/1884096877/heap_4.o: ../../../Source/portable/MemMang/heap_4.c  .generated_files/flags/USB-II_STARTER_KIT/e7202d015ec3a41aef2b60f5a89e506a63ecec8e .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/1884096877" 
	@${RM} ${OBJECTDIR}/_ext/1884096877/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1884096877/heap_4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1884096877/heap_4.o.d" -o ${OBJECTDIR}/_ext/1884096877/heap_4.o ../../../Source/portable/MemMang/heap_4.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/USB-II_STARTER_KIT/da2378841b499e6ed074994a25534e64f8f25600 .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/1472/ConfigPerformance.o: ../ConfigPerformance.c  .generated_files/flags/USB-II_STARTER_KIT/973bf40c46fc685bd7fdcd8f5426ca7d409c9f2d .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ConfigPerformance.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ConfigPerformance.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ConfigPerformance.o.d" -o ${OBJECTDIR}/_ext/1472/ConfigPerformance.o ../ConfigPerformance.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/1472/mainSETRLedBlink.o: ../mainSETRLedBlink.c  .generated_files/flags/USB-II_STARTER_KIT/4ad8a60ff247061e834a098139491e366ec229e2 .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/mainSETRLedBlink.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/mainSETRLedBlink.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1472/mainSETRLedBlink.o.d" -o ${OBJECTDIR}/_ext/1472/mainSETRLedBlink.o ../mainSETRLedBlink.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/1852901230/uart.o: ../../UART/uart.c  .generated_files/flags/USB-II_STARTER_KIT/1720e89d5bffb44dbafd7ece7d039f3d4c65a8ce .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/1852901230" 
	@${RM} ${OBJECTDIR}/_ext/1852901230/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1852901230/uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1852901230/uart.o.d" -o ${OBJECTDIR}/_ext/1852901230/uart.o ../../UART/uart.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
else
${OBJECTDIR}/_ext/332309696/port.o: ../../../Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/USB-II_STARTER_KIT/d81deac5cf2dbcdbc127321bd12d0a0953ce2bf2 .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/332309696" 
	@${RM} ${OBJECTDIR}/_ext/332309696/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/332309696/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/332309696/port.o.d" -o ${OBJECTDIR}/_ext/332309696/port.o ../../../Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/449926602/queue.o: ../../../Source/queue.c  .generated_files/flags/USB-II_STARTER_KIT/b9d7abc00146e3cf9b0220370a33122d50449430 .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/449926602" 
	@${RM} ${OBJECTDIR}/_ext/449926602/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/449926602/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/449926602/queue.o.d" -o ${OBJECTDIR}/_ext/449926602/queue.o ../../../Source/queue.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/449926602/tasks.o: ../../../Source/tasks.c  .generated_files/flags/USB-II_STARTER_KIT/d9a1fad9b8dfdee187458c173344f512eee066a .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/449926602" 
	@${RM} ${OBJECTDIR}/_ext/449926602/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/449926602/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/449926602/tasks.o.d" -o ${OBJECTDIR}/_ext/449926602/tasks.o ../../../Source/tasks.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/449926602/list.o: ../../../Source/list.c  .generated_files/flags/USB-II_STARTER_KIT/8dfbf89c639c6a9418eff85b9ff244cbb55c43ec .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/449926602" 
	@${RM} ${OBJECTDIR}/_ext/449926602/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/449926602/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/449926602/list.o.d" -o ${OBJECTDIR}/_ext/449926602/list.o ../../../Source/list.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/449926602/timers.o: ../../../Source/timers.c  .generated_files/flags/USB-II_STARTER_KIT/3752bb58df92e060e7f7c47c92fe866e98aab6cb .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/449926602" 
	@${RM} ${OBJECTDIR}/_ext/449926602/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/449926602/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/449926602/timers.o.d" -o ${OBJECTDIR}/_ext/449926602/timers.o ../../../Source/timers.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/1884096877/heap_4.o: ../../../Source/portable/MemMang/heap_4.c  .generated_files/flags/USB-II_STARTER_KIT/89e3c58be5e89cbd8d6934358aeba9d1afad7456 .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/1884096877" 
	@${RM} ${OBJECTDIR}/_ext/1884096877/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1884096877/heap_4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1884096877/heap_4.o.d" -o ${OBJECTDIR}/_ext/1884096877/heap_4.o ../../../Source/portable/MemMang/heap_4.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/USB-II_STARTER_KIT/ccad272cf85cb02b2fc9f0b01da87e0e7448d34e .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/1472/ConfigPerformance.o: ../ConfigPerformance.c  .generated_files/flags/USB-II_STARTER_KIT/6cb8cc49459fb09fb552d3a97fd842f4b7099313 .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ConfigPerformance.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ConfigPerformance.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ConfigPerformance.o.d" -o ${OBJECTDIR}/_ext/1472/ConfigPerformance.o ../ConfigPerformance.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/1472/mainSETRLedBlink.o: ../mainSETRLedBlink.c  .generated_files/flags/USB-II_STARTER_KIT/7c32337c8c482ed55b826fd151a68eb1bb8fbdc7 .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/mainSETRLedBlink.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/mainSETRLedBlink.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1472/mainSETRLedBlink.o.d" -o ${OBJECTDIR}/_ext/1472/mainSETRLedBlink.o ../mainSETRLedBlink.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
${OBJECTDIR}/_ext/1852901230/uart.o: ../../UART/uart.c  .generated_files/flags/USB-II_STARTER_KIT/e7997b9b1cd80afda1d06db757f779aeca1be408 .generated_files/flags/USB-II_STARTER_KIT/d55f73a18bf11a00a687ff00baaa9b44bb96546
	@${MKDIR} "${OBJECTDIR}/_ext/1852901230" 
	@${RM} ${OBJECTDIR}/_ext/1852901230/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1852901230/uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DPIC32_STARTER_KIT -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1852901230/uart.o.d" -o ${OBJECTDIR}/_ext/1852901230/uart.o ../../UART/uart.c    -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -I ../../../Source/include -I ../../../Source/portable/MPLAB/PIC32MX -I ../../Common/include -I ../   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/RTOSDemoChipKitLedBlink.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_SIMULATOR=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/RTOSDemoChipKitLedBlink.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,--defsym=_min_heap_size=0,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml 
	
else
${DISTDIR}/RTOSDemoChipKitLedBlink.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/RTOSDemoChipKitLedBlink.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_USB-II_STARTER_KIT=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml 
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/RTOSDemoChipKitLedBlink.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
