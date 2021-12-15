# robosys_report1
ロボットシステム学「課題１」

# 概要
講義ビデオを見ながらデバイスドライバを作成し、改造する。また、著作権やライセンスの記述も考慮する。

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

# 回路の説明
今回使用する回路は下図のように接続する。
![S__21561397](https://user-images.githubusercontent.com/94817675/146217858-44289919-2dc6-474b-b083-f7f961fef952.jpg)

また今回は、LEDのカソードとラズパイ４の「Ground」を接続し、抵抗(240Ω)と「GPIO 25」を接続している。

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
URL : 

# ライセンス
GNU General Public License v2.0

また、以下のURLから閲覧可能
URL : https://github.com/SakaTaku2/robosys_report1/blob/3394557b1d9618ffd1dcc6306e8000a87f2b1b60/LICENSE

 
