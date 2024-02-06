from SCons.Script import *

def Firmware(env, target, sources, **kwargs):
	# Can't automate object creation with variants, when you have multiple outputs from the same source
	# require the user to do it instead!
	libobjs = [env.Object(f) for f in Flatten([env['LIB_SOURCES']])]
	firmware = env.Program(target, sources + libobjs, **kwargs)
	# TODO make this autodepend on the ... actual? ldscript?
	#env.Depends(firmware, '${LAKS_PATH}/ld_scripts/${LINK_SCRIPT}')
	#env.Depends(firmware, '${LINK_SCRIPT}')
	return firmware

def exists():
    return True

def generate(env):
    env.AddMethod(Firmware)