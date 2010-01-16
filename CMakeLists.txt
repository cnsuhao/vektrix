cmake_minimum_required (VERSION 2.6)
project (vektrix)

# core library
add_subdirectory (lib/scripts)

# plugins
#add_subdirectory (plugins/AS3Plugin/scripts) not supported yet
add_subdirectory (plugins/CairoPlugin/scripts)
add_subdirectory (plugins/OgrePlugin/scripts)
add_subdirectory (plugins/SwfPlugin/scripts)
add_subdirectory (plugins/XmlPlugin/scripts)

# demos
add_subdirectory (demos/Ogre3D/scripts)

set(
VTX_LAUNCHER 
"#!/bin/bash

tty -s\;
if [ $? -ne 0 ]\;
    then konsole --workdir $(dirname $0) -e \"$0\"\;
    exit\;
fi

")

# macro for creating launcher scripts
macro(CREATE_LAUNCHER LAUNCHER_NAME)
    execute_process(COMMAND echo ${VTX_LAUNCHER}./${LAUNCHER_NAME} OUTPUT_FILE ./bin/${LAUNCHER_NAME}.sh)
    execute_process(COMMAND chmod 777 ./bin/${LAUNCHER_NAME}.sh)
endmacro(CREATE_LAUNCHER)

# create "bin" directory
execute_process(COMMAND mkdir ./bin/)

# copy Ogre3D OpenGL RenderSystem
execute_process(COMMAND cp $ENV{OGRE_HOME}/lib/OGRE/RenderSystem_GL.so ./bin/)

# create launcher scripts
CREATE_LAUNCHER("vektrix_Ogre3D_demo")

