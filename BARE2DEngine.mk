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
Date                   :=22/11/21
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
CXXFLAGS :=  -g -std=c++17 -Wall $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Source_DebugRenderer.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Renderer.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_FontRenderer.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_VAO.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_MutableTexture.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Sound.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_ShaderProgram.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Logger.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Script.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Font.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/Source_Cache.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_BARE2DEngine.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_PicoPNG.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Timer.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_ResourceManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Screen.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_BAREErrors.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_BasicRenderer.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Window.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_App.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/Source_GLContextManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_IOManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_InputManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_ScreenList.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/Source_DebugRenderer.cpp$(ObjectSuffix): Source/DebugRenderer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DebugRenderer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DebugRenderer.cpp$(DependSuffix) -MM Source/DebugRenderer.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/DebugRenderer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_DebugRenderer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DebugRenderer.cpp$(PreprocessSuffix): Source/DebugRenderer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DebugRenderer.cpp$(PreprocessSuffix) Source/DebugRenderer.cpp

$(IntermediateDirectory)/Source_Renderer.cpp$(ObjectSuffix): Source/Renderer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Renderer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Renderer.cpp$(DependSuffix) -MM Source/Renderer.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/Renderer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Renderer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Renderer.cpp$(PreprocessSuffix): Source/Renderer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Renderer.cpp$(PreprocessSuffix) Source/Renderer.cpp

$(IntermediateDirectory)/Source_FontRenderer.cpp$(ObjectSuffix): Source/FontRenderer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_FontRenderer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_FontRenderer.cpp$(DependSuffix) -MM Source/FontRenderer.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/FontRenderer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_FontRenderer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_FontRenderer.cpp$(PreprocessSuffix): Source/FontRenderer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_FontRenderer.cpp$(PreprocessSuffix) Source/FontRenderer.cpp

$(IntermediateDirectory)/Source_VAO.cpp$(ObjectSuffix): Source/VAO.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_VAO.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_VAO.cpp$(DependSuffix) -MM Source/VAO.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/VAO.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_VAO.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_VAO.cpp$(PreprocessSuffix): Source/VAO.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_VAO.cpp$(PreprocessSuffix) Source/VAO.cpp

$(IntermediateDirectory)/Source_MutableTexture.cpp$(ObjectSuffix): Source/MutableTexture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_MutableTexture.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_MutableTexture.cpp$(DependSuffix) -MM Source/MutableTexture.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/MutableTexture.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_MutableTexture.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_MutableTexture.cpp$(PreprocessSuffix): Source/MutableTexture.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_MutableTexture.cpp$(PreprocessSuffix) Source/MutableTexture.cpp

$(IntermediateDirectory)/Source_Sound.cpp$(ObjectSuffix): Source/Sound.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Sound.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Sound.cpp$(DependSuffix) -MM Source/Sound.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/Sound.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Sound.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Sound.cpp$(PreprocessSuffix): Source/Sound.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Sound.cpp$(PreprocessSuffix) Source/Sound.cpp

$(IntermediateDirectory)/Source_ShaderProgram.cpp$(ObjectSuffix): Source/ShaderProgram.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_ShaderProgram.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_ShaderProgram.cpp$(DependSuffix) -MM Source/ShaderProgram.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/ShaderProgram.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_ShaderProgram.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_ShaderProgram.cpp$(PreprocessSuffix): Source/ShaderProgram.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_ShaderProgram.cpp$(PreprocessSuffix) Source/ShaderProgram.cpp

$(IntermediateDirectory)/Source_Logger.cpp$(ObjectSuffix): Source/Logger.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Logger.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Logger.cpp$(DependSuffix) -MM Source/Logger.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/Logger.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Logger.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Logger.cpp$(PreprocessSuffix): Source/Logger.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Logger.cpp$(PreprocessSuffix) Source/Logger.cpp

$(IntermediateDirectory)/Source_Script.cpp$(ObjectSuffix): Source/Script.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Script.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Script.cpp$(DependSuffix) -MM Source/Script.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/Script.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Script.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Script.cpp$(PreprocessSuffix): Source/Script.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Script.cpp$(PreprocessSuffix) Source/Script.cpp

$(IntermediateDirectory)/Source_Font.cpp$(ObjectSuffix): Source/Font.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Font.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Font.cpp$(DependSuffix) -MM Source/Font.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/Font.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Font.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Font.cpp$(PreprocessSuffix): Source/Font.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Font.cpp$(PreprocessSuffix) Source/Font.cpp

$(IntermediateDirectory)/Source_Cache.cpp$(ObjectSuffix): Source/Cache.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Cache.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Cache.cpp$(DependSuffix) -MM Source/Cache.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/Cache.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Cache.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Cache.cpp$(PreprocessSuffix): Source/Cache.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Cache.cpp$(PreprocessSuffix) Source/Cache.cpp

$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(ObjectSuffix): Source/BARE2DEngine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(DependSuffix) -MM Source/BARE2DEngine.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/BARE2DEngine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(PreprocessSuffix): Source/BARE2DEngine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_BARE2DEngine.cpp$(PreprocessSuffix) Source/BARE2DEngine.cpp

$(IntermediateDirectory)/Source_PicoPNG.cpp$(ObjectSuffix): Source/PicoPNG.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_PicoPNG.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_PicoPNG.cpp$(DependSuffix) -MM Source/PicoPNG.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/PicoPNG.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_PicoPNG.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_PicoPNG.cpp$(PreprocessSuffix): Source/PicoPNG.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_PicoPNG.cpp$(PreprocessSuffix) Source/PicoPNG.cpp

$(IntermediateDirectory)/Source_Timer.cpp$(ObjectSuffix): Source/Timer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Timer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Timer.cpp$(DependSuffix) -MM Source/Timer.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/Timer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Timer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Timer.cpp$(PreprocessSuffix): Source/Timer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Timer.cpp$(PreprocessSuffix) Source/Timer.cpp

$(IntermediateDirectory)/Source_ResourceManager.cpp$(ObjectSuffix): Source/ResourceManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_ResourceManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_ResourceManager.cpp$(DependSuffix) -MM Source/ResourceManager.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/ResourceManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_ResourceManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_ResourceManager.cpp$(PreprocessSuffix): Source/ResourceManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_ResourceManager.cpp$(PreprocessSuffix) Source/ResourceManager.cpp

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

$(IntermediateDirectory)/Source_BasicRenderer.cpp$(ObjectSuffix): Source/BasicRenderer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_BasicRenderer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_BasicRenderer.cpp$(DependSuffix) -MM Source/BasicRenderer.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/BasicRenderer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_BasicRenderer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_BasicRenderer.cpp$(PreprocessSuffix): Source/BasicRenderer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_BasicRenderer.cpp$(PreprocessSuffix) Source/BasicRenderer.cpp

$(IntermediateDirectory)/Source_Window.cpp$(ObjectSuffix): Source/Window.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Window.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Window.cpp$(DependSuffix) -MM Source/Window.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/Window.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Window.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Window.cpp$(PreprocessSuffix): Source/Window.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Window.cpp$(PreprocessSuffix) Source/Window.cpp

$(IntermediateDirectory)/Source_App.cpp$(ObjectSuffix): Source/App.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_App.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_App.cpp$(DependSuffix) -MM Source/App.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/App.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_App.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_App.cpp$(PreprocessSuffix): Source/App.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_App.cpp$(PreprocessSuffix) Source/App.cpp

$(IntermediateDirectory)/Source_GLContextManager.cpp$(ObjectSuffix): Source/GLContextManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_GLContextManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_GLContextManager.cpp$(DependSuffix) -MM Source/GLContextManager.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/GLContextManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_GLContextManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_GLContextManager.cpp$(PreprocessSuffix): Source/GLContextManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_GLContextManager.cpp$(PreprocessSuffix) Source/GLContextManager.cpp

$(IntermediateDirectory)/Source_IOManager.cpp$(ObjectSuffix): Source/IOManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_IOManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_IOManager.cpp$(DependSuffix) -MM Source/IOManager.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/IOManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_IOManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_IOManager.cpp$(PreprocessSuffix): Source/IOManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_IOManager.cpp$(PreprocessSuffix) Source/IOManager.cpp

$(IntermediateDirectory)/Source_InputManager.cpp$(ObjectSuffix): Source/InputManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_InputManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_InputManager.cpp$(DependSuffix) -MM Source/InputManager.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/InputManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_InputManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_InputManager.cpp$(PreprocessSuffix): Source/InputManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_InputManager.cpp$(PreprocessSuffix) Source/InputManager.cpp

$(IntermediateDirectory)/Source_ScreenList.cpp$(ObjectSuffix): Source/ScreenList.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_ScreenList.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_ScreenList.cpp$(DependSuffix) -MM Source/ScreenList.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/Source/ScreenList.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_ScreenList.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_ScreenList.cpp$(PreprocessSuffix): Source/ScreenList.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_ScreenList.cpp$(PreprocessSuffix) Source/ScreenList.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


