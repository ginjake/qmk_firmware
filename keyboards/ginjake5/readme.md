# 自作キーボードginjake名刺

# 必要なもの
・ProMicro  
・Cherry MX互換キースイッチ 5つ  
・リセットスイッチ 1つ  
・イカした抵抗  

# 組み立て方

1 ProMicroを組み立てます  
2 キースイッチをつけます  
3 リセットスイッチをつけます  
4 ファームを焼いて終わり  
5 上側は飾りなので、適当な抵抗をつけてもつけなくても大丈夫

# 環境構築
本家ドキュメント参照  
https://docs.qmk.fm/#/newbs_getting_started

#LEDについて
sk6812miniに対応していますが、上級者向けなので分かっている人以外はおすすめしません

# ファームの焼き方
qmk compile -kb ginjake -km default:flash  
を実行した後、リセットスイッチを1回(ProMicroによっては2回素早く)押す

![完成イメージ](https://user-images.githubusercontent.com/16838187/184341818-c454eb21-9cc6-4fe3-9c68-dc434e870fe1.png)

Keyboard Maintainer: [ginjake](https://github.com/ginjake) [Twitter:@sirojake](https://twitter.com/sirojake)  
Hardware Supported: Pro Micro, 

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb ginjake5 -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/n
