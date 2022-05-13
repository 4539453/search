Example search queries:

Jane Austen | Louis Joseph \
Jane ~Austen

Query Grammar:

- expr  : uset (NOT uset)
- uset  : nset (OR nset)
- nset  : set (AND set)
- set   : WORD | LPAREN expr RPAREN

nset('∩'set) - result of intersections \
uset('∪'set) - result of union