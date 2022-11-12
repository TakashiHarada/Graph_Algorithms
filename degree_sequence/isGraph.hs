import Data.Char
import Data.List

main = getLine >>=
  \l -> 
    if isNumSeq l
    then
      if (isGraph . map read . split . init . tail) l
      then putStrLn "Input sequence is the degree sequence for some graph."
      else putStrLn "Input sequence is not a degree sequence."
    else putStrLn "Enter a non-increasing postive number sequence."

isGraph :: [Int] -> Bool
isGraph [] = False
isGraph (v:vs)
  | any (< 0) (v:vs) = False
  | all (\x -> 0 == x) (v:vs) = True
  | otherwise = isGraph ((reverse . sort ) (dec v vs))

dec :: Int -> [Int] -> [Int]
dec 0 as = as
dec a (v:vs) = (v-1) : (dec (a-1) vs)

isNumSeq :: String -> Bool
isNumSeq [] = False
isNumSeq s
  | length s < 3 = False
  | head s /= '(' || last s /= ')' = False
  | (any (\x -> x == "")) ss = False
  | (any (not . isNum)) ss = False
  | otherwise = True
  where ss = (split . init . tail) s

split :: String -> [String]
split s = (map reverse . split' "") s

split' :: String -> String -> [String]
split' s [] = [s]
split' s (c:cs)
  | isSpace c = split' s cs
  | ',' == c = s : (split' "" cs)
  | otherwise = split' (c : s) cs

isNum :: String -> Bool
isNum s = all isDecimal s

isDecimal :: Char -> Bool
isDecimal x = elem x ['0'..'9']
