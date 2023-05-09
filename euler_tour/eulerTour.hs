import Data.List

type Vertex = Int
type Edge = (Vertex, Vertex)
type AdList = [[Vertex]]

readEdge :: IO Edge
readEdge = fmap ((\[x,y] -> (x,y)) . (map read . words)) getLine

addVertex :: AdList -> Edge -> AdList
addVertex al (u,v) = prev ++ [v:(al !! u)] ++ next
  where
    -- es = al !! u
    prev = take u al
    next = drop (u+1) al

makeAdjacencyList :: AdList -> [Edge] -> AdList
makeAdjacencyList al [] = al
makeAdjacencyList al ((u,v):es)
  = makeAdjacencyList (addVertex (addVertex al (u,v)) (v,u)) es

removeVertex :: Vertex -> Vertex -> AdList -> AdList
removeVertex v u al = prev ++ [(delete v (al !! u))] ++ next
  where
    prev = take u al
    next = drop (u+1) al

removeEdge :: Edge -> AdList -> AdList
removeEdge (u, v) al = removeVertex u v (removeVertex v u al)

makeEulerTour :: AdList -> Vertex -> [Edge] -> [Edge] -> [Edge]
makeEulerTour al v s l
  | [] == al !! v =
    if [] == s then l else makeEulerTour al ((fst . head) s) (tail s) ((head s) : l)
  | otherwise =
    makeEulerTour (removeEdge (v, u) al) u ((v, u):s) l
    where u = head (al !! v)

main = fmap (map read . words) getLine >>=
       \[n, m] -> sequence (replicate m readEdge) >>=
       \es ->
         let al = (makeAdjacencyList (replicate n []) es) in
           mapM_ print (makeEulerTour al 0 [] [])

-- main =
--   do
--     [n, m] <- fmap (map read. words) getLine
--     es <- sequence (replicate m readEdge)
--     let al = (makeAdjacencyList (replicate n [])) es
--     mapM_ print (makeEulerTour al 0 [] [])
