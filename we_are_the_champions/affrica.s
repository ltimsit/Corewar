.name "aff"
.comment "aff"

sti r1, %1, %:livel
affff: ld %66, r1
aff r1
ld %111, r1
aff r1
ld %110, r1
aff r1
ld %106, r1
aff r1
ld %111, r1
aff r1
ld %117, r1
aff r1
ld %114, r1
aff r1
ld %32, r1
aff r1
ld %108, r1
aff r1
ld %101, r1
aff r1
ld %115, r1
aff r1
ld %32, r1
aff r1
ld %108, r1
aff r1
ld %111, r1
aff r1
ld %117, r1
aff r1
ld %108, r1
aff r1
ld %111, r1
aff r1
ld %117, r1
aff r1
ld %115, r1
aff r1
ld %32, r1
aff r1
ld %33, r1
aff r1
and r1, %0, r1
aff r1
livel: live %1
zjmp %:affff
