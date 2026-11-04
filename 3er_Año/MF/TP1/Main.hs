import Data.Char
import Graphics.Gloss
import Graphics.Gloss.Data.ViewPort
import Graphics.Gloss.Interface.IO.Interact
import GHC.Float
import Text.Read (readMaybe)

type DVector = (Double, Double)

data Planet = Planet 
    { pos     :: DVector
    , vel     :: DVector
    , tray    :: [Point]
    , pColor  :: Color  
    , traylen :: Int
    } deriving (Show, Eq)

data Interface = Interface 
    { iText   :: String 
    , wsize   :: (Int, Int)
    } deriving (Show, Eq)

data Translation = Translation 
    { pressl  :: Bool
    , lastpos :: Point
    , cord    :: Point
    } deriving (Show, Eq)

data World = World 
    { planets :: [Planet]
    , iface   :: Interface
    , wScale  :: Float  
    , trans   :: Translation
    } deriving (Show, Eq)

m2Picture :: World -> Picture
m2Picture w = 
    pictures [
        translate tx ty (
            scale f f (
                pictures [
                    color yellow (circleSolid rSol),
                    pictures (map drawPlanet (planets w))
                ]
            )
        ),
        ifacePicture (iface w)
    ]
  where 
    f = wScale w
    (tx, ty) = cord (trans w)

ifacePicture :: Interface -> Picture
ifacePicture i = 
    pictures [
        translate 0 hy (scale 0.15 0.15 (color white (text "X  Y  Vx  Vy"))),
        translate (-100) (hy - 20) (scale 0.15 0.15 (color white (text ("Agregar: " ++ iText i))))
    ]
  where 
    (_, y) = wsize i
    hy = fromIntegral (y `div` 2 - 50) :: Float

drawPlanet :: Planet -> Picture
drawPlanet p = 
    pictures [
        color c (translate (double2Float px) (double2Float py) (circleSolid rPlaneta)),
        color c (line (tray p))
    ]
  where 
    (px, py) = pos p
    c = pColor p

transition :: Float -> World -> World
transition _ w = w { planets = map transitionPlanet (filter colisionSol (planets w)) }

colisionSol :: Planet -> Bool
colisionSol p = double2Float (norma2 (pos p)) > rPlaneta + rSol

transitionPlanet :: Planet -> Planet
transitionPlanet p = p 
    { pos     = nuevaPos r v deltaT
    , vel     = nuevaVel v (accelPos masaSol r) deltaT
    , tray    = if n == 0 then (double2Float px, double2Float py) : take 5000 ps 
                          else ps
    , traylen = (n + 1) `mod` 10000
    }
  where
    r@(px, py) = pos p
    v  = vel p
    ps = tray p
    n  = traylen p

handler :: Event -> World -> World
handler (EventKey k ks _ ep@(x, y)) w = case (k, ks) of
    (SpecialKey KeyBackspace, Down) -> updateText sinit
    (Char '\b', Down)               -> updateText sinit
    (Char c, Down)                  -> updateText (\s -> s ++ [c])
    (SpecialKey KeySpace, Down)     -> updateText (\s -> s ++ " ")
    (SpecialKey KeyEnter, Down)     -> addPlanet w
    (MouseButton WheelUp, _)        -> zoom 1.1
    (MouseButton WheelDown, _)      -> zoom 0.9
    (MouseButton LeftButton, Down)  -> w { trans = tr { pressl = True, lastpos = ep } }
    (MouseButton LeftButton, Up)    -> w { trans = tr { pressl = False, lastpos = ep } }
    _                               -> w
  where
    i  = iface w
    tr = trans w
    f  = wScale w
    (tx, ty) = cord tr
    updateText modifier = w { iface = i { iText = modifier (iText i) } }
    zoom factor = w { wScale = f * factor
                    , trans  = tr { cord = (x - (x - tx) * factor, y - (y - ty) * factor) } 
                    }
handler (EventResize newSize) w = 
    w { iface = (iface w) { wsize = newSize } }
handler (EventMotion np@(x, y)) w = 
    if pressl tr
    then w { trans = tr { lastpos = np, cord = (tx - dx, ty - dy) } }
    else w
  where
    tr = trans w
    (pfx, pfy) = lastpos tr
    (tx, ty)   = cord tr
    dx = pfx - x
    dy = pfy - y


addPlanet :: World -> World
addPlanet w = case parseVectors (iText (iface w)) of
    [Just x, Just y, Just vx, Just vy] -> 
        w { planets = Planet (x,y) (vx,vy) [] blue 0 : planets w
          , iface   = (iface w) { iText = "" } 
          }
    _ -> w


sinit :: String -> String
sinit s = if null s then s else init s

parseVectors :: String -> [Maybe Double]
parseVectors s = (map (\x -> readMaybe x :: Maybe Double) (words s))
 
initState :: World
initState = World 
    { planets = 
        [ Planet { pos = (7.406e11, 0), vel = (0, 1.304e4), tray = [], pColor = orange, traylen = 0 } -- jupiter
        , Planet { pos = (1.496e11, 0), vel = (0, 29780),   tray = [], pColor = blue,   traylen = 0 } -- la tierra
        ]
    , iface  = Interface { iText = "", wsize = (1920, 1080) }
    , wScale = 5e-10
    , trans  = Translation { pressl = False, lastpos = (0,0), cord = (0,0) }
    }          

main = do
    play (InWindow "TP" (1920, 1080) (100,100))
         black
         (60*60*30*8)
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
deltaT = 3

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


