Shift-JIS �̂Ђ炪�Ȃ̕�������A�����̃p�^�[���Ń��[�}���ɕϊ����ė�

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



���̂Ƃ���VS2015�p�A�������}���`�o�C�g��p
Linux BSD �ӂ��hoge�낤�Ǝv�����񂾂���UTF�ǂ����悤�ł��̂܂�
���o�̓t�@�C���̎w����ȗ�����ƁA�W�����o�͂��g��
���͂ɂ̓��C���h�J�[�h���g�p�\
�W���o�͂� Win �̎d�l�� CRLF�A-o �ŏo�͂���� LF

hoge.txt
>>>
�ق�
�ӂ�
�҂悤
>>>

��H�킹���

tmpout.txt
<<<
hoge
fuga
huga
piyo
piyoh
piyou
<<<

���o�Ă���
