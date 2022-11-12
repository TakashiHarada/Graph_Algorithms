-- Since this program naively implements the Kruskal's algorith,
-- it is not efficient Haskell code.

import Data.List
import Data.Char

type Vertex = Int
type Edge = (Vertex, Vertex)
type WEdge = (Edge, Int)

type WGraph = ([Vertex], [WEdge])

main =
  fmap (map split . lines) getContents >>=
  \c -> let mst = (sort . kruskal . readGraph) c in
    let sum = foldr (\e acc -> (snd e) + acc) 0 mst in mapM_ print mst >>= \_ -> putStrLn $ "Weight = " ++ show sum
      
readGraph :: [[String]] -> WGraph
readGraph ss = (vs, es)
  where
    n = (read . head . head) ss
    vs = [0..(n-1)]
    es' = (tail . init) ss
    es = map (\(x:y:[z]) -> ((x,y), z)) $ (map (map read) . tail . init) es'

split :: String -> [String]
split s = (map reverse . split' "") s

split' :: String -> String -> [String]
split' s [] = [s]
split' s (c:cs)
  | isSpace c = s: (split' "" cs)
  | otherwise = split' (c : s) cs

kruskal :: WGraph -> [WEdge]
kruskal (vs, es) = map (\(w, (x,y)) -> ((x, y), w)) $ kruskal' es' comp
  where
    n = length vs
    comp = [ (x, x) | x <- [0..(n-1)] ]
    es' = (sort . map (\((x, y), z) -> (z, (x, y)))) es

kruskal' :: [(Int, Edge)] -> [(Vertex, Int)] -> [(Int, Edge)]
kruskal' [] _ = []
kruskal' ((w, (u,v)):es) comp
  | is_same_component u v comp = kruskal' es comp
  | otherwise = (w, (u,v)) : (kruskal' es comp')
  where
    cu = snd (comp !! u)
    cv = snd (comp !! v)
    comp' = update comp cu cv

is_same_component :: Vertex -> Vertex -> [(Vertex, Int)] -> Bool
is_same_component u v comp = snd (comp !! u) == snd (comp !! v)
    
update :: [(Vertex, Int)] -> Int -> Int -> [(Vertex, Int)]
update [] _ _ = []
update (c:cs) cu cv
  | snd c == cv = (fst c, cu) : update cs cu cv
  | otherwise   = c : update cs cu cv
