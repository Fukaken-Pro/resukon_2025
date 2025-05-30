# Resukon 2025 Kurengame

このプロジェクトは、Arduinoを使用してサーボモーターやモーターを制御するプログラムです。以下に各ファイルの概要と使い方を説明します。

## ファイル構成

- **resukon_2025_kurengame.ino**  
  メインのArduinoスケッチファイルです。サーボモーターやモーターの初期化、シリアル通信の処理、ループ内での制御ロジックが記述されています。

- **resukon_servo.h / resukon_servo.cpp**  
  サーボモーターを制御するクラス`Servoangle`を定義しています。サーボの角度変更やリセット機能を提供します。

- **resukon_moter.h / resukon_moter.cpp**  
  モーターを制御するクラス`Moterconfig`を定義しています。アナログ出力やデジタル出力を用いたモーター制御機能を提供します。

## セットアップ

1. Arduino IDEを開き、`resukon_2025_kurengame.ino`を開きます。
2. 必要なライブラリ（例: Servoライブラリ）がインストールされていることを確認してください。
3. Arduinoボードを接続し、適切なポートとボードを選択します。
4. スケッチをアップロードします。

## 使用方法

1. Arduinoを起動し、シリアルモニタを開きます（ボーレート: 115200）。
2. シリアル通信を通じて、以下の形式でデータを送信します:
- `x`: データの種類（`BOTAN`またはスティックのインデックス）
- `y`: ボタンまたはスティックのインデックス
- `z`: 値（ボタンの状態またはスティックの値）

3. ボタンやスティックの入力に応じて、サーボモーターやモーターが制御されます。

## クラスの詳細

### Servoangleクラス

- **プロパティ**
| | プロパティ             | 役割                     | 初期値   |
|------------------------|--------------------------|----------|
| `upbotan` / `downbotan`| サーボを動かすボタン     | 0        |
| `limit`                | サーボ角度の上限と下限   | 180 / 0  |
| `angle`                | サーボの角度             | 0        |

- **メソッド**
  - `change()`: ボタン入力に応じて角度を変更
  - `reset()`: サーボ角度を初期値にリセット


### Moterconfigクラス

- **プロパティ**
  - `moterpow`: モーターの出力状態
  - `convalue`: アナログ制御値
  - `botanf` / `botanb`: モーターを動かすボタンの状態を保存する
- **メソッド**
  - `analogpower()`: アナログ値でモーターを制御
  - `digitalpower()`: ボタン入力でモーターを制御
  - `reset()`: モーターを停止

## 注意事項

- ハードウェアの接続が正しいことを確認してください。
- サーボモーターやモーターの動作範囲を超えないように注意してください。
- シリアル通信の形式が正しいことを確認してください。

以上がこのプロジェクトの使い方です。