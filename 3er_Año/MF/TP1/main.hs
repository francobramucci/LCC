import Data.Char
import Graphics.Gloss
import Graphics.Gloss.Data.ViewPort
import Text.Read
import GHC.Float

type DVector = (Double, Double)
type Planet = (DVector, DVector, [Point], Color, Int)
type Modelo = [Planet]

m2Picture :: Modelo -> Picture
m2Picture planets = scale 1e-10 1e-10 (pictures [
    color yellow (circleSolid 6.96e10),
    pictures (map drawPlanet planets)
    ])

drawPlanet :: Planet -> Picture
drawPlanet ((x, y), _, ps, c, _) = pictures [
    color c (translate (double2Float x) (double2Float y) (circleSolid 4e10)),
    color c (line ps)
    ]

transition :: ViewPort -> Float -> Modelo -> Modelo
transition _ _ planets = map transitionPlanet planets

transitionPlanet :: Planet -> Planet
transitionPlanet (r@(x, y), v, ps, c, n) = (nuevaPos r v deltaT, 
                                            nuevaVel v (accelPos masaSol r) deltaT, 
                                            if n == 0 then ((double2Float x, double2Float y) : (take 5000 ps)) else ps,
                                            c, mod (n+1) 100)
 
getDouble:: String -> IO Double
getDouble prompt = do
    putStr prompt
    xs <- getLine

    case readMaybe xs :: Maybe Double of
        Just d -> return d
        _      -> do putStrLn "ERROR: Numero invalido"
                     getDouble prompt

main = do
    putStrLn "Ingrese el vector posicion inicial: "
    x <- getDouble "X = "
    y <- getDouble "Y = "

    putStrLn "\nIngrese el vector velocidad inicial: "
    vx <- getDouble "Vx = "
    vy <- getDouble "Vy = "

    simulate (InWindow "TP" (1920, 1080) (100, 100)) 
             black 
             (600)
             [
              ((x,y), (vx,vy), [], green, 0), 
              ((7.406e11, 0), (0, 1.304e4), [], orange, 0),
              ((1.496e11, 0), (0, 29780), [], blue, 0)
             ]
             m2Picture
             transition

    return ()

-- Constante de gravitacion universal
constG :: Double 
constG = 6.67430e-11

-- Masa del sol
masaSol :: Double 
masaSol = 1.98847e30

-- Segundos en un mes
deltaT :: Double 
deltaT = 30*24*60/10

-- Calcula la norma euclidea
norma2 :: DVector -> Double 
norma2 (a, b) = sqrt (a*a + b*b)

-- Dada una masa y una posicion, calcula la aceleracion gravitatoria 
accelPos :: Double -> DVector -> DVector
accelPos mT r@(x, y) = let f = (- constG * mT) / ((norma2 r) ^ 3)
                       in (f * x, f * y)

-- Dada la posicion y velocidad actuales y un diferencial de tiempo dt
-- aproxima la nueva posicion tomando la velocidad como constante
-- en el intervalo de duracion dt
nuevaPos :: DVector -> DVector -> Double -> DVector
nuevaPos (x, y) (vx, vy) dt = (x + vx*dt, y + vy*dt)

-- Dada la velocidad y aceleracion actuales y un diferencial de tiempo dt
-- aproxima la nueva velocidad tomando la aceleracion como consante en el
-- intervalo de duracion dt
nuevaVel :: DVector -> DVector -> Double -> DVector
nuevaVel (vx, vy) (ax, ay) dt = (vx + ax*dt, vy + ay*dt)


-- main :: IO ()
-- main = display (InWindow "TP" (400, 400) (10, 10)) black (color white (circle 100))
--
-- 




