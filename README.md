# FMODTapeStopPlugin

> **このREADMEは GitHub copilot が作成しました。**

FMOD 用の **TapeStop DSP プラグイン** です。音声の再生速度やピッチを徐々に落とし、テープ停止のような効果を狙うことを目的としています。

## 特徴

- FMOD DSP プラグインとして実装
- 責務を分割した構成
  - `src/Domain`: 基本アルゴリズムや補助クラス
  - `src/UseCase`: TapeStop の振る舞いをまとめる層
  - `src/InterfaceAdapter`: FMOD のパラメータ入出力コールバック
  - `src/Framework`: FMOD DSP のエントリポイントとコールバック
- Windows + CMake を前提にビルド可能

## 前提環境

- Windows
- CMake 3.28 以上
- C++20 対応コンパイラ（MSVC / MinGW など）
- FMOD Studio API の SDK

## FMOD SDK の配置

このプロジェクトでは、FMOD SDK をリポジトリ直下の `ThirdParty` に置く想定です。

必要な構成:

```text
ThirdParty/
  inc/
    fmod_common.h
    fmod_dsp.h
    ...
  lib/
    fmod_vc.lib
    fmodL_vc.lib
    fmodstudio_vc.lib
    fmodstudioL_vc.lib
    ...
```

> `CMakeLists.txt` は `ThirdParty/inc` と `ThirdParty/lib` を参照します。

## ビルド方法

### CMake でビルド

```powershell
cmake -S "D:\PandD\FMODTapeStopPlugin" -B "D:\PandD\FMODTapeStopPlugin\cmake-build-debug"
cmake --build "D:\PandD\FMODTapeStopPlugin\cmake-build-debug"
```

生成物は `FMODTapeStopPlugin` の DLL です。

### 既存テストをビルド

`tests/Makefile` が用意されています。Linux / MSYS2 / WSL 系の環境で `make` が使える場合は次のように実行できます。

```bash
cd tests
make
```

テスト対象:

- `test_ParameterGetCallbacks.cpp`
- `test_DSPCallbacks.cpp`

## GitHub Actions での自動ビルド

`.github/workflows/build.yml` で、Windows の CMake ビルドを自動化しています。

### ポイント

- リポジトリには `ThirdParty` を含めず、CI 実行時に Google Drive から `ThirdParty.zip` を取得します。
- 取得後に `ThirdParty/` として展開し、そのまま CMake ビルドに使います。
- Google Drive FILE_ID は workflow 内で設定済みです。

### 使い方

1. リポジトリに workflow を push する
2. Google Drive 側で `ThirdParty.zip` にアクセスできる共有設定にする
3. push / pull request / 手動実行で自動ビルドが走る

### CI の成果物

workflow 実行後、Actions の Artifacts から以下を取得できます。

- `FMODTapeStopPlugin-windows`

artifact にはビルド成果物（`dll`）と `CMakeCache.txt` が含まれます。

### 重要

この構成は Windows 向けです。`ThirdParty.zip` には `ThirdParty/inc` と `ThirdParty/lib` が含まれている必要があります。

## ディレクトリ構成

```text
src/
  Domain/
    DelayLine.cpp
    DelayLine.h
    OnePoleLowpass.cpp
    OnePoleLowpass.h
  UseCase/
    TapeStopEngine.cpp
    TapeStopEngine.h
    TapeStopParameters.h
  InterfaceAdapter/
    ParameterDesc.cpp
    ParameterDesc.h
    ParameterGetCallbacks.cpp
    ParameterGetCallbacks.h
    ParameterIndex.h
    ParameterSetCallbacks.cpp
    ParameterSetCallbacks.h
  Framework/
    DSPCallbacks.cpp
    DSPCallbacks.h
    DSPDesc.cpp
    DSPDesc.h
    TapeStopInternalData.h
    FmodAllocator.h
ThirdParty/
  inc/
  lib/
tests/
  test_DSPCallbacks.cpp
  test_ParameterGetCallbacks.cpp
  Makefile
```

## 実装メモ

- FMOD との接続点は `src/Framework/DSPDesc.cpp` の `FMODGetDSPDescription()` です。
- DSP コールバックは `src/Framework/DSPCallbacks.cpp` にあります。
- パラメータ定義は `src/InterfaceAdapter/ParameterDesc.cpp` で初期化しています。

## 注意点

### 1. `FMOD_RESULT` や `F_CALL` のエラー

FMOD のヘッダは `fmod_common.h` → `fmod_dsp.h` の順で読む前提です。`FMOD_RESULT` や `F_CALL` が解決できない場合は、

- `ThirdParty/inc` のヘッダが正しく参照されているか
- テスト用の `tests/include` が本番ビルドに混ざっていないか
- `using namespace` や独自定義で名前が衝突していないか

を確認してください。

### 2. 読み込み時にクラッシュする場合

FMOD Studio でプラグインを読み込むときに落ちる場合は、以下を疑ってください。

- `FMODGetDSPDescription()` が正しくエクスポートされているか
- コールバック関数の呼び出し規約 `F_CALL` が一致しているか
- `plugindata` の初期化と解放が対になっているか
- `dsp_state->functions` や `alloc/free` が `nullptr` でないか

### 3. パラメータの初期化

`ParameterDesc.cpp` の `InitParameterDescs()` は一度だけ呼ばれる想定です。パラメータ配列 `s_Params` の初期化順序を崩さないようにしてください。

## 開発時の確認ポイント

- `src/Framework/DSPDesc.cpp` の `tapestopDesc` が 1 箇所で定義されているか
- `src/Framework/DSPCallbacks.cpp` と各ヘッダで宣言と定義が一致しているか
- FMOD Studio 側の SDK バージョンと `ThirdParty/inc` のバージョンが一致しているか

## ライセンス

FMOD SDK 自体は Firelight Technologies のライセンス条件に従ってください。

