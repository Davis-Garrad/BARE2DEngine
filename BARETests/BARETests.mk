##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=BARETests
ConfigurationName      :=Debug
WorkspacePath          :=/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine
ProjectPath            :=/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Davis-Dev
Date                   :=15/11/21
CodeLitePath           :=/home/davis-dev/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="BARETests.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=   -lSDL2 -lSDL2_ttf -lSDL2_mixer -lGL -lGLEW
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../Source/ 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)BARE2DEngine 
ArLibs                 :=  "libBARE2DEngine.a" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../Release/ 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/TestScreen.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d "../.build-debug/BARE2DEngine" $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

"../.build-debug/BARE2DEngine":
	@$(MakeDirCommand) "../.build-debug"
	@echo stam > "../.build-debug/BARE2DEngine"




MakeIntermediateDirs:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)


$(IntermediateDirectory)/.d:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/TestScreen.cpp$(ObjectSuffix): TestScreen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestScreen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestScreen.cpp$(DependSuffix) -MM TestScreen.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/TestScreen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestScreen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestScreen.cpp$(PreprocessSuffix): TestScreen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestScreen.cpp$(PreprocessSuffix) TestScreen.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


