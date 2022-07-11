#define STRINGIFY(s) STRINGIFYI(s)
#define STRINGIFYI(s) #s
#define RODATA(s) STRINGIFY(.rodata. ## s)

.section RODATA(SYMBOL)
.global SYMBOL
SYMBOL:
.incbin STRINGIFY(FILE)
.size SYMBOL,.-SYMBOL
