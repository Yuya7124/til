import qrcode
import qrcode.image.svg

class MakeQR: # クラス定義
  def __init__(self, output):  # コンストラクタの引数にoutputを設定
    self.url = ""  #URLの初期値を空にする
    self.output = output  # 引数からアウトプット用のファイル名を設定

  def make(self):  # makeメゾットの定義(QRコード生成・保存)
    factory = qrcode.image.svg.SvgImage
    img = qrcode.make(self.url, image_factory = factory)
    img.save(self.output)

  def run(self):
     url = input("URLを入力してください: ")
     if not url.startswith("http"):  # コンソールから入力された文字列が、httpから始まっているか？
        print("入力された文字列が、http から始まっていません")  # httpから始まらない場合はメッセージを出力
        return  # runメゾットの実行をここで終えるためにreturn文を使う
     self.url = url  # 入力されたURLをインスタンス属性にする
     self.make()  # makeメゾットを実行してQRコード生成と保存

if __name__ == "__main__":
    import sys # sysライブラリをインポート
    args = sys.argv  # コマンドライン引数を取得する
    output = args[1]  # コマンドライン引数から、一つ目の引数をoutput変数に入れる
    app = MakeQR(output)  # MakeQRクラスをインスタンス化する際に、outputを指定する
    # app.make()  # makeメゾットを呼び出し、QRコード画像が生成され、保存する
    app.run()  # runメゾットを実行