from building import *
import rtconfig

# get current directory
cwd     = GetCurrentDir()

# The set of source files associated with this SConscript file.
src     = Glob('src/*.c')
path    = [cwd + '/src']

LOCAL_CCFLAGS = ''

group = DefineGroup('capnp', src, depend = ['PKG_USING_CAPNP'], CPPPATH = path, LOCAL_CCFLAGS = LOCAL_CCFLAGS)

Return('group')
