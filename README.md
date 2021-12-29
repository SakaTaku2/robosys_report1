# robosys_report1
ロボットシステム学「課題１」

# 概要
講義ビデオを見ながらデバイスドライバを作成する。

# 動作環境
以下の環境を用いて動作確認を行う。

OS : ubuntu 20.04 server

# 準備
今回のデバイスドライバには以下のものが必要になる。

・Raspberry Pi 4 Computer Model B (4GB RAM)

・ジャンパーワイヤ(オス-メス) ×２

・抵抗(240Ω) ×１

・青色ダイオード ×１

・ブレッドボード ×１

# 回路の説明![２．直線のグラフ](https://user-images.githubusercontent.com/94817675/147661807-3236aaad-7c9c-46d3-a410-741921fbdd56.png)

今回使用する回路は下図のように接続する。
![S__21561397](https://user-images.githubusercontent.com/94817675/146217858-44289919-2dc6-474b-b083-f7f961fef952.jpg)


今回は、ラズパイ４の「GPIO 25」と抵抗(240Ω)を接続し、抵抗(240Ω)とLEDのアノードを接続、そしてLEDのカソードとラズパイ４の「Ground」を接続している。
# インストール方法
以下のコマンドをターミナルで実行する。

  ```
  $ git clone git@github.com:SakaTaku2/robosys_report1.git
 
  $ cd robosys_report1/
  
  $ make
  
  $ sudo insmod myled.ko
  
  $ sudo chmod 666 /dev/myled0
  ```

# 実行方法
・LEDを点灯させる

  ```
  $ echo 1 > /dev/myled0
  ```
  
・LEDを消灯させる

  ``` 
  $ echo 0 > /dev/myled0
  ```
  
# サンプル動画
URL : https://youtu.be/2hP8krfeIx0

# ライセンス
GNU General Public License v2.0
