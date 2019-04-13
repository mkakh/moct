# moct
moctはmouse remote controllerの略です.   
無線マウスをcmusのリモコンにしたくて作ったプログラムです．

## Usage
ソースコードのdefineのところを自分の環境に合わせて使ってください．   
`cat /proc/bus/input/devices`で確認することが出来ます．


デバイスを扱うのでroot権限で実行してください．

`make`→`make install`→`moct`で使えます．

`make uninstall`にも対応しています

参考URL：http://www.nakatayuki.com/archives/1061180296.html
