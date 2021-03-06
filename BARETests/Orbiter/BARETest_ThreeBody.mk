##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=BARETest_ThreeBody
ConfigurationName      :=Debug
WorkspacePath          :=/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine
ProjectPath            :=/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/Orbiter
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Davis-Dev
Date                   :=13/01/22
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
ObjectsFileList        :="BARETest_ThreeBody.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=   -lSDL2 -lSDL2_ttf -lSDL2_mixer -lGL -lGLEW
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../../Source/ 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)BARE2DEngine $(LibrarySwitch)CEGUIBase-0 $(LibrarySwitch)CEGUIOpenGLRenderer-0 $(LibrarySwitch)lua5.3 
ArLibs                 :=  "libBARE2DEngine.a" "CEGUIBase-0" "CEGUIOpenGLRenderer-0" "lua5.3" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../../Debug/ $(LibraryPathSwitch)/usr/include/x86_64-linux-gnu/cegui-0.8.7/ 

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
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/OrbitScreen.cpp$(ObjectSuffix) $(IntermediateDirectory)/Body.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d "../../.build-debug/BARE2DEngine" $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

"../../.build-debug/BARE2DEngine":
	@$(MakeDirCommand) "../../.build-debug"
	@echo stam > "../../.build-debug/BARE2DEngine"




MakeIntermediateDirs:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)


$(IntermediateDirectory)/.d:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/Orbiter/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/OrbitScreen.cpp$(ObjectSuffix): OrbitScreen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OrbitScreen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/OrbitScreen.cpp$(DependSuffix) -MM OrbitScreen.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/Orbiter/OrbitScreen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/OrbitScreen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OrbitScreen.cpp$(PreprocessSuffix): OrbitScreen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OrbitScreen.cpp$(PreprocessSuffix) OrbitScreen.cpp

$(IntermediateDirectory)/Body.cpp$(ObjectSuffix): Body.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Body.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Body.cpp$(DependSuffix) -MM Body.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/Orbiter/Body.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Body.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Body.cpp$(PreprocessSuffix): Body.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Body.cpp$(PreprocessSuffix) Body.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


