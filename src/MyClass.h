#ifndef MYCLASS_H
#define MYCLASS_H

#include <HsFFI.h>

#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {
class MyClass : public Sprite2D {
  GDCLASS(MyClass, Sprite2D)

protected:
  static void _bind_methods();

public:
  HsPtr hs_state;

  MyClass();
  ~MyClass();

  float get_amplitude();
  void set_amplitude(float);

  void _process(double) override;
};

} // namespace godot

extern "C" void myClassSetPosition(HsPtr myClass, double, double);

extern "C" HsPtr myClassCtor(HsPtr);
extern "C" void myClassDtor(HsPtr);
extern "C" float myClassGetAmplitude(HsPtr);
extern "C" HsPtr myClassSetAmplitude(HsPtr, int);
extern "C" HsPtr myClassProcess(HsPtr, double);

#endif
