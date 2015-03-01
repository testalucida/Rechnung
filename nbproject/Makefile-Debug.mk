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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1618188523/RechnungGroup.o \
	${OBJECTDIR}/_ext/1618188523/UebersichtTree.o \
	${OBJECTDIR}/src/DetailTabs.o \
	${OBJECTDIR}/src/MainHandler.o \
	${OBJECTDIR}/src/MySql.o \
	${OBJECTDIR}/src/PrintHandler.o \
	${OBJECTDIR}/src/PrintView.o \
	${OBJECTDIR}/src/PrintablePage.o \
	${OBJECTDIR}/src/Rechnung.o \
	${OBJECTDIR}/src/RechnungHandler.o \
	${OBJECTDIR}/src/RechnungIO.o \
	${OBJECTDIR}/src/RechnungPosGroupPrint.o \
	${OBJECTDIR}/src/RechnungTableData.o \
	${OBJECTDIR}/src/RechnungToolBar.o \
	${OBJECTDIR}/src/StatisticIO.o \
	${OBJECTDIR}/src/StatistikHandler.o \
	${OBJECTDIR}/src/TreeHandler.o \
	${OBJECTDIR}/src/UebersichtModel.o \
	${OBJECTDIR}/src/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=`fltk-config --cxxflags` 
CXXFLAGS=`fltk-config --cxxflags` 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/lib -L/usr/local/lib -L../../My_1_5/lib/Debug -L../../fltk-1.3.2/lib -L../Flx_1/lib/Debug -lflx_1 -lmy_1_5 -lfltk_forms -lfltk_images -lfltk_jpeg -lfltk_png

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rechnung2

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rechnung2: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rechnung2 ${OBJECTFILES} ${LDLIBSOPTIONS} `fltk-config --use-images --ldstaticflags` `mysql_config --libs`

${OBJECTDIR}/_ext/1618188523/RechnungGroup.o: /home/max/cpp/fltk/Rechnung2/src/RechnungGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1618188523
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1618188523/RechnungGroup.o /home/max/cpp/fltk/Rechnung2/src/RechnungGroup.cpp

${OBJECTDIR}/_ext/1618188523/UebersichtTree.o: /home/max/cpp/fltk/Rechnung2/src/UebersichtTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1618188523
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1618188523/UebersichtTree.o /home/max/cpp/fltk/Rechnung2/src/UebersichtTree.cpp

${OBJECTDIR}/src/DetailTabs.o: src/DetailTabs.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/DetailTabs.o src/DetailTabs.cpp

${OBJECTDIR}/src/MainHandler.o: src/MainHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/MainHandler.o src/MainHandler.cpp

${OBJECTDIR}/src/MySql.o: src/MySql.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/MySql.o src/MySql.cpp

${OBJECTDIR}/src/PrintHandler.o: src/PrintHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/PrintHandler.o src/PrintHandler.cpp

${OBJECTDIR}/src/PrintView.o: src/PrintView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/PrintView.o src/PrintView.cpp

${OBJECTDIR}/src/PrintablePage.o: src/PrintablePage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/PrintablePage.o src/PrintablePage.cpp

${OBJECTDIR}/src/Rechnung.o: src/Rechnung.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Rechnung.o src/Rechnung.cpp

${OBJECTDIR}/src/RechnungHandler.o: src/RechnungHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/RechnungHandler.o src/RechnungHandler.cpp

${OBJECTDIR}/src/RechnungIO.o: src/RechnungIO.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/RechnungIO.o src/RechnungIO.cpp

${OBJECTDIR}/src/RechnungPosGroupPrint.o: src/RechnungPosGroupPrint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/RechnungPosGroupPrint.o src/RechnungPosGroupPrint.cpp

${OBJECTDIR}/src/RechnungTableData.o: src/RechnungTableData.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/RechnungTableData.o src/RechnungTableData.cpp

${OBJECTDIR}/src/RechnungToolBar.o: src/RechnungToolBar.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/RechnungToolBar.o src/RechnungToolBar.cpp

${OBJECTDIR}/src/StatisticIO.o: src/StatisticIO.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/StatisticIO.o src/StatisticIO.cpp

${OBJECTDIR}/src/StatistikHandler.o: src/StatistikHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/StatistikHandler.o src/StatistikHandler.cpp

${OBJECTDIR}/src/TreeHandler.o: src/TreeHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/TreeHandler.o src/TreeHandler.cpp

${OBJECTDIR}/src/UebersichtModel.o: src/UebersichtModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/UebersichtModel.o src/UebersichtModel.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_TEST_ -I../../fltk-1.3.2 -I../../My_1_5 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rechnung2

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
