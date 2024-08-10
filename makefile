default: RunAll

FolderBase = /eos/user/p/pchou/figs/hlt/20240810
ForestBase = /eos/cms/store/group/phys_heavyions_ops/pchou/Forest
HLTBase    = /eos/home-p/pchou/HLT2024/CMSSW_14_0_11/src/HLTrigger/Configuration/test/workstation/HLT_DIGI_CMSSW14011
UPText     = "pp ref, \#sqrt{s_{NN}} = 5.36 TeV, 2024 Simulation"

RunAll: RunPhoton RunEle RunDoubleEle

RunPhoton: Execute
	mkdir -p log
	./Execute_HLTperformance_QCDPhoton_ppref  --typeofdata "QCDPhoton_ppref_1400v172_dr05" \
	--folder "$(FolderBase)/QCDPhoton/" \
	--forestfile "$(ForestBase)/Pythia8_ppRef_QCDPhoton30_TuneCP5/QCDPhoton_20230524_miniAOD/240417_212103/" \
	--hltfile "$(HLTBase)/ppref_MC_QCDPhoton_1400v172_Macro_20240808/240809_151230/0000/*.root" \
	--uptext $(UPText) > log/QCDPhoton_ppref.out 2> log/QCDPhoton_ppref.err < /dev/null &

	./Execute_HLTperformance_QCDPhoton_ppref  --typeofdata "QCDPhoton_ppref_1400v172_EG10_dr05" \
	--folder "$(FolderBase)/QCDPhoton/" \
	--forestfile "$(ForestBase)/Pythia8_ppRef_QCDPhoton30_TuneCP5/QCDPhoton_20230524_miniAOD/240417_212103/" \
	--hltfile "$(HLTBase)/ppref_MC_QCDPhoton_1400v172_EG10_Macro_20240808/240809_151330/0000/*.root" \
	--uptext $(UPText) > log/QCDPhoton_ppref_EG10.out 2> log/QCDPhoton_ppref_EG10.err < /dev/null &

	./Execute_HLTperformance_QCDPhoton_ppref  --typeofdata "QCDPhoton_ppref_1400v172_noL1_dr05" \
	--folder "$(FolderBase)/QCDPhoton/" \
	--forestfile "$(ForestBase)/Pythia8_ppRef_QCDPhoton30_TuneCP5/QCDPhoton_20230524_miniAOD/240417_212103/" \
	--hltfile "$(HLTBase)/ppref_MC_QCDPhoton_1400v172_noL1_Macro_20240808/240809_151417/0000/*.root" \
	--uptext $(UPText) > log/QCDPhoton_ppref_noL1.out 2> log/QCDPhoton_ppref_noL1.err < /dev/null &


Execute: HLTperformance_QCDPhoton_ppref.cpp
	g++ HLTperformance_QCDPhoton_ppref.cpp -o Execute_HLTperformance_QCDPhoton_ppref `root-config --cflags --libs` -lASImage -std=c++17

RunEle: ExecuteEle
	mkdir -p log
	./Execute_HLTperformance_ee_ppref  --typeofdata "Zee_ppref_1400v172_dr05" \
	--folder "$(FolderBase)/Zee/" \
	--forestfile "$(ForestBase)/Zee_20240417_miniAOD/240418_050541/" \
	--hltfile "$(HLTBase)/ppref_MC_Zee_1400v172_Macro_20240808/240809_151517/0000/*.root" \
	--uptext $(UPText) > log/ee_ppref.out 2> log/ee_ppref.err < /dev/null &

	./Execute_HLTperformance_ee_ppref  --typeofdata "Zee_ppref_1400v172_EG10_dr05" \
	--folder "$(FolderBase)/Zee/" \
	--forestfile "$(ForestBase)/Zee_20240417_miniAOD/240418_050541/" \
	--hltfile "$(HLTBase)/ppref_MC_Zee_1400v172_EG10_Macro_20240808/240809_151551/0000/*.root" \
	--uptext $(UPText) > log/ee_ppref_EG10.out 2> log/ee_ppref_EG10.err < /dev/null &

	./Execute_HLTperformance_ee_ppref  --typeofdata "Zee_ppref_1400v172_noL1_dr05" \
	--folder "$(FolderBase)/Zee/" \
	--forestfile "$(ForestBase)/Zee_20240417_miniAOD/240418_050541/" \
	--hltfile "$(HLTBase)/ppref_MC_Zee_1400v172_noL1_Macro_20240808/240809_151625/0000/*.root" \
	--uptext $(UPText) > log/ee_ppref_noL1.out 2> log/ee_ppref_noL1.err < /dev/null &

ExecuteEle: HLTperformance_ee_ppref.cpp
	g++ HLTperformance_ee_ppref.cpp -o Execute_HLTperformance_ee_ppref `root-config --cflags --libs` -lASImage -std=c++17

RunDoubleEle: ExecuteDoubleEle
	mkdir -p log
	./Execute_HLTperformance_doublee_ppref  --typeofdata "doublee_ppref_1400v172_dr05" \
	--folder "$(FolderBase)/doublee/" \
	--forestfile "$(ForestBase)/Zee_20240417_miniAOD/240418_050541/" \
	--hltfile "$(HLTBase)/ppref_MC_Zee_1400v172_Macro_20240808/240809_151517/0000/*.root" \
	--uptext $(UPText) > log/doublee_ppref.out 2> log/doublee_ppref.err < /dev/null &

	./Execute_HLTperformance_doublee_ppref  --typeofdata "doublee_ppref_1400v172_EG10_dr05" \
	--folder "$(FolderBase)/doublee/" \
	--forestfile "$(ForestBase)/Zee_20240417_miniAOD/240418_050541/" \
	--hltfile "$(HLTBase)/ppref_MC_Zee_1400v172_EG10_Macro_20240808/240809_151551/0000/*.root" \
	--uptext $(UPText) > log/doublee_ppref_EG10.out 2> log/ee_ppref_EG10.err < /dev/null &

	./Execute_HLTperformance_doublee_ppref  --typeofdata "doublee_ppref_1400v172_noL1_dr05" \
	--folder "$(FolderBase)/doublee/" \
	--forestfile "$(ForestBase)/Zee_20240417_miniAOD/240418_050541/" \
	--hltfile "$(HLTBase)/ppref_MC_Zee_1400v172_noL1_Macro_20240808/240809_151625/0000/*.root" \
	--uptext $(UPText) > log/doublee_ppref_noL1.out 2> log/doublee_ppref_noL1.err < /dev/null &

ExecuteDoubleEle: HLTperformance_doublee_ppref.cpp
	g++ HLTperformance_doublee_ppref.cpp -o Execute_HLTperformance_doublee_ppref `root-config --cflags --libs` -lASImage -std=c++17

RunRate: ExecuteRate
	mkdir -p log
	./Execute_HLTrate_ppref \
	--mbpath "/eos/cms/store/group/phys_heavyions_ops/pchou/HLT_DIGI_CMSSW1321/ppref_MC_MB_1320V32/Macro/CRAB_UserFiles/ppref_MC_MB_1320V32_tag132X2023_Macro/230911_140716/0000/*.root" \
	> log/rate_ppref.out 2> log/rate_ppref.err < /dev/null &

ExecuteRate: HLTrate_ppref.cpp
	g++ HLTrate_ppref.cpp -o Execute_HLTrate_ppref `root-config --cflags --libs` -lASImage -std=c++17