cmlibAudio by ABCanG

【はじめに】
オーディオ系（？）をまとめたものです。
ミュート関連は競合しないようになっているはずです。

【モジュール情報】
　ファイル名：cmlibaudio.prx
　モジュール名：cmlibAudio
　ライブラリ名：cmliAaudio

【使い方】
　1.プログラムのソースファイルに"cmlibaudio.h"をインクルードしてください。
　　"libmenu.h"にはlibmenuの関数などが定義されています。

　2.プログラム内で"cmlibAudio"が読み込まれているかチェックして、必要に応じて読み込むようにしてください。
　　（詳しくはサンプルを見てください）

　3.ビルド時に、"cmlibaudio.S"を一緒にビルドしてください。
　　（例：Makefileに"OBJS += cmlibaudio.o"と記述）

　4.ライブラリである"cmlibaudio.prx"は"/seplugins/lib/"以下に配置するようにお願いします。


/////Changelog/////

*1.0 (2011.07.02)
[] 最初のリリース。
