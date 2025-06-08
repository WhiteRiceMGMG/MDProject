
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
gccがいります．


<pre>bash git clone https://github.com/WhiteRiceMGMG/MDProject.git
cd MDProject/molsim-v1.0
make 
./main </pre>

#分子動力学法
分子集団の分子全てに運動方程式を用いて計算し，分子の運動を観測する手法．
ニュートン第二法則を用いて運動を追跡する．
$$
m_i \frac{d^2 \mathbf{r}_i(t)}{dt^2} = \mathbf{F}_i(t)
$$