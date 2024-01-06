{-# LANGUAGE ForeignFunctionInterface #-}
{-# LANGUAGE OverloadedRecordDot #-}

module MyClass where

import Foreign.C.Types (CDouble (..), CFloat (..))
import Foreign.Ptr (Ptr)
import Foreign.StablePtr (StablePtr, deRefStablePtr, freeStablePtr, newStablePtr)

data MyClass = MyClass
  { cxxThis :: Ptr (),
    timePassed :: Double,
    amplitude :: Float
  }

foreign import ccall unsafe myClassSetPosition :: Ptr () -> CDouble -> CDouble -> IO ()

foreign export ccall myClassCtor :: Ptr () -> IO (StablePtr MyClass)

foreign export ccall myClassDtor :: StablePtr MyClass -> IO ()

foreign export ccall myClassGetAmplitude :: StablePtr MyClass -> IO CFloat

foreign export ccall myClassProcess :: StablePtr MyClass -> CDouble -> IO (StablePtr MyClass)

foreign export ccall myClassSetAmplitude :: StablePtr MyClass -> CFloat -> IO (StablePtr MyClass)

setPosition :: MyClass -> CDouble -> CDouble -> IO ()
setPosition myClass = myClassSetPosition myClass.cxxThis

myClassCtor :: Ptr () -> IO (StablePtr MyClass)
myClassCtor cxxThis =
  newStablePtr $
    MyClass
      { cxxThis = cxxThis,
        timePassed = 0.0,
        amplitude = 10
      }

myClassDtor :: StablePtr MyClass -> IO ()
myClassDtor = freeStablePtr

myClassGetAmplitude :: StablePtr MyClass -> IO CFloat
myClassGetAmplitude statePtr = do
  myClass <- deRefStablePtr statePtr
  return $ realToFrac myClass.amplitude

myClassSetAmplitude :: StablePtr MyClass -> CFloat -> IO (StablePtr MyClass)
myClassSetAmplitude statePtr (cAmplitude :: CFloat) = do
  myClass <- deRefStablePtr statePtr
  let amplitude = realToFrac cAmplitude
  freeStablePtr statePtr
  newStablePtr $ myClass {amplitude = amplitude}

myClassProcess :: StablePtr MyClass -> CDouble -> IO (StablePtr MyClass)
myClassProcess statePtr (cDelta :: CDouble) = do
  myClass <- deRefStablePtr statePtr
  let delta = realToFrac cDelta

  setPosition
    myClass
    (realToFrac (realToFrac myClass.amplitude + (realToFrac myClass.amplitude * sin (myClass.timePassed * 2.0))))
    (realToFrac (realToFrac myClass.amplitude + (realToFrac myClass.amplitude * cos (myClass.timePassed * 1.5))))

  freeStablePtr statePtr
  newStablePtr $ myClass {timePassed = myClass.timePassed + delta}
