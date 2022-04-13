
class Lexer:
    def __init__(self,text):
        self.text = text
        self.pos = 0
        self.current_char = self.text[self.pos]
        self.preprocresult = ''

    def error(self):
        raise Exception('Invalid character')
    
    def advance(self):
        self.pos += 1
        if self.pos > len(self.text)-1:
            self.current_char = None
        else:
            self.current_char = self.text[self.pos]
    
    def isSpecialChar(self):
        return self.current_char in ('(', ')', '|', '&', '~')
    
    def prevIsSpecialChar(self):
        return self.preprocresult[len(self.preprocresult)-1] in ('(', ')', '|', '&', '~')
    
    def skip_whitespace(self):
        while self.current_char is not None and self.current_char.isspace():
            self.advance()

    def word(self):
        result = ''
        while self.current_char is not None and not self.current_char.isspace() and not self.isSpecialChar():
            result += self.current_char
            self.advance()
        return result

    def get_next_token(self):
        if self.current_char is None:
            return None
       
        if self.current_char.isspace():
            self.skip_whitespace()
            if not self.isSpecialChar() and not self.prevIsSpecialChar():
                return '&'

        if not self.isSpecialChar():
            return self.word()
        
        if self.isSpecialChar():
            char = self.current_char
            self.advance()
            return char
        
        self.error()
    def preprocess(self):
        self.preprocresult = ''
        current_token = self.get_next_token()
        while current_token is not None:
            self.preprocresult += current_token
            current_token = self.get_next_token()
        result = self.preprocresult
        self.__init__(result) 
        return result
    
    def text2(self):
        return self.text

def main():
    while True:
        try:
            text = input('query> ')
        except EOFError:
            break
        if not text:
            continue
        lexer = Lexer(text)
        print(lexer.preprocess())
        print(lexer.text2())

if __name__ == '__main__':
    main()
