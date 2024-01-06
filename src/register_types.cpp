#include "MyClass.h"

#include <HsFFI.h>

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void init_godot_hs_example(ModuleInitializationLevel p_level) {
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }

  int argc = 1;
  const char *argv[] = {"godot-hs-example", NULL};
  char **pargv = const_cast<char **>(argv);
  hs_init(&argc, &pargv);
  UtilityFunctions::print("Haskell runtime initialized");

  ClassDB::register_class<MyClass>();
}

void terminate_godot_hs_example(ModuleInitializationLevel p_level) {
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }

  hs_exit();
}

extern "C" {
GDExtensionBool GDE_EXPORT init_godot_hs_example_gdextension(
    GDExtensionInterfaceGetProcAddress p_get_proc_address,
    const GDExtensionClassLibraryPtr p_library,
    GDExtensionInitialization *r_initialization) {
  GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library,
                                          r_initialization);

  init_obj.register_initializer(init_godot_hs_example);
  init_obj.register_terminator(terminate_godot_hs_example);
  init_obj.set_minimum_library_initialization_level(
      MODULE_INITIALIZATION_LEVEL_SCENE);

  return init_obj.init();
}
}
