{-# LANGUAGE ForeignFunctionInterface #-}

module Add1 (add1) where

import Foreign.C.Types (CInt (..))

foreign export ccall "add1" add1 :: CInt -> CInt

add1 :: CInt -> CInt
add1 x = x + 1
