##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=BARETests
ConfigurationName      :=Release
WorkspaceConfiguration :=All
WorkspacePath          :=/home/davis-dev/Documents/BARE2DEngine
ProjectPath            :=/home/davis-dev/Documents/BARE2DEngine/BARETests/BasicTest
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=
Date                   :=2022-11-23
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
OutputDirectory        :=$(IntermediateDirectory)
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="BARETests.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../../Source/ 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)boost_thread $(LibrarySwitch)boost_filesystem $(LibrarySwitch)boost_system $(LibrarySwitch)lua5.3 $(LibrarySwitch)BARE2DEngine $(LibrarySwitch)CEGUIBase-0 $(LibrarySwitch)CEGUIOpenGLRenderer-0 $(LibrarySwitch)SDL2 $(LibrarySwitch)SDL2_mixer $(LibrarySwitch)SDL2_ttf $(LibrarySwitch)GL $(LibrarySwitch)GLU $(LibrarySwitch)GLEW $(LibrarySwitch)pthread 
ArLibs                 :=  "libboost_thread.a" "libboost_filesystem.a" "libboost_system.a" "lua5.3" "libBARE2DEngine.a" "CEGUIBase-0" "CEGUIOpenGLRenderer-0" "SDL2" "SDL2_mixer" "SDL2_ttf" "GL" "GLU" "GLEW" "pthread" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../../Release/ 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O3 -Wall $(Preprocessors)
CFLAGS   :=  -g -O3 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestScreen.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

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
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/BARETests/BasicTest/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/TestScreen.cpp$(ObjectSuffix): TestScreen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestScreen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestScreen.cpp$(DependSuffix) -MM TestScreen.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/BARETests/BasicTest/TestScreen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestScreen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestScreen.cpp$(PreprocessSuffix): TestScreen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestScreen.cpp$(PreprocessSuffix) TestScreen.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


