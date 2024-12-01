module Ex04 where

import Data.Semigroup
import Data.Monoid
import Control.Monad.State (State, get, put, evalState)
import Test.QuickCheck
import Priority
import Size

-- DEFINITIONS AND HELPER FUNCTIONS --

type NodeInfo = (Size, Priority)
data QueueTree a
  = Null
  | Leaf NodeInfo a
  | Node NodeInfo (QueueTree a) (QueueTree a)
  deriving (Show)

nodeInfo :: QueueTree a -> NodeInfo
nodeInfo Null = mempty
nodeInfo (Leaf i _) = i
nodeInfo (Node i _ _) = i

sizeOf :: QueueTree a -> Size
sizeOf = fst . nodeInfo

maxPrio :: QueueTree a -> Priority
maxPrio = snd . nodeInfo

-- checks whether the tree structure
-- is balanced (i.e. that the left subtree and the right
-- subtree don't ever differ too much in size)
balanced :: QueueTree a -> Bool
balanced (Node i l r) =
  let sl = unSize (sizeOf l) in
  let sr = unSize (sizeOf r) in
  abs (sl - sr) <= 1 && balanced l && balanced r
balanced _ = True



-- EXERCISE STARTS HERE --

-- Task 1a. Write a well-formedness predicate
--          wf for the `QueueTree` data type.

-- Hint: Both `Priority` and `Size` are semigroups/monoids.
-- This means that the type `NodeInfo` is also automatically
-- a monoid.

wf :: QueueTree a -> Bool
wf Null              = True
wf (Leaf info _)     = s == 1 && p >= 0 where
  s = unSize . fst $ info
  p = unPriority . snd $ info
wf (Node info tl tr) = infoIsValid && wf tl && wf tr where
  infoIsValid = info == nodeInfo tl <> nodeInfo tr

-- Task 1b. Write smart constructors `leaf` and `node`
--          for the `QueueTree` data type which maintain
--          the well-formedness invariant. I.e. given
--          well-formed inputs, the smart constructors
--          should give well-formed outputs.
--          You should /not/ tweak the structure of the ~QueueTree~
--          beyond updating the ~NodeInfo~; in particular don't do
--          ~node Null Null = Null~.

leaf :: Priority -> a -> QueueTree a
leaf p x
  | unPriority p >= 0 = Leaf (size 1, p) x
  | otherwise         = error "leaf: priority error"

node :: QueueTree a -> QueueTree a -> QueueTree a
-- node Null tr = tr
-- node tl Null = tl
node tl tr   = Node (nodeInfo tl <> nodeInfo tr) tl tr



-- Task 2a. Implement the usual priority queue functions
--          for the type `QueueTree`. These are
--          pop - Remove the element from the queue that has the
--               highest priority. Return the modified queue,
--               along with the removed element (if any).
--          insert - add an element to the queue with the given priority.

pop :: QueueTree a -> (QueueTree a, Maybe a)
pop Null             = (Null, Nothing)
pop (Leaf _ x)       = (Null, Just x)
pop (Node _ tl tr)
  | maxPrioOfTl < maxPrioOfTr = let (tr', x) = pop tr in (node tl tr', x)
  | maxPrioOfTl > maxPrioOfTr = let (tl', x) = pop tl in (node tl' tr, x)
  | otherwise                 = case pop tl of
    (_, Nothing) -> let (tr', x) = pop tr in (node tl tr', x)
    (tl', x)     -> (node tl' tr, x)
  where
    maxPrioOfTl = unPriority $ maxPrio tl
    maxPrioOfTr = unPriority $ maxPrio tr

insert :: Priority -> a -> QueueTree a -> QueueTree a
insert p x tree = case tree of
  Null                     -> leaf p x
  Leaf _ _                 -> node tree $ leaf p x
  Node _ tl tr
    | sizeOfTl <= sizeOfTr -> node (insert p x tl) tr
    | otherwise            -> node tl $ insert p x tr
    where
      sizeOfTl = unSize $ sizeOf tl
      sizeOfTr = unSize $ sizeOf tr

-- Task 2b. Implement a function `fromList` that converts a
--          list of `(Priority, x)` pairs into a well-formed
--          and balanced `QueueTree x` structure.

fromList :: [(Priority, a)] -> QueueTree a
fromList = foldr (uncurry insert) Null

-- Hint: you can use `fromList` to implement an `Arbitrary`
-- instance for `QueueTree`, allowing you to test your work.
instance Arbitrary a => Arbitrary (QueueTree a) where
  arbitrary = resize 50 $ sized $ buildTree where
    buildTree s = frequency [(1, pure Null), (s, action)] where
      action = insert <$> arbitrary <*> arbitrary <*> buildTree (s - 1)

-- Task 3. Implement stateful versions of the pop and insert
--         operations above using the `State` type in Haskell's
--         standard mtl library.
--         Implement a `peek` operation which just returns the
--         highest-priority element without changing the
--         state of the queue.
--         Do not use the `state` function in your final
--         implementations!

pop' :: State (QueueTree a) (Maybe a)
pop' = get >>= \tree -> let (tree', x) = pop tree in put tree' >> pure x

insert' :: Priority -> a -> State (QueueTree a) ()
insert' p x = get >>= put . insert p x

peek' :: State (QueueTree a) (Maybe a)
peek' = get >>= \tree -> let (_, x) = pop tree in pure x



-- END OF EXERCISE --

-- You can use the following three examples to test your
-- implementations of pop' and insert', and to practice
-- reading `State`-ful functions.

-- Returns the highest priority currently in the `QueueTree`
-- without changing the state.
getMaxPrio' :: State (QueueTree a) Priority
getMaxPrio' =
  get >>= \q ->
  return (maxPrio q)

-- Removes the element with the second-highest priority
-- in the queue.
dip' :: State (QueueTree a) ()
dip' =
  getMaxPrio' >>= \p ->
  pop'        >>= \h1 ->
  pop'        >>= \h2 ->
  case h1 of
    Nothing -> return ()
    Just h1 -> insert' p h1

-- a `State`-free version of dip
dip :: QueueTree Char -> QueueTree Char
dip = evalState $
  dip' >>= \() ->
  get
