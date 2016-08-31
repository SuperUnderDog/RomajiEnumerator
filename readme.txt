Shift-JIS のひらがなの文字列を、複数のパターンでローマ字に変換して列挙

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



今のところVS2015用、しかもマルチバイト専用
Linux BSD 辺りにhogeろうと思ったんだけどUTFどうしようでそのまま
入出力ファイルの指定を省略すると、標準入出力を使う
入力にはワイルドカードが使用可能
標準出力は Win の仕様上 CRLF、-o で出力すると LF

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
