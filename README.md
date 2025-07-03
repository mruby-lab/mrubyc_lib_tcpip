# ESP32_mruby/c

- ESP32でmruby/cを動作させ、通信機能を使えるようにする

# 注意事項

- `hal_init`がArduinoのライブラリと衝突するので、`mrbc_hal_init`に書き換える
    - hal.c の `hal_init` を `mrbc_hal_init` に変更（1か所）
    - rrt0.c の `hal_init` を `mrbc_hal_init` に変更（1か所）