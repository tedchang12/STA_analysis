# STA_analysis
#程式說明
電路分析中時程分析是設計電路上很重要的一個考量，在此程式中我建立了一個tool，可以產生電路中所有的True Path，藉此來找出哪些區塊是可以進行加速的。
#使用方法
將Verilog model檔案匯入取得節點結構，再將Verilog gate-level netlist轉成ＡＯＶ Ｎetwork進行分析。
使用./a.out verlog.v case.v即可產生所有true path。
#程式DEMO
![Image of demo](https://github.com/tedchang12/STA_analyisis/blob/master/Case1.png)
![Image of demo](https://github.com/tedchang12/STA_analyisis/blob/master/Case2.png)
![Image of demo](https://github.com/tedchang12/STA_analyisis/blob/master/Case3.png)
![Image of demo](https://github.com/tedchang12/STA_analyisis/blob/master/Case4.png)
![Image of demo](https://github.com/tedchang12/STA_analyisis/blob/master/Case5.png)
