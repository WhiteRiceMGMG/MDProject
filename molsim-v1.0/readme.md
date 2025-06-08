
gccがいります．

## Molecular Dynamics Simulation 
gccを用いてビルドし，簡単に実行できます．

## ビルドと実行方法
以下の手順でクローンし，ビルド&実行できます．
'''bash
git clone https://github.com/WhiteRiceMGMG/MDProject.git
cd MDProject/molsim-v1.0
make
./main

## 実装した

## 分子動力学法
分子集団の分子全てに運動方程式を用いて計算し，分子の運動を観測する手法．<br>
ニュートン第二法則を用いて運動を追跡する．<br>
速度Verlet法を用いて運動方程式の時間積分を行う．<br>
分子間の相互作用は Lennard-Jonesポテンシャル を用いる．<br>





