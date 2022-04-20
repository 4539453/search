Example search queries:
Mulsanne & mulliner - W.O.
Julius - caesar
(osman | Asaf Jah VII) & billion 

Query Grammar:
expr  : uset (NOT uset)\*
uset  : nset (OR nset)\*
nset  : set (AND set)\*
set   : WORD | LPAREN expr RPAREN

nset('∩'set) - result of intersections
uset('∪'set) - result of union

Preference: AND(&) > OR(|) > NOT(-)

