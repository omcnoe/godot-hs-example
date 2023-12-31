{-# LANGUAGE ForeignFunctionInterface #-}

module Hello where

import Foreign.C.String (CString, newCString)
import Foreign.Marshal.Alloc (free)
import Foreign.Ptr (Ptr)

foreign export ccall hs_hello :: IO CString

hs_hello :: IO CString
hs_hello = newCString "Hello from Haskell :)"

foreign export ccall hs_free :: Ptr a -> IO ()

hs_free :: Ptr a -> IO ()
hs_free = free
