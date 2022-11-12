main = mapM_ putStrLn $ map show subg

v = [1,2,3,4]
e = [(1,2), (1,3), (1,4), (2,4), (3,4)]
g = (v, e)

subg = [ (v', e') | v' <- pow v, e' <- pow e, isSubGraph v' e']

pow :: [a] -> [[a]]
pow [] = [[]]
pow (x:xs) = (map (x:) (pow xs)) ++ pow xs

isSubGraph :: [Int] -> [(Int,Int)] -> Bool
isSubGraph [] _ = False
isSubGraph _ [] = True
isSubGraph vs ((v,u):es)
  | elem v vs && elem u vs = isSubGraph vs es
  | otherwise = False
