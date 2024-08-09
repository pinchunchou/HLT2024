
default: RunAll

RunAll: RunPhoton RunEle RunDoubleEle

RunPhoton: Execute
	mkdir -p log
	./Execute_HLTperformance_QCDPhoton_ppref > log/QCDPhoton_ppref.out 2> log/QCDPhoton_ppref.err < /dev/null &

Execute: HLTperformance_QCDPhoton_ppref.cpp
	g++ HLTperformance_QCDPhoton_ppref.cpp -o Execute_HLTperformance_QCDPhoton_ppref `root-config --cflags --libs` -lASImage -std=c++17

RunEle: ExecuteEle
	mkdir -p log
	./Execute_HLTperformance_ee_ppref > log/ee_ppref.out 2> log/ee_ppref.err < /dev/null &

ExecuteEle: HLTperformance_ee_ppref.cpp
	g++ HLTperformance_ee_ppref.cpp -o Execute_HLTperformance_ee_ppref `root-config --cflags --libs` -lASImage -std=c++17

RunDoubleEle: ExecuteDoubleEle
	mkdir -p log
	./Execute_HLTperformance_doublee_ppref > log/doublee_ppref.out 2> log/doublee_ppref.err < /dev/null &

ExecuteDoubleEle: HLTperformance_doublee_ppref.cpp
	g++ HLTperformance_doublee_ppref.cpp -o Execute_HLTperformance_doublee_ppref `root-config --cflags --libs` -lASImage -std=c++17

RunRate: ExecuteRate
	mkdir -p log
	./Execute_HLTrate_ppref > log/rate_ppref.out 2> log/rate_ppref.err < /dev/null &

ExecuteRate: HLTrate_ppref.cpp
	g++ HLTrate_ppref.cpp -o Execute_HLTrate_ppref `root-config --cflags --libs` -lASImage -std=c++17