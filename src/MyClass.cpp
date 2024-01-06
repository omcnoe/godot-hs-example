#include "MyClass.h"

#include <godot_cpp/classes/engine.hpp>

using namespace godot;

extern "C" void myClassSetPosition(HsPtr myClass, double x, double y) {
  ((MyClass *)myClass)->set_position(Vector2(x, y));
}

void MyClass::_bind_methods() {
  ClassDB::bind_method(D_METHOD("get_amplitude"), &MyClass::get_amplitude);
  ClassDB::bind_method(D_METHOD("set_amplitude", "p_amplitude"),
                       &MyClass::set_amplitude);
  ClassDB::add_property("MyClass", PropertyInfo(Variant::FLOAT, "amplitude"),
                        "set_amplitude", "get_amplitude");
}

MyClass::MyClass() {
  if (Engine::get_singleton()->is_editor_hint()) {
    set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
  }
  hs_state = myClassCtor(this);
}

MyClass::~MyClass() { myClassDtor(this->hs_state); }

float MyClass::get_amplitude() { return myClassGetAmplitude(this->hs_state); }

void MyClass::set_amplitude(float amplitude) {
  hs_state = myClassSetAmplitude(this->hs_state, amplitude);
}

void MyClass::_process(double delta) {
  hs_state = myClassProcess(this->hs_state, delta);
}
