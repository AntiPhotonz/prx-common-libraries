/**************
* prxlibmenu
***************/

by wn
sample by SnyFbSx

※テスト版。文字描画の前にフォントをロードしてください。

【はじめに】
　prxlibmenuはlibmenu(v1.5)の関数群をひとつのprxにまとめた動的ライブラリです。
　他のプログラムにlibmenu(v1.5)と同等の機能を提供します。

【モジュール情報】
　ファイル名：prxlibmenu.prx
　モジュール名：prxlibmenu
　ライブラリ名：prxlibmenu

【使い方】
　1.プログラムのソースファイルに"libmenu.h"をインクルードしてください。
　　"libmenu.h"にはlibmenuの関数などが定義されています。

　2.プログラム内で"prxlibmenu"が読み込まれているかチェックして、必要に応じて読み込むようにしてください。また、文字を描画する場合は、"libmLoadFont"で必要なフォントをロードしてください。
　　（サンプル："sample/checkmod.c"）

　3.ビルド時に、"prmlibmenu.S"を一緒にビルドしてください。
　　（例：Makefileに"OBJS += prxlibmenu.o"と記述）

【さいごに】
　libmenuの作者はmaxemさんです。ありがとうございます。
　libmenuの使い方については、libmenuを参考にしてください。
　ライブラリである"prxlibmenu.prx"は"/seplugins/lib/"以下に配置するようにお願いします。
　フォントは"/seplugins/lib/font"に配置してください。
