#include "Hello_stub.h"
#include <HsFFI.h>

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void init_hs_shim(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	int argc = 1;
	char *argv[] = { "shim", NULL };
	char **pargv = argv;
	hs_init(&argc, &pargv);

	char *hello = (char*)hs_hello();
	UtilityFunctions::print(hello);
	hs_free(hello); // allocated by Haskell, must free by Haskell
}

void terminate_hs_shim(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	hs_exit();
}

extern "C" {
GDExtensionBool GDE_EXPORT init_hs_shim_gdextension(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(init_hs_shim);
	init_obj.register_terminator(terminate_hs_shim);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
