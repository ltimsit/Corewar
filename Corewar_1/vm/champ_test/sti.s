.name "sti"
.comment " "

live %1
live %2
test: 
	live %7
	live %2
	 sti r1,%:test, %0 #RDD
	 sti r1, r1, %0    #RRD
	 sti r1, 1, %0 #RID
