# STA_analysis
#程式說明
In the circuit design, static timing analysis is a main concern that help us to find blocks to speed up this circuit. As so, I design a tool to find the path which belong to True Path, in that we can dertermine which block we can speedup.
#使用方法
將Verilog model檔案匯入取得節點結構，再將Verilog gate-level netlist轉成ＡＯＶ Ｎetwork進行分析。
使用./a.out verlog.v case.v即可產生所有true path。
#程式DEMO
![Image of demo](https://github.com/tedchang12/STA_analyisis/blob/master/Case1.png)
![Image of demo](https://github.com/tedchang12/STA_analyisis/blob/master/Case2.png)
![Image of demo](https://github.com/tedchang12/STA_analyisis/blob/master/Case3.png)
![Image of demo](https://github.com/tedchang12/STA_analyisis/blob/master/Case4.png)
![Image of demo](https://github.com/tedchang12/STA_analyisis/blob/master/Case5.png)
