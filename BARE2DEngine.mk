##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=BARE2DEngine
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :=/home/davis-dev/Documents/Dynasty
ProjectPath            :=/home/davis-dev/Documents/BARE2DEngine
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 :=$(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=
Date                   :=2023-06-14
CodeLitePath           :=/home/davis-dev/.codelite
MakeDirCommand         :=mkdir -p
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
OutputDirectory        :=$(ConfigurationName)
OutputFile             :=$(ConfigurationName)/lib$(ProjectName).a
Preprocessors          :=$(PreprocessorSwitch)DEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  -lboost_filesystem -lboost_system -lSDL2 -lSDL2_ttf -lSDL2_mixer -lGL -lGLEW
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)include $(IncludeSwitch)/usr/include $(IncludeSwitch)/usr/include/x86_64-linux-gnu/cegui-0.8.7/ $(IncludeSwitch)./Other_Libraries 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/lib/x86_64-linux-gnu/ 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
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
Objects0=$(IntermediateDirectory)/Source_BasicRenderer.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_FontRenderer.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_FBORenderer.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_BumpyRenderer.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_TexturelessRenderer.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Font.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_MutableTexture.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_GLContextManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_ShaderProgram.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Window.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/Source_Camera2D.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Vertex.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_VAO.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_LuaScriptQueue.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Logger.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_LuaFunctions.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_BARE2DEngine.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_LuaScript.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_ResourceManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_IOManager.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/Source_InputManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Renderer.cpp$(ObjectSuffix) $(IntermediateDirectory)/Other_Libraries_PicoPNG.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_AudioManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_XMLDataTypes.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Cache.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_ParticleEngine2D.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_LuaScriptEngine.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_XMLDataManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_BARECEGUI.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/Source_Timer.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Filesystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_DebugRenderer.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_Screen.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_ScreenList.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_BAREErrors.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_LuaContextManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/Source_App.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(IntermediateDirectory)/$(OutputFile)

$(IntermediateDirectory)/$(OutputFile): $(Objects)
	@$(MakeDirCommand) "$(IntermediateDirectory)"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList)
	@echo rebuilt > $(IntermediateDirectory)/BARE2DEngine.relink

MakeIntermediateDirs:
	@$(MakeDirCommand) "$(IntermediateDirectory)"
	@$(MakeDirCommand) "$(OutputDirectory)"

$(IntermediateDirectory):
	@$(MakeDirCommand) "$(IntermediateDirectory)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Source_BasicRenderer.cpp$(ObjectSuffix): Source/BasicRenderer.cpp $(IntermediateDirectory)/Source_BasicRenderer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/BasicRenderer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_BasicRenderer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_BasicRenderer.cpp$(DependSuffix): Source/BasicRenderer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_BasicRenderer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_BasicRenderer.cpp$(DependSuffix) -MM Source/BasicRenderer.cpp

$(IntermediateDirectory)/Source_BasicRenderer.cpp$(PreprocessSuffix): Source/BasicRenderer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_BasicRenderer.cpp$(PreprocessSuffix) Source/BasicRenderer.cpp

$(IntermediateDirectory)/Source_FontRenderer.cpp$(ObjectSuffix): Source/FontRenderer.cpp $(IntermediateDirectory)/Source_FontRenderer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/FontRenderer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_FontRenderer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_FontRenderer.cpp$(DependSuffix): Source/FontRenderer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_FontRenderer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_FontRenderer.cpp$(DependSuffix) -MM Source/FontRenderer.cpp

$(IntermediateDirectory)/Source_FontRenderer.cpp$(PreprocessSuffix): Source/FontRenderer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_FontRenderer.cpp$(PreprocessSuffix) Source/FontRenderer.cpp

$(IntermediateDirectory)/Source_FBORenderer.cpp$(ObjectSuffix): Source/FBORenderer.cpp $(IntermediateDirectory)/Source_FBORenderer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/FBORenderer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_FBORenderer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_FBORenderer.cpp$(DependSuffix): Source/FBORenderer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_FBORenderer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_FBORenderer.cpp$(DependSuffix) -MM Source/FBORenderer.cpp

$(IntermediateDirectory)/Source_FBORenderer.cpp$(PreprocessSuffix): Source/FBORenderer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_FBORenderer.cpp$(PreprocessSuffix) Source/FBORenderer.cpp

$(IntermediateDirectory)/Source_BumpyRenderer.cpp$(ObjectSuffix): Source/BumpyRenderer.cpp $(IntermediateDirectory)/Source_BumpyRenderer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/BumpyRenderer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_BumpyRenderer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_BumpyRenderer.cpp$(DependSuffix): Source/BumpyRenderer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_BumpyRenderer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_BumpyRenderer.cpp$(DependSuffix) -MM Source/BumpyRenderer.cpp

$(IntermediateDirectory)/Source_BumpyRenderer.cpp$(PreprocessSuffix): Source/BumpyRenderer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_BumpyRenderer.cpp$(PreprocessSuffix) Source/BumpyRenderer.cpp

$(IntermediateDirectory)/Source_TexturelessRenderer.cpp$(ObjectSuffix): Source/TexturelessRenderer.cpp $(IntermediateDirectory)/Source_TexturelessRenderer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/TexturelessRenderer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_TexturelessRenderer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_TexturelessRenderer.cpp$(DependSuffix): Source/TexturelessRenderer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_TexturelessRenderer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_TexturelessRenderer.cpp$(DependSuffix) -MM Source/TexturelessRenderer.cpp

$(IntermediateDirectory)/Source_TexturelessRenderer.cpp$(PreprocessSuffix): Source/TexturelessRenderer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_TexturelessRenderer.cpp$(PreprocessSuffix) Source/TexturelessRenderer.cpp

$(IntermediateDirectory)/Source_Font.cpp$(ObjectSuffix): Source/Font.cpp $(IntermediateDirectory)/Source_Font.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/Font.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Font.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Font.cpp$(DependSuffix): Source/Font.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Font.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Font.cpp$(DependSuffix) -MM Source/Font.cpp

$(IntermediateDirectory)/Source_Font.cpp$(PreprocessSuffix): Source/Font.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Font.cpp$(PreprocessSuffix) Source/Font.cpp

$(IntermediateDirectory)/Source_MutableTexture.cpp$(ObjectSuffix): Source/MutableTexture.cpp $(IntermediateDirectory)/Source_MutableTexture.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/MutableTexture.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_MutableTexture.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_MutableTexture.cpp$(DependSuffix): Source/MutableTexture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_MutableTexture.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_MutableTexture.cpp$(DependSuffix) -MM Source/MutableTexture.cpp

$(IntermediateDirectory)/Source_MutableTexture.cpp$(PreprocessSuffix): Source/MutableTexture.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_MutableTexture.cpp$(PreprocessSuffix) Source/MutableTexture.cpp

$(IntermediateDirectory)/Source_GLContextManager.cpp$(ObjectSuffix): Source/GLContextManager.cpp $(IntermediateDirectory)/Source_GLContextManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/GLContextManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_GLContextManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_GLContextManager.cpp$(DependSuffix): Source/GLContextManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_GLContextManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_GLContextManager.cpp$(DependSuffix) -MM Source/GLContextManager.cpp

$(IntermediateDirectory)/Source_GLContextManager.cpp$(PreprocessSuffix): Source/GLContextManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_GLContextManager.cpp$(PreprocessSuffix) Source/GLContextManager.cpp

$(IntermediateDirectory)/Source_ShaderProgram.cpp$(ObjectSuffix): Source/ShaderProgram.cpp $(IntermediateDirectory)/Source_ShaderProgram.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/ShaderProgram.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_ShaderProgram.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_ShaderProgram.cpp$(DependSuffix): Source/ShaderProgram.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_ShaderProgram.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_ShaderProgram.cpp$(DependSuffix) -MM Source/ShaderProgram.cpp

$(IntermediateDirectory)/Source_ShaderProgram.cpp$(PreprocessSuffix): Source/ShaderProgram.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_ShaderProgram.cpp$(PreprocessSuffix) Source/ShaderProgram.cpp

$(IntermediateDirectory)/Source_Window.cpp$(ObjectSuffix): Source/Window.cpp $(IntermediateDirectory)/Source_Window.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/Window.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Window.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Window.cpp$(DependSuffix): Source/Window.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Window.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Window.cpp$(DependSuffix) -MM Source/Window.cpp

$(IntermediateDirectory)/Source_Window.cpp$(PreprocessSuffix): Source/Window.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Window.cpp$(PreprocessSuffix) Source/Window.cpp

$(IntermediateDirectory)/Source_Camera2D.cpp$(ObjectSuffix): Source/Camera2D.cpp $(IntermediateDirectory)/Source_Camera2D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/Camera2D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Camera2D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Camera2D.cpp$(DependSuffix): Source/Camera2D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Camera2D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Camera2D.cpp$(DependSuffix) -MM Source/Camera2D.cpp

$(IntermediateDirectory)/Source_Camera2D.cpp$(PreprocessSuffix): Source/Camera2D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Camera2D.cpp$(PreprocessSuffix) Source/Camera2D.cpp

$(IntermediateDirectory)/Source_Vertex.cpp$(ObjectSuffix): Source/Vertex.cpp $(IntermediateDirectory)/Source_Vertex.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/Vertex.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Vertex.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Vertex.cpp$(DependSuffix): Source/Vertex.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Vertex.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Vertex.cpp$(DependSuffix) -MM Source/Vertex.cpp

$(IntermediateDirectory)/Source_Vertex.cpp$(PreprocessSuffix): Source/Vertex.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Vertex.cpp$(PreprocessSuffix) Source/Vertex.cpp

$(IntermediateDirectory)/Source_VAO.cpp$(ObjectSuffix): Source/VAO.cpp $(IntermediateDirectory)/Source_VAO.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/VAO.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_VAO.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_VAO.cpp$(DependSuffix): Source/VAO.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_VAO.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_VAO.cpp$(DependSuffix) -MM Source/VAO.cpp

$(IntermediateDirectory)/Source_VAO.cpp$(PreprocessSuffix): Source/VAO.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_VAO.cpp$(PreprocessSuffix) Source/VAO.cpp

$(IntermediateDirectory)/Source_LuaScriptQueue.cpp$(ObjectSuffix): Source/LuaScriptQueue.cpp $(IntermediateDirectory)/Source_LuaScriptQueue.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/LuaScriptQueue.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_LuaScriptQueue.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_LuaScriptQueue.cpp$(DependSuffix): Source/LuaScriptQueue.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_LuaScriptQueue.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_LuaScriptQueue.cpp$(DependSuffix) -MM Source/LuaScriptQueue.cpp

$(IntermediateDirectory)/Source_LuaScriptQueue.cpp$(PreprocessSuffix): Source/LuaScriptQueue.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_LuaScriptQueue.cpp$(PreprocessSuffix) Source/LuaScriptQueue.cpp

$(IntermediateDirectory)/Source_Logger.cpp$(ObjectSuffix): Source/Logger.cpp $(IntermediateDirectory)/Source_Logger.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/Logger.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Logger.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Logger.cpp$(DependSuffix): Source/Logger.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Logger.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Logger.cpp$(DependSuffix) -MM Source/Logger.cpp

$(IntermediateDirectory)/Source_Logger.cpp$(PreprocessSuffix): Source/Logger.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Logger.cpp$(PreprocessSuffix) Source/Logger.cpp

$(IntermediateDirectory)/Source_LuaFunctions.cpp$(ObjectSuffix): Source/LuaFunctions.cpp $(IntermediateDirectory)/Source_LuaFunctions.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/LuaFunctions.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_LuaFunctions.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_LuaFunctions.cpp$(DependSuffix): Source/LuaFunctions.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_LuaFunctions.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_LuaFunctions.cpp$(DependSuffix) -MM Source/LuaFunctions.cpp

$(IntermediateDirectory)/Source_LuaFunctions.cpp$(PreprocessSuffix): Source/LuaFunctions.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_LuaFunctions.cpp$(PreprocessSuffix) Source/LuaFunctions.cpp

$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(ObjectSuffix): Source/BARE2DEngine.cpp $(IntermediateDirectory)/Source_BARE2DEngine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/BARE2DEngine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(DependSuffix): Source/BARE2DEngine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(DependSuffix) -MM Source/BARE2DEngine.cpp

$(IntermediateDirectory)/Source_BARE2DEngine.cpp$(PreprocessSuffix): Source/BARE2DEngine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_BARE2DEngine.cpp$(PreprocessSuffix) Source/BARE2DEngine.cpp

$(IntermediateDirectory)/Source_LuaScript.cpp$(ObjectSuffix): Source/LuaScript.cpp $(IntermediateDirectory)/Source_LuaScript.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/LuaScript.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_LuaScript.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_LuaScript.cpp$(DependSuffix): Source/LuaScript.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_LuaScript.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_LuaScript.cpp$(DependSuffix) -MM Source/LuaScript.cpp

$(IntermediateDirectory)/Source_LuaScript.cpp$(PreprocessSuffix): Source/LuaScript.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_LuaScript.cpp$(PreprocessSuffix) Source/LuaScript.cpp

$(IntermediateDirectory)/Source_ResourceManager.cpp$(ObjectSuffix): Source/ResourceManager.cpp $(IntermediateDirectory)/Source_ResourceManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/ResourceManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_ResourceManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_ResourceManager.cpp$(DependSuffix): Source/ResourceManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_ResourceManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_ResourceManager.cpp$(DependSuffix) -MM Source/ResourceManager.cpp

$(IntermediateDirectory)/Source_ResourceManager.cpp$(PreprocessSuffix): Source/ResourceManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_ResourceManager.cpp$(PreprocessSuffix) Source/ResourceManager.cpp

$(IntermediateDirectory)/Source_IOManager.cpp$(ObjectSuffix): Source/IOManager.cpp $(IntermediateDirectory)/Source_IOManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/IOManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_IOManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_IOManager.cpp$(DependSuffix): Source/IOManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_IOManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_IOManager.cpp$(DependSuffix) -MM Source/IOManager.cpp

$(IntermediateDirectory)/Source_IOManager.cpp$(PreprocessSuffix): Source/IOManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_IOManager.cpp$(PreprocessSuffix) Source/IOManager.cpp

$(IntermediateDirectory)/Source_InputManager.cpp$(ObjectSuffix): Source/InputManager.cpp $(IntermediateDirectory)/Source_InputManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/InputManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_InputManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_InputManager.cpp$(DependSuffix): Source/InputManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_InputManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_InputManager.cpp$(DependSuffix) -MM Source/InputManager.cpp

$(IntermediateDirectory)/Source_InputManager.cpp$(PreprocessSuffix): Source/InputManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_InputManager.cpp$(PreprocessSuffix) Source/InputManager.cpp

$(IntermediateDirectory)/Source_Renderer.cpp$(ObjectSuffix): Source/Renderer.cpp $(IntermediateDirectory)/Source_Renderer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/Renderer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Renderer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Renderer.cpp$(DependSuffix): Source/Renderer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Renderer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Renderer.cpp$(DependSuffix) -MM Source/Renderer.cpp

$(IntermediateDirectory)/Source_Renderer.cpp$(PreprocessSuffix): Source/Renderer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Renderer.cpp$(PreprocessSuffix) Source/Renderer.cpp

$(IntermediateDirectory)/Other_Libraries_PicoPNG.cpp$(ObjectSuffix): Other_Libraries/PicoPNG.cpp $(IntermediateDirectory)/Other_Libraries_PicoPNG.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Other_Libraries/PicoPNG.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Other_Libraries_PicoPNG.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Other_Libraries_PicoPNG.cpp$(DependSuffix): Other_Libraries/PicoPNG.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Other_Libraries_PicoPNG.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Other_Libraries_PicoPNG.cpp$(DependSuffix) -MM Other_Libraries/PicoPNG.cpp

$(IntermediateDirectory)/Other_Libraries_PicoPNG.cpp$(PreprocessSuffix): Other_Libraries/PicoPNG.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Other_Libraries_PicoPNG.cpp$(PreprocessSuffix) Other_Libraries/PicoPNG.cpp

$(IntermediateDirectory)/Source_AudioManager.cpp$(ObjectSuffix): Source/AudioManager.cpp $(IntermediateDirectory)/Source_AudioManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/AudioManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_AudioManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_AudioManager.cpp$(DependSuffix): Source/AudioManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_AudioManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_AudioManager.cpp$(DependSuffix) -MM Source/AudioManager.cpp

$(IntermediateDirectory)/Source_AudioManager.cpp$(PreprocessSuffix): Source/AudioManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_AudioManager.cpp$(PreprocessSuffix) Source/AudioManager.cpp

$(IntermediateDirectory)/Source_XMLDataTypes.cpp$(ObjectSuffix): Source/XMLDataTypes.cpp $(IntermediateDirectory)/Source_XMLDataTypes.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/XMLDataTypes.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_XMLDataTypes.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_XMLDataTypes.cpp$(DependSuffix): Source/XMLDataTypes.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_XMLDataTypes.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_XMLDataTypes.cpp$(DependSuffix) -MM Source/XMLDataTypes.cpp

$(IntermediateDirectory)/Source_XMLDataTypes.cpp$(PreprocessSuffix): Source/XMLDataTypes.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_XMLDataTypes.cpp$(PreprocessSuffix) Source/XMLDataTypes.cpp

$(IntermediateDirectory)/Source_Cache.cpp$(ObjectSuffix): Source/Cache.cpp $(IntermediateDirectory)/Source_Cache.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/Cache.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Cache.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Cache.cpp$(DependSuffix): Source/Cache.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Cache.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Cache.cpp$(DependSuffix) -MM Source/Cache.cpp

$(IntermediateDirectory)/Source_Cache.cpp$(PreprocessSuffix): Source/Cache.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Cache.cpp$(PreprocessSuffix) Source/Cache.cpp

$(IntermediateDirectory)/Source_ParticleEngine2D.cpp$(ObjectSuffix): Source/ParticleEngine2D.cpp $(IntermediateDirectory)/Source_ParticleEngine2D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/ParticleEngine2D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_ParticleEngine2D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_ParticleEngine2D.cpp$(DependSuffix): Source/ParticleEngine2D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_ParticleEngine2D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_ParticleEngine2D.cpp$(DependSuffix) -MM Source/ParticleEngine2D.cpp

$(IntermediateDirectory)/Source_ParticleEngine2D.cpp$(PreprocessSuffix): Source/ParticleEngine2D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_ParticleEngine2D.cpp$(PreprocessSuffix) Source/ParticleEngine2D.cpp

$(IntermediateDirectory)/Source_LuaScriptEngine.cpp$(ObjectSuffix): Source/LuaScriptEngine.cpp $(IntermediateDirectory)/Source_LuaScriptEngine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/LuaScriptEngine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_LuaScriptEngine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_LuaScriptEngine.cpp$(DependSuffix): Source/LuaScriptEngine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_LuaScriptEngine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_LuaScriptEngine.cpp$(DependSuffix) -MM Source/LuaScriptEngine.cpp

$(IntermediateDirectory)/Source_LuaScriptEngine.cpp$(PreprocessSuffix): Source/LuaScriptEngine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_LuaScriptEngine.cpp$(PreprocessSuffix) Source/LuaScriptEngine.cpp

$(IntermediateDirectory)/Source_XMLDataManager.cpp$(ObjectSuffix): Source/XMLDataManager.cpp $(IntermediateDirectory)/Source_XMLDataManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/XMLDataManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_XMLDataManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_XMLDataManager.cpp$(DependSuffix): Source/XMLDataManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_XMLDataManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_XMLDataManager.cpp$(DependSuffix) -MM Source/XMLDataManager.cpp

$(IntermediateDirectory)/Source_XMLDataManager.cpp$(PreprocessSuffix): Source/XMLDataManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_XMLDataManager.cpp$(PreprocessSuffix) Source/XMLDataManager.cpp

$(IntermediateDirectory)/Source_BARECEGUI.cpp$(ObjectSuffix): Source/BARECEGUI.cpp $(IntermediateDirectory)/Source_BARECEGUI.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/BARECEGUI.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_BARECEGUI.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_BARECEGUI.cpp$(DependSuffix): Source/BARECEGUI.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_BARECEGUI.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_BARECEGUI.cpp$(DependSuffix) -MM Source/BARECEGUI.cpp

$(IntermediateDirectory)/Source_BARECEGUI.cpp$(PreprocessSuffix): Source/BARECEGUI.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_BARECEGUI.cpp$(PreprocessSuffix) Source/BARECEGUI.cpp

$(IntermediateDirectory)/Source_Timer.cpp$(ObjectSuffix): Source/Timer.cpp $(IntermediateDirectory)/Source_Timer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/Timer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Timer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Timer.cpp$(DependSuffix): Source/Timer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Timer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Timer.cpp$(DependSuffix) -MM Source/Timer.cpp

$(IntermediateDirectory)/Source_Timer.cpp$(PreprocessSuffix): Source/Timer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Timer.cpp$(PreprocessSuffix) Source/Timer.cpp

$(IntermediateDirectory)/Source_Filesystem.cpp$(ObjectSuffix): Source/Filesystem.cpp $(IntermediateDirectory)/Source_Filesystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/Filesystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Filesystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Filesystem.cpp$(DependSuffix): Source/Filesystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Filesystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Filesystem.cpp$(DependSuffix) -MM Source/Filesystem.cpp

$(IntermediateDirectory)/Source_Filesystem.cpp$(PreprocessSuffix): Source/Filesystem.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Filesystem.cpp$(PreprocessSuffix) Source/Filesystem.cpp

$(IntermediateDirectory)/Source_DebugRenderer.cpp$(ObjectSuffix): Source/DebugRenderer.cpp $(IntermediateDirectory)/Source_DebugRenderer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/DebugRenderer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_DebugRenderer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DebugRenderer.cpp$(DependSuffix): Source/DebugRenderer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DebugRenderer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DebugRenderer.cpp$(DependSuffix) -MM Source/DebugRenderer.cpp

$(IntermediateDirectory)/Source_DebugRenderer.cpp$(PreprocessSuffix): Source/DebugRenderer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DebugRenderer.cpp$(PreprocessSuffix) Source/DebugRenderer.cpp

$(IntermediateDirectory)/Source_Screen.cpp$(ObjectSuffix): Source/Screen.cpp $(IntermediateDirectory)/Source_Screen.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/Screen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_Screen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Screen.cpp$(DependSuffix): Source/Screen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Screen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Screen.cpp$(DependSuffix) -MM Source/Screen.cpp

$(IntermediateDirectory)/Source_Screen.cpp$(PreprocessSuffix): Source/Screen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Screen.cpp$(PreprocessSuffix) Source/Screen.cpp

$(IntermediateDirectory)/Source_ScreenList.cpp$(ObjectSuffix): Source/ScreenList.cpp $(IntermediateDirectory)/Source_ScreenList.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/ScreenList.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_ScreenList.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_ScreenList.cpp$(DependSuffix): Source/ScreenList.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_ScreenList.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_ScreenList.cpp$(DependSuffix) -MM Source/ScreenList.cpp

$(IntermediateDirectory)/Source_ScreenList.cpp$(PreprocessSuffix): Source/ScreenList.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_ScreenList.cpp$(PreprocessSuffix) Source/ScreenList.cpp

$(IntermediateDirectory)/Source_BAREErrors.cpp$(ObjectSuffix): Source/BAREErrors.cpp $(IntermediateDirectory)/Source_BAREErrors.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/BAREErrors.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_BAREErrors.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_BAREErrors.cpp$(DependSuffix): Source/BAREErrors.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_BAREErrors.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_BAREErrors.cpp$(DependSuffix) -MM Source/BAREErrors.cpp

$(IntermediateDirectory)/Source_BAREErrors.cpp$(PreprocessSuffix): Source/BAREErrors.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_BAREErrors.cpp$(PreprocessSuffix) Source/BAREErrors.cpp

$(IntermediateDirectory)/Source_LuaContextManager.cpp$(ObjectSuffix): Source/LuaContextManager.cpp $(IntermediateDirectory)/Source_LuaContextManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/LuaContextManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_LuaContextManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_LuaContextManager.cpp$(DependSuffix): Source/LuaContextManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_LuaContextManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_LuaContextManager.cpp$(DependSuffix) -MM Source/LuaContextManager.cpp

$(IntermediateDirectory)/Source_LuaContextManager.cpp$(PreprocessSuffix): Source/LuaContextManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_LuaContextManager.cpp$(PreprocessSuffix) Source/LuaContextManager.cpp

$(IntermediateDirectory)/Source_App.cpp$(ObjectSuffix): Source/App.cpp $(IntermediateDirectory)/Source_App.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/davis-dev/Documents/BARE2DEngine/Source/App.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Source_App.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_App.cpp$(DependSuffix): Source/App.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_App.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_App.cpp$(DependSuffix) -MM Source/App.cpp

$(IntermediateDirectory)/Source_App.cpp$(PreprocessSuffix): Source/App.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_App.cpp$(PreprocessSuffix) Source/App.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


