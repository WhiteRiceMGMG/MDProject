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
├── 原子に初速度を与える（シード値）
│
├── 初期の力を計算（compute_forces）
│
├── タイムステップループ開始
│   │
│   ├── 1. Velocity-Verlet法 前半（位置更新・速度半分）
│   ├── 2. 力の再計算（新しい位置に基づいて）
│   ├── 3. Velocity-Verlet法 後半（速度の残り半分）
│   ├── 4. 必要に応じて出力（例：座標・エネルギー）
│   │
│   └──（終了条件まで繰り返し）
│
└── 終了

 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
ファイル構成

 md_sim/
├── main.c            // メイン関数：シミュレーション全体の流れ
├── atom.h            // Atom構造体や関数のプロトタイプ
├── atom.c            // Atomの初期化・処理関数
├── force.h           // 力計算のプロトタイプ
├── force.c           // LJ力などの実装
├── integrator.h      // 時間発展関数のプロトタイプ
├── integrator.c      // Velocity-Verletなどの実装
├── param.h           // SystemParam構造体の定義
├── Makefile          // コンパイル用（あると便利）

 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
