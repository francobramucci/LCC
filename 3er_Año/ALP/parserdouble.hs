import Text.ParserCombinators.Parsec.Prim
import Text.ParserCombinators.Parsec.Combinator
import Text.ParserCombinators.Parsec.Char

parseDouble :: Parser Bool
parseDouble = do
    spaces
    char '-' <|> return 'T'
    many1 digit
    (char '.' >> many1 digit) <|> return "T"
    (char 'e' >> (char '-' <|> return 'T') >> many1 digit) <|> return "T"
    return True
    <|> return False

