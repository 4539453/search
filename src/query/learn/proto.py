INTEGER, PLUS, MINUS, EOF = 'INTEGER', 'PLUS', 'MINUS', 'EOF'

class Token:
    def __init__(self, typee, value):
        self.type = typee;
        self.value = value;

    def __str__(self):
        return 'Token({typee}, {value})'.format(typee = self.type, value = repr(self.value))

    def __repr__(self):
        return self.__str__()

class Interpreter():
    def __init__(self, text):
        self.text = text
        self.pos = 0
        self.current_char = self.text[self.pos]
        self.current_token = None
    
    #Lexer
    def error(self):
        raise Exception('Invalid syntax')
    
    def advance(self):
        self.pos += 1
        if self.pos > len(self.text)-1:
            self.current_char = None
        else:
            self.current_char = self.text[self.pos]

    def skip_whitespace(self):
        while self.current_char is not None and self.current_char.isspace():
            self.advance()

    def integer(self):
        result = ''
        while self.current_char is not None and self.current_char.isdigit():
            result += self.current_char
            self.advance()
        return int(result)

    def get_next_token(self):
        
        if self.current_char is None:
            return Token(EOF, None)
       
        if self.current_char.isspace():
            self.skip_whitespace()
        
        if self.current_char.isdigit():
            return Token(INTEGER, self.integer())
        
        if self.current_char == '+':
            self.advance()
            return Token(PLUS, '+')
        
        if self.current_char == '-':
            self.advance()
            return Token(MINUS, '-')
        
        self.error()

    #Parser/Interpreter

    def eat(self, token_type):
        if self.current_token.type == token_type:
            self.current_token = self.get_next_token()
        else:
            self.error()
    
    def term(self):
        token = self.current_token
        self.eat(INTEGER)
        return token.value

    def expr(self):
        self.current_token = self.get_next_token()
        result = self.term()

        while self.current_token.type in (MINUS, PLUS):
            token = self.current_token
            if token.type == PLUS:
                self.eat(PLUS)
                result+=self.term()
            else:
                self.eat(MINUS)
                result-=self.term()
        return result

def main():
    while True:
        try:
            # To run under Python3 replace 'raw_input' call
            # with 'input'
            text = input('calc> ')
        except EOFError:
            break
        if not text:
            continue
        interpreter = Interpreter(text)
        result = interpreter.expr()
        print(result)


if __name__ == '__main__':
    main()
