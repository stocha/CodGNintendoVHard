#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin_4.x-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/BitLogicNintendo.o \
	${OBJECTDIR}/BitLogicNintendo2.o \
	${OBJECTDIR}/FirstTry.o \
	${OBJECTDIR}/Normaliser.o \
	${OBJECTDIR}/OfficialEncoder.o \
	${OBJECTDIR}/v5_Formulaz.o \
	${OBJECTDIR}/v5_main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/codgnintendovhard.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/codgnintendovhard.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/codgnintendovhard ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/BitLogicNintendo.o: BitLogicNintendo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BitLogicNintendo.o BitLogicNintendo.cpp

${OBJECTDIR}/BitLogicNintendo2.o: BitLogicNintendo2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BitLogicNintendo2.o BitLogicNintendo2.cpp

${OBJECTDIR}/FirstTry.o: FirstTry.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FirstTry.o FirstTry.cpp

${OBJECTDIR}/Normaliser.o: Normaliser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Normaliser.o Normaliser.cpp

${OBJECTDIR}/OfficialEncoder.o: OfficialEncoder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/OfficialEncoder.o OfficialEncoder.cpp

${OBJECTDIR}/v5_Formulaz.o: v5_Formulaz.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/v5_Formulaz.o v5_Formulaz.cpp

${OBJECTDIR}/v5_main.o: v5_main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/v5_main.o v5_main.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${OBJECTDIR}/BitLogicNintendo_nomain.o: ${OBJECTDIR}/BitLogicNintendo.o BitLogicNintendo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/BitLogicNintendo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BitLogicNintendo_nomain.o BitLogicNintendo.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/BitLogicNintendo.o ${OBJECTDIR}/BitLogicNintendo_nomain.o;\
	fi

${OBJECTDIR}/BitLogicNintendo2_nomain.o: ${OBJECTDIR}/BitLogicNintendo2.o BitLogicNintendo2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/BitLogicNintendo2.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BitLogicNintendo2_nomain.o BitLogicNintendo2.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/BitLogicNintendo2.o ${OBJECTDIR}/BitLogicNintendo2_nomain.o;\
	fi

${OBJECTDIR}/FirstTry_nomain.o: ${OBJECTDIR}/FirstTry.o FirstTry.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/FirstTry.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FirstTry_nomain.o FirstTry.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/FirstTry.o ${OBJECTDIR}/FirstTry_nomain.o;\
	fi

${OBJECTDIR}/Normaliser_nomain.o: ${OBJECTDIR}/Normaliser.o Normaliser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Normaliser.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Normaliser_nomain.o Normaliser.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Normaliser.o ${OBJECTDIR}/Normaliser_nomain.o;\
	fi

${OBJECTDIR}/OfficialEncoder_nomain.o: ${OBJECTDIR}/OfficialEncoder.o OfficialEncoder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/OfficialEncoder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/OfficialEncoder_nomain.o OfficialEncoder.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/OfficialEncoder.o ${OBJECTDIR}/OfficialEncoder_nomain.o;\
	fi

${OBJECTDIR}/v5_Formulaz_nomain.o: ${OBJECTDIR}/v5_Formulaz.o v5_Formulaz.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/v5_Formulaz.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/v5_Formulaz_nomain.o v5_Formulaz.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/v5_Formulaz.o ${OBJECTDIR}/v5_Formulaz_nomain.o;\
	fi

${OBJECTDIR}/v5_main_nomain.o: ${OBJECTDIR}/v5_main.o v5_main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/v5_main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/v5_main_nomain.o v5_main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/v5_main.o ${OBJECTDIR}/v5_main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/codgnintendovhard.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
