<style type="text/css">
<!--
	div.toc ul ul ul li { display: inline; }
-->
</style>

# REIMU plugins for Touhou replays User's Manual {: #UsersManual }

## Table of Contents {: #ToC }

[TOC]

----------------------------------------

## Introduction {: #Introduction }

これは、プラグイン型リプレイビュアー「[REIMU][REIMU]」用のプラグインです。

  [REIMU]: http://www.sue445.net/downloads/reimu.html

----------------------------------------

## Disclaimer {: #Disclaimer }

**本プラグインの利用は自己責任の下で実施して下さい。**

本プラグインの免責事項などの詳細は [License](#License) の通りとします。（つまり BSD 2-Clause License です。）

----------------------------------------

## Supported Titles {: #SupportedTitles }

### 対応済み {: #Supported }

対応している東方 Project の作品名・バージョン：

* th12replay.rpi: 東方星蓮船 ver. 1.00b
* th125replay.rpi: ダブルスポイラー ver. 1.00a
* th125bestshot.rpi: ダブルスポイラー ver. 1.00a

### 対応予定あり {: #WillSupport }

以下作品については、本プラグイン作者の原作プレイ進捗状況に伴って今後対応予定です：

* 妖精大戦争
* 東方神霊廟
* 東方輝針城

以下作品についても上記と同様ですが、本プラグイン作者は格ゲーが弾幕 STG 以上に下手なので、後回しです：

* 東方緋想天
* 東方非想天則
* 東方心綺楼

### 対応予定無し {: #NotSupported }

以下作品については REIMU 作者謹製プラグインがあるので、対応予定はありません：

* 東方萃夢想
* 東方永夜抄
* 東方花映塚
* 東方文花帖
* 東方風神録
* 東方地霊殿

以下作品については、REIMU 作者が公開していないのと同じ理由により、対応予定はありません：

* 東方紅魔郷
* 東方妖々夢

全作品の過去バージョンで作成されたリプレイファイルについては、本プラグイン作者の方での動作確認が困難なので、対応予定はありません。

----------------------------------------

## Environments {: #Environments }

### ビルド環境 {: #BuiltEnv }

* Windows 7 Professional SP1 (64bit) + Visual Studio Express 2012

### 動作確認済み環境 {: #TestedEnv }

* Windows XP Home Edition SP3 (32bit)
* Windows 7 Professional SP1 (64bit)
* Windows 8 (64bit)　※ th12replay.rpi のみ
* Windows 8.1 (64bit)

本プラグイン導入後の REIMU 起動時に「msvcr110.dll がない」といったメッセージが表示される場合、下記をインストールしてください。

* [Visual Studio 2012 更新プログラム 3 の Visual C++ 再頒布可能パッケージ][Runtime]

  [Runtime]: http://www.microsoft.com/ja-jp/download/details.aspx?id=30679

----------------------------------------

## Installation {: #Installation }

### インストール {: #Install }

Web からダウンロードした zip ファイルを任意の場所に展開し、\*.rpi ファイルを REIMU の plugin フォルダ内の任意の場所に格納してください。

### アンインストール {: #Uninstall }

格納した \*.rpi ファイルを削除して下さい。本プラグインはレジストリの書き換えをしません。

----------------------------------------

## How to Use {: #HowToUse }

基本的に REIMU 作者謹製プラグインと同様ですので、そちらの readme.txt や REIMU 本体のヘルプを参照してください。

----------------------------------------

## Notes {: #Notes }

以下の注意点は、本プラグインの今後の更新により変更される可能性があります。

* プラグインごとの設定（コメントの表記方法を変えるなど）は、今のところ対応予定はありません。
* REIMU 本体の「リストビュー作成時に最近読み込んだフォルダの履歴を自動的に読み込む」設定を有効にしていても、地霊殿以降の作品については読み込んでくれないようです。（REIMU 本体の不具合？）  
REIMU 本体の設定ファイル (reimu.ini) 内の `RecentDir1` を手動で設定すれば読み込むようになります。

----------------------------------------

## Copyrights {: #Copyrights }

* 東方 Project の各作品の著作権は[上海アリス幻樂団][ZUN]様にあります。本プラグイン作者とは一切関係がありません。
* REIMU の著作権は [sue445][sue445] 様にあります。本プラグイン作者とは一切関係がありません。
* 本プラグインの著作権は IIHOSHI Yoshinori ([Web site][MyWeb], [Twitter][MyTwitter]) にあります。

  [ZUN]: http://www16.big.or.jp/~zun/ "上海アリス幻樂団"
  [TasoFro]: http://www.tasofro.net/ "黄昏フロンティア"
  [sue445]: http://www.sue445.net/ "sue445.NET"
  [MyWeb]: http://www.colorless-sight.jp "Colorless Sight"
  [MyTwitter]: http://twitter.com/iihoshi

----------------------------------------

## License {: #License }

Copyright (c) 2013, IIHOSHI Yoshinori  
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------

## ChangeLog {: #ChangeLog }

Ver. 20131110

* ダブルスポイラーに対応
	* th125replay.rpi: リプレイファイル用
	* th125bestshot.rpi: ベストショットファイル用

Ver. 20130929\_2

* Windows XP への対応漏れを修正
* このマニュアルを追加

Ver. 20130929

* 公開開始
* 東方星蓮船に対応
