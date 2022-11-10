import System.Random
import Data.List
import Text.Read

main = fmap readMaybe getLine >>= \mn -> genSeq mn >>= \s -> putStrLn s

genSeq :: Maybe Int -> IO String
genSeq Nothing  = return "Enter a positive integer."
genSeq (Just n) = getStdGen >>=
  \gen -> return ((map bracket2paren . show . reverse . sort . take n) (randomRs (1, n-1) gen))

bracket2paren :: Char -> Char
bracket2paren '[' = '('
bracket2paren ']' = ')'
bracket2paren c   = c
