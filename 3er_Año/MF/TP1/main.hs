import Data.Char
import Graphics.Gloss
import Graphics.Gloss.Data.ViewPort
import Text.Read

type DVector = (Float, Float)

type Modelo = (DVector, DVector)


m2Picture :: Modelo -> Picture
m2Picture ((x, y), _) = scale 1e-7 1e-7 (pictures [
    color yellow (circleSolid 6.96e8),
    color green (translate x y (circleSolid 4e8))
    ])

transition :: ViewPort -> Float -> Modelo -> Modelo
transition _ _ (r, v) = (nuevaPos r v deltaT, nuevaVel v (accelPos masaSol r) deltaT)


getFloat:: String -> IO Float
getFloat prompt = do
    putStr prompt
    xs <- getLine

    case readMaybe xs :: Maybe Float of
        Just d -> return d
        _      -> do putStrLn "ERROR: Numero invalido"
                     getFloat prompt

main = do
    putStrLn "Ingrese el vector posicion inicial: "
    x <- getFloat "X = "
    y <- getFloat "Y = "

    putStrLn "\nIngrese el vector velocidad inicial: "
    vx <- getFloat "Vx = "
    vy <- getFloat "Vy = "

    -- putStrLn "\nIngrese la masa del planeta: "
    -- mp <- getFloat "mp = "

    simulate (InWindow "TP" (640, 480) (100, 100)) 
             black 
             600
             ((x,y), (vx,vy))
             m2Picture
             transition

    return ()

-- Constante de gravitacion universal
constG :: Float 
constG = 6.67430e-11

-- Masa del sol
masaSol :: Float 
masaSol = 1.98847e30

-- Segundos en un dia
deltaT :: Float 
deltaT = 60

-- Calcula la norma euclidea
norma2 :: DVector -> Float 
norma2 (a, b) = sqrt (a*a + b*b)

-- Dada una masa y una posicion, calcula la aceleracion gravitatoria 
accelPos :: Float -> DVector -> DVector
accelPos mT r@(x, y) = let f = (- constG * mT) / ((norma2 r) ^ 3)
                       in (f * x, f * y)

-- Dada la posicion y velocidad actuales y un diferencial de tiempo dt
-- aproxima la nueva posicion tomando la velocidad como constante
-- en el intervalo de duracion dt
nuevaPos :: DVector -> DVector -> Float -> DVector
nuevaPos (x, y) (vx, vy) dt = (x + vx*dt, y + vy*dt)

-- Dada la velocidad y aceleracion actuales y un diferencial de tiempo dt
-- aproxima la nueva velocidad tomando la aceleracion como consante en el
-- intervalo de duracion dt
nuevaVel :: DVector -> DVector -> Float -> DVector
nuevaVel (vx, vy) (ax, ay) dt = (vx + ax*dt, vy + ay*dt)


-- main :: IO ()
-- main = display (InWindow "TP" (400, 400) (10, 10)) black (color white (circle 100))




