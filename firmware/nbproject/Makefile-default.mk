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
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
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
SOURCEFILES_QUOTED_IF_SPACED=main.c onewire.c dstemperature.c twi.c tm1637.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/onewire.o ${OBJECTDIR}/dstemperature.o ${OBJECTDIR}/twi.o ${OBJECTDIR}/tm1637.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/onewire.o.d ${OBJECTDIR}/dstemperature.o.d ${OBJECTDIR}/twi.o.d ${OBJECTDIR}/tm1637.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/onewire.o ${OBJECTDIR}/dstemperature.o ${OBJECTDIR}/twi.o ${OBJECTDIR}/tm1637.o

# Source Files
SOURCEFILES=main.c onewire.c dstemperature.c twi.c tm1637.c

# Pack Options 
PACK_COMPILER_OPTIONS=-I "${DFP_DIR}/include"
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/attiny45"



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATtiny45
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/18f599bddb2372a424a592cb1b143801cd7db1d .generated_files/flags/default/12c67fe6cdcd6963bda122da91f9033805394b5f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=attiny45 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o  -o ${OBJECTDIR}/main.o main.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -DF_CPU=8000000UL
	
${OBJECTDIR}/onewire.o: onewire.c  .generated_files/flags/default/cc4122e796c2108754ce016f3c0d3dc9c13879bd .generated_files/flags/default/12c67fe6cdcd6963bda122da91f9033805394b5f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onewire.o.d 
	@${RM} ${OBJECTDIR}/onewire.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=attiny45 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/onewire.o.d" -MT "${OBJECTDIR}/onewire.o.d" -MT ${OBJECTDIR}/onewire.o  -o ${OBJECTDIR}/onewire.o onewire.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -DF_CPU=8000000UL
	
${OBJECTDIR}/dstemperature.o: dstemperature.c  .generated_files/flags/default/69e466464f473642f912549d7526718e2ab8bdd3 .generated_files/flags/default/12c67fe6cdcd6963bda122da91f9033805394b5f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dstemperature.o.d 
	@${RM} ${OBJECTDIR}/dstemperature.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=attiny45 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/dstemperature.o.d" -MT "${OBJECTDIR}/dstemperature.o.d" -MT ${OBJECTDIR}/dstemperature.o  -o ${OBJECTDIR}/dstemperature.o dstemperature.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -DF_CPU=8000000UL
	
${OBJECTDIR}/twi.o: twi.c  .generated_files/flags/default/d596a418b2941f91dfcb39d40e0cfd3f525afd03 .generated_files/flags/default/12c67fe6cdcd6963bda122da91f9033805394b5f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/twi.o.d 
	@${RM} ${OBJECTDIR}/twi.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=attiny45 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/twi.o.d" -MT "${OBJECTDIR}/twi.o.d" -MT ${OBJECTDIR}/twi.o  -o ${OBJECTDIR}/twi.o twi.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -DF_CPU=8000000UL
	
${OBJECTDIR}/tm1637.o: tm1637.c  .generated_files/flags/default/8caab7d1f321339335cad158b786d3a8a151da8d .generated_files/flags/default/12c67fe6cdcd6963bda122da91f9033805394b5f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tm1637.o.d 
	@${RM} ${OBJECTDIR}/tm1637.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=attiny45 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/tm1637.o.d" -MT "${OBJECTDIR}/tm1637.o.d" -MT ${OBJECTDIR}/tm1637.o  -o ${OBJECTDIR}/tm1637.o tm1637.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -DF_CPU=8000000UL
	
else
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/e8b0a82687c5817bdc823aa0198151107a4c0b07 .generated_files/flags/default/12c67fe6cdcd6963bda122da91f9033805394b5f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=attiny45 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o  -o ${OBJECTDIR}/main.o main.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -DF_CPU=8000000UL
	
${OBJECTDIR}/onewire.o: onewire.c  .generated_files/flags/default/47a05aa6e2089994b98fb7a7b4c7fb38d19d902f .generated_files/flags/default/12c67fe6cdcd6963bda122da91f9033805394b5f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onewire.o.d 
	@${RM} ${OBJECTDIR}/onewire.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=attiny45 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/onewire.o.d" -MT "${OBJECTDIR}/onewire.o.d" -MT ${OBJECTDIR}/onewire.o  -o ${OBJECTDIR}/onewire.o onewire.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -DF_CPU=8000000UL
	
${OBJECTDIR}/dstemperature.o: dstemperature.c  .generated_files/flags/default/ddf87487dd00aa036a9a53dff157eefaf70d8f5f .generated_files/flags/default/12c67fe6cdcd6963bda122da91f9033805394b5f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dstemperature.o.d 
	@${RM} ${OBJECTDIR}/dstemperature.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=attiny45 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/dstemperature.o.d" -MT "${OBJECTDIR}/dstemperature.o.d" -MT ${OBJECTDIR}/dstemperature.o  -o ${OBJECTDIR}/dstemperature.o dstemperature.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -DF_CPU=8000000UL
	
${OBJECTDIR}/twi.o: twi.c  .generated_files/flags/default/4301bd1a2a4981da7b459539bb87110266e22c69 .generated_files/flags/default/12c67fe6cdcd6963bda122da91f9033805394b5f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/twi.o.d 
	@${RM} ${OBJECTDIR}/twi.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=attiny45 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/twi.o.d" -MT "${OBJECTDIR}/twi.o.d" -MT ${OBJECTDIR}/twi.o  -o ${OBJECTDIR}/twi.o twi.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -DF_CPU=8000000UL
	
${OBJECTDIR}/tm1637.o: tm1637.c  .generated_files/flags/default/14e85bf2b5c38862ce0be771f34802e5d6a15ad1 .generated_files/flags/default/12c67fe6cdcd6963bda122da91f9033805394b5f
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tm1637.o.d 
	@${RM} ${OBJECTDIR}/tm1637.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=attiny45 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/tm1637.o.d" -MT "${OBJECTDIR}/tm1637.o.d" -MT ${OBJECTDIR}/tm1637.o  -o ${OBJECTDIR}/tm1637.o tm1637.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -DF_CPU=8000000UL
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=attiny45 ${PACK_COMMON_OPTIONS}   -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}/firmware.${IMAGE_TYPE}.map"    -o ${DISTDIR}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  -DF_CPU=8000000UL $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	
	
	${MP_CC_DIR}/avr-objdump -h -S "${DISTDIR}/firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" > "${DISTDIR}/firmware.${IMAGE_TYPE}.lss"
	
	
	
else
${DISTDIR}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=attiny45 ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}/firmware.${IMAGE_TYPE}.map"    -o ${DISTDIR}/firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  -DF_CPU=8000000UL $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}/avr-objcopy -O ihex "${DISTDIR}/firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/firmware.${IMAGE_TYPE}.hex"
	
	${MP_CC_DIR}/avr-objdump -h -S "${DISTDIR}/firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" > "${DISTDIR}/firmware.${IMAGE_TYPE}.lss"
	
	
	
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
