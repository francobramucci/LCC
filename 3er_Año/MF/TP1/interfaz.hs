import Graphics.Gloss
import Graphics.Gloss.Data.ViewPort
import Graphics.Gloss.Interface.IO.Interact
import Text.Read (readMaybe)

type DVector = (Double, Double)

type World = (String, (Int, Int), [(DVector, DVector)])

-- data World = W {
--     s :: String,
--     p :: (Int, Int),
--     d :: [(Double, Double)]
-- } deriving (Show)

world2Pic :: World -> Picture
world2Pic (s, (x, y), _) = pictures [
    translate (-100) ((fromIntegral (div y 2 - 50))::Float) (scale 0.15 0.15 (color white (text ("Agregar: " ++ s)))),
    color yellow (circleSolid 10)
    ]

handler :: Event -> World -> World
handler (EventKey k ks _ _) (s, p, ds) = case (k, ks) of
                                              (SpecialKey KeyBackspace, Down) -> (sinit s, p, ds)
                                              (Char '\b', Down) -> (sinit s, p, ds) -- En wayland gloss captura el BS como un Char en vez de SpecialKey
                                              (Char c, Down) ->  (s ++ [c], p, ds)
                                              (SpecialKey KeySpace, Down) ->  (s ++ [' '], p, ds)
                                              (SpecialKey KeyEnter, Down) -> addPlanet (s,p,ds)
                                              _ -> (s, p, ds)
handler (EventResize (x, y)) (s, _, ds) = (s, (x,y), ds)
handler _ w = w

advance :: Float -> World -> World
advance _ w = w


initState :: World
initState = ("", (1920, 1080), [])

main = do
    play (InWindow "Interfaz" (1920, 1080) (100, 100)) black 60 initState world2Pic handler advance
    return ()

sinit :: String -> String
sinit s = if null s then s else init s

parseVectors :: String -> [Maybe Double]
parseVectors s =  (map (\x -> readMaybe x :: Maybe Double) (words s))

addPlanet :: World -> World
addPlanet (s, p, ds) = case parseVectors s of
                            [Just x, Just y, Just vx, Just vy] -> ([], p, ((x,y), (vx,vy)):ds)
                            _ -> (s, p, ds)


