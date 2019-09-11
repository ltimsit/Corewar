.name "ld"
.comment ""

live %1
test:live %5
live %6
ld 1,r12
st r12,0
ld 512,r3
st r3,0
ld :test,r4;:
st r4,r14
