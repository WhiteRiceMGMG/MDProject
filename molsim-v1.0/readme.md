## Molecular Dynamics Simulation 
gccを用いてビルドし，簡単に実行できます．

## ビルドと実行方法
以下の手順でクローンし，ビルド & 実行できます：

```bash
git clone https://github.com/WhiteRiceMGMG/MDProject.git
cd MDProject/molsim-v1.0
make
./main
```

## 実装した機能
速度Verlet法を用いて運動方程式の時間積分を行う．<br>
分子間の相互作用は Lennard-Jonesポテンシャル を用いる．<br>

## 拡張予定
境界条件を追加．





