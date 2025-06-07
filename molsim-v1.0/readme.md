使い方(多分)　そのままコピペしてどうぞ
gccがいります．
-------------------------------------------------------------------
git clone https://github.com/WhiteRiceMGMG/MDProject.git
cd MDProject/molsim-v1.0
make
./main
-------------------------------------------------------------------




##プロトタイプ##
LJポテンシャルとVelocity Verlet法のみ再現
セルはない
原子は2つだけ初期配置で置けるだけ

次やりたいこと
せるの概念作る
原子入力で行けるように



参考
https://polymer.apphy.u-fukui.ac.jp/~koishi/lecture/mol_sim.php#sim_program
https://qiita.com/kaityo256/items/2356fff922938ae3c87c







Features
 - Basic molecular dynamics simulation
 - Velocity-Verlet integration
 - Lennard-Jones potential
 - Configurable time step, particle count
 - File output for trajectories 

Build & Run
 - GCC | Clang
 - Make (optional)
 - A posix compliant environment Linux, WSL, macOS

Compile
 - gcc -o md_sim src/main.c src/particle.c src/simulation.c -lm
 

 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 フローチャート

開始
│
├── システムパラメータ初期化（例：時間刻み, 粒子数, ε, σ など）
│
├── 原子構造体の配列を用意
│
├── 原子の初期配置を設定（ハードコード）
│
├── 原子に初速度を与える（シード値？）
│
├── 初期の力を計算（compute_forces）
│
├── タイムステップループ開始
│   │
│   ├── 1. Velocity-Verlet法 前半
│   ├── 2. 力の再計算（
│   ├── 3. Velocity-Verlet法 後半
│   ├── 4. 必要に応じて出力（
│   │
│   └──（終了条件まで繰り返し）
│
└── 終了

 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
ファイル構成

 md_sim/
├── main.c         
├── atom.h         
├── atom.c         
├── force.h        
├── force.c        
├── integrator.h   
├── integrator.c   
├── param.h        
├── Makefile       

 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
