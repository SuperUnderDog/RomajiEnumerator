RomajiEnumerator

  usage: RomajiEnumerator [option]
  
  required
    none
  
  option
    -? -h                        // Help
    -o <output word list file>   // (default stdout)
    -i <input word list file>    // (default stdin)

  example:
    RomajiEnumerator -i hoge.txt -o tmpout.txt



今のところVS2015用
しかもマルチバイト専用
Linux BSD 辺りにhogeろうと思ったんだけどUTFどうしようでそのまま
入出力ファイルの指定を無視すると標準入出力を使う

hoge.txt
>>>
ほげ
ふが
ぴよう
>>>

を食わせると

tmpout.txt
<<<
hoge
fuga
huga
piyo
piyoh
piyou
<<<

が出てくる
