all:
	g++ -o exec matrix.cpp
test-n:
	sudo perf stat -o test-n.txt -e L1-dcache-loads,L1-dcache-load-misses,branches,branch-misses ./exec 1000 n
test-i:
	sudo perf stat -o test-i.txt -e L1-dcache-loads,L1-dcache-load-misses,branches,branch-misses ./exec 1000 i
test-u:
	sudo perf stat -o test-u.txt -e L1-dcache-loads,L1-dcache-load-misses,branches,branch-misses ./exec 1000 u
reset:
	rm exec
	rm test.txt
	rm results/raw/*.txt -f
