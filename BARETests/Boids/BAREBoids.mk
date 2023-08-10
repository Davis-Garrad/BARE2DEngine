##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=BAREBoids
ConfigurationName      :=Release
WorkspaceConfiguration :=Release
WorkspacePath          :=/home/davis-dev/Documents/Programming/C++/BARE2DEngine
ProjectPath            :=/home/davis-dev/Documents/Programming/C++/BARE2DEngine/BARETests/Boids
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Davis-Dev
Date                   :=03/08/23
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
ObjectsFileList        :="BAREBoids.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../../Source/ $(IncludeSwitch)/usr/include/ 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)BARE2DEngine $(LibrarySwitch)CEGUIBase-0 $(LibrarySwitch)CEGUIOpenGLRenderer-0 $(LibrarySwitch)SDL2 $(LibrarySwitch)SDL2_mixer $(LibrarySwitch)SDL2_ttf $(LibrarySwitch)GL $(LibrarySwitch)GLU $(LibrarySwitch)GLEW $(LibrarySwitch)pthread $(LibrarySwitch)boost_filesystem $(LibrarySwitch)boost_system $(LibrarySwitch)lua5.3 
ArLibs                 :=  "libBARE2DEngine.a" "CEGUIBase-0" "CEGUIOpenGLRenderer-0" "SDL2" "SDL2_mixer" "SDL2_ttf" "GL" "GLU" "GLEW" "pthread" "boost_filesystem" "boost_system" "lua5.3" 
LibPath                := $(LibraryPathSwitch)../../Release/ $(LibraryPathSwitch)/lib/x86_64-linux-gnu 

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
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/AppScreen.cpp$(ObjectSuffix) $(IntermediateDirectory)/Boid.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d "../../.build-release/BARE2DEngine" $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

"../../.build-release/BARE2DEngine":
	@$(MakeDirCommand) "../../.build-release"
	@echo stam > "../../.build-release/BARE2DEngine"




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
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/BARE2DEngine/BARETests/Boids/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/AppScreen.cpp$(ObjectSuffix): AppScreen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/AppScreen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/AppScreen.cpp$(DependSuffix) -MM AppScreen.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/BARE2DEngine/BARETests/Boids/AppScreen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AppScreen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AppScreen.cpp$(PreprocessSuffix): AppScreen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/AppScreen.cpp$(PreprocessSuffix) AppScreen.cpp

$(IntermediateDirectory)/Boid.cpp$(ObjectSuffix): Boid.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Boid.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Boid.cpp$(DependSuffix) -MM Boid.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/BARE2DEngine/BARETests/Boids/Boid.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Boid.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Boid.cpp$(PreprocessSuffix): Boid.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Boid.cpp$(PreprocessSuffix) Boid.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


