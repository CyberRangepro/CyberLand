import os
import sys
import shutil
from subprocess import Popen, PIPE

import SCons
from SCons.Environment import Environment
from SCons.Script import ARGUMENTS, SConscript

sys.path.append("./share/scons")
from lex_bison import *

env = Environment()
Export('env')
SConscript('src/fireedge/SConscript', must_exist=0)
cwd = os.getcwd()

# Environment that will be applied to each scons child
main_env = Environment()
main_env['ENV']['PATH'] = os.environ['PATH']

main_env['CXXFLAGS'] = " -DGITVERSION=\'\"" + git_version + "\"\'"

# snippet borrowed from http://dev.gentoo.org/~vapier/scons-blows.txt
# makes scons aware of build related environment variables
if 'CC' in os.environ:
    main_env['CC'] = os.environ['CC']
if 'CFLAGS' in os.environ:
    main_env['CCFLAGS'] += SCons.Util.CLVar(os.environ['CFLAGS'])
if 'CXX' in os.environ:
    main_env['CXX'] = os.environ['CXX']
if 'CXXFLAGS' in os.environ:
    main_env['CXXFLAGS'] += SCons.Util.CLVar(os.environ['CXXFLAGS'])
if 'LDFLAGS' in os.environ:
    main_env['LINKFLAGS'] += SCons.Util.CLVar(os.environ['LDFLAGS'])
else:
    os.environ['LDFLAGS'] = ""

# Add builders for flex and bison
add_lex(main_env)
add_bison(main_env)

# Include dirs
main_env.Append(CPPPATH=[
    cwd+'/include'
])

# Library dirs
main_env.Append(LIBPATH=[
    cwd+'/src/CyperLand/'
])

# Compile flags
main_env.Append(CPPFLAGS=[
    "-g",
    "-Wall",
    "-std=c++17",
    "-Wno-overloaded-virtual"
])

# Linking flags & common libraries
main_env.Append(LINKFLAGS=['-g', '-pthread'])
main_env.Append(LIBS=['z'])


build_scripts=[
    'src/CyperLand/SConstruct',
    'src/rm/SConstruct',
    'src/fireedge/SConstruct',
]


for script in build_scripts:
    env = main_env.Clone()
    SConscript(script, exports='env')
