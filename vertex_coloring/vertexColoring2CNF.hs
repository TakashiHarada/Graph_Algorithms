main =
  fmap (map read . words) getLine >>=
  \[n,m] -> (sequence . take m . repeat) (fmap (map read . words) getLine) >>=
  \es -> fmap read getLine >>=
  \d -> putStrLn (firstLine n m d) >>=
  \_ -> putStrLn (init (atLeastOneColor n d)) >>=
  \_ -> putStrLn (init (adjacentConstraint d es))

firstLine :: Int -> Int -> Int -> String
firstLine n m d = "p cnf " ++ show (n*d) ++ " " ++ (show (n + m*d))

atLeastOneColor :: Int -> Int -> String
atLeastOneColor n d = (unlines .map (\x -> x ++ " 0") . map unwords) [ map (show . \x -> d*i+x) [1..d] | i <- [0..(n-1)]]

adjacentConstraint :: Int -> [[Int]] -> String
adjacentConstraint d [] = ""
adjacentConstraint d (e:es) = (adjacentConstraint' d e) ++ (adjacentConstraint d es)

adjacentConstraint' :: Int -> [Int] -> String
adjacentConstraint' d e = (unlines . map unwords) [ [show (-(u*d+j)), show (-(v*d+j)), "0"] | j <- [1..3]]
  where
    u = head e
    v = last e
