import Data.Char
import Graphics.Gloss
import Graphics.Gloss.Data.ViewPort
import Graphics.Gloss.Interface.IO.Interact
import GHC.Float
import Text.Read (readMaybe)

type DVector = (Double, Double)
type Planet = (DVector, DVector, [Point], Color, Int)
type Interface = (String, (Int, Int))
type Translation = (Bool, Point, (Float, Float))
type World = ([Planet], Interface, Float, Translation)

m2Picture :: World -> Picture
m2Picture (planets, iface, f, (_, _, (tx, ty))) = 
    pictures [
        translate tx ty (
            scale f f (
                pictures [
                    color yellow (circleSolid rSol),
                    pictures (map drawPlanet planets)
                ]
            )
        ),
        ifacePicture iface
    ]

ifacePicture :: Interface -> Picture
ifacePicture (s, (x,y)) = 
    pictures [
        translate 0 (hy) (scale 0.15 0.15 (color white (text "X  Y  Vx  Vy"))),
        translate (-100) (hy-20) (scale 0.15 0.15 (color white (text ("Agregar: " ++ s))))
    ]
    where hy = ((fromIntegral (div y 2 - 50))::Float)

drawPlanet :: Planet -> Picture
drawPlanet ((x, y), _, ps, c, _) = 
    pictures [
        color c (translate (double2Float x) (double2Float y) (circleSolid rPlaneta)),
        color c (line ps)
    ]

transition :: Float -> World -> World
transition _ (planets, iface, f, t) = (map transitionPlanet (filter colisionSol planets), iface, f, t)

colisionSol :: Planet -> Bool
colisionSol (r, _, _, _, _) = double2Float (norma2 r) > rPlaneta + rSol

transitionPlanet :: Planet -> Planet
transitionPlanet (r@(x, y), v, ps, c, n) = (nuevaPos r v deltaT, 
                                            nuevaVel v (accelPos masaSol r) deltaT, 
                                            if n == 0 then ((double2Float x, double2Float y) : (take 5000 ps)) else ps,
                                            c, mod (n+1) 100)

handler :: Event -> World -> World
handler (EventKey k ks _ ep@(x,y)) w@(ps, (s, p), f, t@(b, pf, ot@(tx,ty))) = case (k, ks) of
                                                  (SpecialKey KeyBackspace, Down) -> (ps, (sinit s, p), f, t)
                                                  (Char '\b', Down) -> (ps, (sinit s, p), f, t) -- En wayland gloss captura el BS como un Char en vez de SpecialKey
                                                  (Char c, Down) ->  (ps, (s ++ [c], p), f, t)
                                                  (SpecialKey KeySpace, Down) ->  (ps, (s ++ [' '], p), f, t)
                                                  (SpecialKey KeyEnter, Down) -> addPlanet (ps, (s,p), f, t)
                                                  (MouseButton WheelUp, _) -> (ps, (s,p), f*1.1, (b, pf, (x - (x-tx)*1.1, y - (y-ty)*1.1)))
                                                  (MouseButton WheelDown, _) -> (ps, (s,p), f*0.9, (b, pf, (x - (x-tx)*0.9, y - (y-ty)*0.9)))
                                                  (MouseButton LeftButton, Down) -> (ps, (s,p), f, (True, ep, ot))
                                                  (MouseButton LeftButton, Up) -> (ps, (s,p), f, (False, ep, ot))
                                                  _ -> w
handler (EventResize (x, y)) (ps, (s, _), f, t) = (ps, (s, (x,y)), f, t)
handler (EventMotion np@(x, y)) w@(ps, i, f, t@(b, pf@(pfx, pfy),  (tx, ty))) = if b then (ps, i, f, (True, np, (tx-dx, ty-dy))) else w
    where dx = 1 * (pfx - x)
          dy = 1 * (pfy - y)

sinit :: String -> String
sinit s = if null s then s else init s

parseVectors :: String -> [Maybe Double]
parseVectors s =  (map (\x -> readMaybe x :: Maybe Double) (words s))
 
addPlanet :: World -> World
addPlanet w@(ps, (s, p), f, t) = case parseVectors s of
                                      [Just x, Just y, Just vx, Just vy] -> (((x,y), (vx,vy), [], blue, 0):ps, ([], p), f, t)
                                      _ -> w

getDouble:: String -> IO Double
getDouble prompt = do
    putStr prompt
    xs <- getLine

    case readMaybe xs :: Maybe Double of
        Just d -> return d
        _      -> do putStrLn "ERROR: Numero invalido"
                     getDouble prompt

initState :: World
initState = 
    (
        [   
            ((7.406e11, 0), (0, 1.304e4), [], orange, 0),
            ((1.496e11, 0), (0, 29780), [], blue, 0)
        ], 
        ("", (1920, 1080)),
        5e-10,
        (False, (0,0), (0,0))
    )
          
main = do
    -- putStrLn "Ingrese el vector posicion inicial: "
    -- x <- getDouble "X = "
    -- y <- getDouble "Y = "
    --
    -- putStrLn "\nIngrese el vector velocidad inicial: "
    -- vx <- getDouble "Vx = "
    -- vy <- getDouble "Vy = "
    --
    -- simulate (InWindow "TP" (1920, 1080) (100, 100)) 
    --          black 
    --          (60 * 60)
    --          [
    --           ((x,y), (vx,vy), [], green, 0), 
    --           ((7.406e11, 0), (0, 1.304e4), [], orange, 0),
    --           ((1.496e11, 0), (0, 29780), [], blue, 0)
    --          ]
    --          m2Picture
    --          transition
    
    play (InWindow "TP" (1920, 1080) (100,100))
         black
         (60*60)
         initState
         m2Picture
         handler
         transition

    return ()
-- Constante de gravitacion universal
constG :: Double 
constG = 6.67430e-11


-- Radio planeta (artificial)
rPlaneta :: Float
rPlaneta = 4e10

rSol :: Float
rSol = 6.96e10

-- Masa del sol
masaSol :: Double
masaSol = 1.98847e30

deltaT :: Double 
deltaT = 30*24*60/60

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




