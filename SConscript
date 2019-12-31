from building import *
import rtconfig

# get current directory
cwd     = GetCurrentDir()

# The set of source files associated with this SConscript file.
src     = Glob('src/*.c')
path    = [cwd + '/src']

if GetDepend('CAPNP_USING_EXAMPLE'):
	path   += [cwd + '/examples']
	src    += Glob('examples/myschema.capnp.c')

if GetDepend('CAPNP_USING_ENCODE_DECODE_EXAMPLE'):
	src    += Glob('examples/capnp_encode_decode.c')

if GetDepend('CAPNP_USING_ENCODE_DECODE_FILE_EXAMPLE'):
	src    += Glob('examples/capnp_encode_to_file.c')
	src    += Glob('examples/capnp_decode_from_file.c')

LOCAL_CCFLAGS = ''

group = DefineGroup('capnp', src, depend = ['PKG_USING_CAPNP'], CPPPATH = path, LOCAL_CCFLAGS = LOCAL_CCFLAGS)

Return('group')
