import Data.Char
import Graphics.Gloss
import Text.Parsec.Prim
import Text.Parsec.Combinator


type DVector = (Double, Double)

isDouble :: Parser Bool
isDouble = do
    char '-' <|> return True
    many1 digit
    char '.' >> many1 digit <|> return True
    char 'e' >> (char '-' <|> return True) >> many1 digit
    return True
    <|> return False

getDouble :: String -> IO Double 
getDouble prompt = do
    putStr prompt
    xs <- getLine
    if xs /= [] && isDouble xs then
        return (read xs)
    else do
        putStrLn "ERROR: Numero invalido"
        getDouble prompt

main = do
    putStrLn "Ingrese el vector posicion inicial: "
    x <- getDouble "X = "
    y <- getDouble "Y = "

    putStrLn "\nIngrese el vector velocidad inicial: "
    vx <- getDouble "Vx = "
    vy <- getDouble "Vy = "

    putStrLn "\nIngrese la masa del planeta: "
    mp <- get 

    return ()

masaSol :: Double
masaSol = 1.98847e30

nuevaVel :: DVector -> DVector ->  


-- main :: IO ()
-- main = display (InWindow "TP" (400, 400) (10, 10)) black (color white (circle 100))
