##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=BARE2DEngine
ConfigurationName      :=Release
WorkspacePath          :=/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine
ProjectPath            :=/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine
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
OutputFile             :=$(IntermediateDirectory)/lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="BARE2DEngine.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=   -lSDL2 -lSDL2_ttf -lSDL2_mixer -lGL -lGLEW
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Source_InputManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_App.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Screen.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_BAREErrors.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_ScreenList.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Logger.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_BARE2DEngine.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Window.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList)
	@$(MakeDirCommand) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/.build-debug"
	@echo rebuilt > "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/.build-debug/BARE2DEngine"

MakeIntermediateDirs:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)


$(ConfigurationName):
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Source_InputManager.cpp$(ObjectSuffix): Source/InputManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_InputManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_InputManager.cpp$(DependSuffix) -MM Source/InputManager.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/InputManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_InputManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_InputManager.cpp$(PreprocessSuffix): Source/InputManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_InputManager.cpp$(PreprocessSuffix) Source/InputManager.cpp

$(IntermediateDirectory)/Source_App.cpp$(ObjectSuffix): Source/App.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_App.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_App.cpp$(DependSuffix) -MM Source/App.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/App.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_App.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_App.cpp$(PreprocessSuffix): Source/App.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_App.cpp$(PreprocessSuffix) Source/App.cpp

$(IntermediateDirectory)/Source_Screen.cpp$(ObjectSuffix): Source/Screen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Screen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Screen.cpp$(DependSuffix) -MM Source/Screen.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/Screen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Screen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Screen.cpp$(PreprocessSuffix): Source/Screen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Screen.cpp$(PreprocessSuffix) Source/Screen.cpp

$(IntermediateDirectory)/Source_BAREErrors.cpp$(ObjectSuffix): Source/BAREErrors.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_BAREErrors.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_BAREErrors.cpp$(DependSuffix) -MM Source/BAREErrors.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/BAREErrors.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_BAREErrors.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_BAREErrors.cpp$(PreprocessSuffix): Source/BAREErrors.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_BAREErrors.cpp$(PreprocessSuffix) Source/BAREErrors.cpp

$(IntermediateDirectory)/Source_ScreenList.cpp$(ObjectSuffix): Source/ScreenList.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_ScreenList.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_ScreenList.cpp$(DependSuffix) -MM Source/ScreenList.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/ScreenList.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_ScreenList.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_ScreenList.cpp$(PreprocessSuffix): Source/ScreenList.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_ScreenList.cpp$(PreprocessSuffix) Source/ScreenList.cpp

$(IntermediateDirectory)/Source_Logger.cpp$(ObjectSuffix): Source/Logger.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Logger.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Logger.cpp$(DependSuffix) -MM Source/Logger.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/Logger.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Logger.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Logger.cpp$(PreprocessSuffix): Source/Logger.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Logger.cpp$(PreprocessSuffix) Source/Logger.cpp

$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(ObjectSuffix): Source/BARE2DEngine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(DependSuffix) -MM Source/BARE2DEngine.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/BARE2DEngine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(PreprocessSuffix): Source/BARE2DEngine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_BARE2DEngine.cpp$(PreprocessSuffix) Source/BARE2DEngine.cpp

$(IntermediateDirectory)/Source_Window.cpp$(ObjectSuffix): Source/Window.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Window.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Window.cpp$(DependSuffix) -MM Source/Window.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/Window.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Window.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Window.cpp$(PreprocessSuffix): Source/Window.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Window.cpp$(PreprocessSuffix) Source/Window.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


