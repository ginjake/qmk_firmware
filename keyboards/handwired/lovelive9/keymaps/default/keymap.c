#include QMK_KEYBOARD_H
#include "raw_hid.h"
//#include "v1.h"

//Following line allows macro to read current RGB settings

rgblight_config_t RGB_current_config;

#define KC_KANJI KC_GRV

enum layer_number {
    _DEFAULT = 0,
    _BLEND
};


// カスタムキーコードを追加
enum custom_keycodes {
  PL1_BLEND = SAFE_RANGE,  // 短押し：プレイリスト1、長押し：ブレンドレイヤー
  PREV_VIDEO,              // 前の動画へ
  REWIND_15S,              // 15秒巻き戻し
  REWIND_1S,               // 1秒巻き戻し
  PLAY_STOP,               // 再生/停止
  FORWARD_5S,              // 5秒先へ
  FORWARD_15S,             // 15秒先へ
  NEXT_VIDEO,              // 次の動画へ
  PLAYLIST2,               // プレイリスト2選択
  
  // ブレンドレイヤー用
  TO_DEFAULT_P1,           // デフォルトレイヤー切り替え＆プレイリスト1選択
  BLEND_IGNORE_TOGGLE,     // ブレンド無視モードON/OFF
  BLEND_TO_0,              // blend率を0に
  BLEND_DOWN,              // blend率を少しずつ下げる
  BLEND_SPEED_3X,          // 押してるときはblend率上げ下げの速度が3倍
  BLEND_UP,                // blend率を少しずつ上げる
  BLEND_TO_100,            // blend率を100に
  TO_DEFAULT_P2,           // デフォルトレイヤー切り替え＆プレイリスト2選択
};


int long_tap_timer;
static uint16_t led_update_timer = 0;
static uint8_t pending_led_update = 0;
static bool pending_default_led = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DEFAULT] = LAYOUT(
    PL1_BLEND, PREV_VIDEO, REWIND_15S, REWIND_1S, PLAY_STOP, FORWARD_5S, FORWARD_15S, NEXT_VIDEO, PLAYLIST2
  ),

  [_BLEND] = LAYOUT(
    TO_DEFAULT_P1, BLEND_IGNORE_TOGGLE, BLEND_TO_0, BLEND_DOWN, BLEND_SPEED_3X, BLEND_UP, BLEND_TO_100, KC_NO, TO_DEFAULT_P2
  ),
};


int aqours_color_h[] = { 26, 340, 150,   0, 199, 220, 53, 265, 322};
int aqours_color_s[] = {255, 165, 255, 255, 255, 350, 255, 255, 255};
int aqours_color_v[] = {255, 255, 255, 255, 255, 255, 200, 255, 255};

// LED状態管理
static uint8_t current_playlist = 1; // 1: プレイリスト1, 2: プレイリスト2
static bool blend_ignore_mode = false;

// LED遅延更新用
static bool pending_blend_ignore_led = false;

void LED_playlist1_set(void) {
  // 全LEDを赤に
  for (int i = 0; i < 9; i++) {
    sethsv(0, 255, 255, (LED_TYPE *)&led[i]); // 赤
  }
  
  // ブレンド無視モードがONなら2番目のLEDを黄色に
  if (blend_ignore_mode) {
    sethsv(220, 255, 255, (LED_TYPE *)&led[7]);
  }
  
  rgblight_set();
}

void LED_playlist2_set(void) {
  // 全LEDを青に
  for (int i = 0; i < 9; i++) {
    sethsv(170, 255, 255, (LED_TYPE *)&led[i]); // 青（HSV: 170度）
  }
  
  // ブレンド無視モードがONなら2番目のLEDを黄色に
  if (blend_ignore_mode) {
    sethsv(220, 255, 255, (LED_TYPE *)&led[7]);
  }
  
  rgblight_set();
}

void LED_blend_layer_set(void) {
  // 全LEDを緑に
  for (int i = 0; i < 9; i++) {
    sethsv(85, 255, 255, (LED_TYPE *)&led[i]); // 緑（HSV: 85度）
  }
  
  // ブレンド無視モードがONなら2番目のLEDを黄色に
  if (blend_ignore_mode) {
    sethsv(220, 255, 255, (LED_TYPE *)&led[7]);
  }
  
  rgblight_set();
}

void LED_default_set(void) {
  if (current_playlist == 1) {
    LED_playlist1_set();
  } else {
    LED_playlist2_set();
  }
}


void LED_default_set_delayed(void) {
  pending_default_led = true;
  pending_led_update = 0;
  led_update_timer = timer_read();
}

void LED_blend_ignore_set_delayed(void) {
  pending_blend_ignore_led = true;
  led_update_timer = timer_read();
}

// Raw HID送信用のヘルパー関数
void send_hid_control_message(uint8_t button_id, uint8_t value) {
  uint8_t data[32] = {0}; // 32バイトバッファを0で初期化
  
  data[0] = 0x01;        // メッセージタイプ（コントロール）
  data[1] = button_id;   // ボタンID (1-15)
  data[2] = value;       // 値 (0 or 127)
  data[3] = 0x00;        // 予約
  
  raw_hid_send(data, 32);
}

// Raw HID受信処理（将来のElectron→QMK通信用）
void raw_hid_receive(uint8_t *data, uint8_t length) {
  if (length != 32) return;
  
  // 受信データ処理（例：LED制御など）
  if (data[0] == 0x02) { // LEDコントロール
    // 将来的にElectronからLED制御を受信する場合
  }
}


// カスタムTap-Hold処理用
static uint16_t pl1_blend_timer = 0;
static bool pl1_blend_pressed = false;
static bool pl1_blend_hold_triggered = false;
#define TAPPING_TERM_PL1 300  // 300ms でタップ/ホールドを判定

// BLEND制御用
static bool blend_down_pressed = false;
static bool blend_up_pressed = false;
static uint16_t blend_control_timer = 0;
#define BLEND_CONTROL_INTERVAL 50  // 50ms間隔でBLEND値を変更

// レイヤー状態変化検知
layer_state_t layer_state_set_user(layer_state_t state) {
  if (IS_LAYER_ON_STATE(state, _BLEND)) {
    // ブレンドレイヤーがアクティブになった
    LED_blend_layer_set();
  } else {
    // デフォルトレイヤーに戻った
    LED_default_set();
  }
  return state;
}

void keyboard_post_init_user(void) {
    current_playlist = 1;      // プレイリスト1をデフォルト選択
    blend_ignore_mode = false; // ブレンド無視モード初期値OFF
    LED_default_set();
    layer_clear();             // 念のため全レイヤーをクリア
    layer_on(_DEFAULT);        // デフォルトレイヤーを確実にオン
}
// カスタムTap-Hold処理
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PL1_BLEND:
      if (record->event.pressed) {
        // キーが押された：タイマー開始
        pl1_blend_timer = timer_read();
        pl1_blend_pressed = true;
        pl1_blend_hold_triggered = false;
      } else {
        // キーが離された
        pl1_blend_pressed = false;
        
        if (!pl1_blend_hold_triggered) {
          // ホールドがトリガーされていない = 短押し（タップ）
          current_playlist = 1;
          send_hid_control_message(1, 127);
          LED_default_set_delayed();
          // すぐにリリースイベント送信
          send_hid_control_message(1, 0);
        }
        // ホールドがトリガーされている場合は何もしない（既にブレンドレイヤー）
      }
      return false;
      
    case PLAYLIST2:
      if (record->event.pressed) {
        current_playlist = 2;
        send_hid_control_message(9, 127);
        LED_default_set_delayed();
      } else {
        send_hid_control_message(9, 0);
      }
      break;
      
    case PREV_VIDEO:
      if (record->event.pressed) {
        send_hid_control_message(2, 127);
      } else {
        send_hid_control_message(2, 0);
      }
      break;
      
    case REWIND_15S:
      if (record->event.pressed) {
        send_hid_control_message(3, 127);
      } else {
        send_hid_control_message(3, 0);
      }
      break;
      
    case REWIND_1S:
      if (record->event.pressed) {
        send_hid_control_message(4, 127);
      } else {
        send_hid_control_message(4, 0);
      }
      break;
      
    case PLAY_STOP:
      if (record->event.pressed) {
        send_hid_control_message(5, 127);
      } else {
        send_hid_control_message(5, 0);
      }
      break;
      
    case FORWARD_5S:
      if (record->event.pressed) {
        send_hid_control_message(6, 127);
      } else {
        send_hid_control_message(6, 0);
      }
      break;
      
    case FORWARD_15S:
      if (record->event.pressed) {
        send_hid_control_message(7, 127);
      } else {
        send_hid_control_message(7, 0);
      }
      break;
      
    case NEXT_VIDEO:
      if (record->event.pressed) {
        send_hid_control_message(8, 127);
      } else {
        send_hid_control_message(8, 0);
      }
      break;
      
    // ブレンドレイヤー用
    case TO_DEFAULT_P1:
      if (record->event.pressed) {
        layer_clear();
        layer_on(_DEFAULT);
        current_playlist = 1;
        send_hid_control_message(10, 127);
        // LEDは layer_state_set_user で自動設定される
      } else {
        send_hid_control_message(10, 0);
      }
      return false;
      
    case TO_DEFAULT_P2:
      if (record->event.pressed) {
        layer_clear();
        layer_on(_DEFAULT);
        current_playlist = 2;
        send_hid_control_message(18, 127);
        // LEDは layer_state_set_user で自動設定される
      } else {
        send_hid_control_message(18, 0);
      }
      return false;
      
    case BLEND_IGNORE_TOGGLE:
      if (record->event.pressed) {
        blend_ignore_mode = !blend_ignore_mode;
        send_hid_control_message(11, 127); // 常に127で送信（押された信号）
        LED_blend_ignore_set_delayed(); // 遅延LED更新
      }
      // リリースイベントは送信しない
      return false; // QMKの標準処理を完全にスキップ
      
    case BLEND_TO_0:
      if (record->event.pressed) {
        send_hid_control_message(12, 127);
      } else {
        send_hid_control_message(12, 0);
      }
      break;
      
    case BLEND_DOWN:
      if (record->event.pressed) {
        blend_down_pressed = true;
        blend_control_timer = timer_read();
        send_hid_control_message(13, 127); // 初回送信
      } else {
        blend_down_pressed = false;
        send_hid_control_message(13, 0);
      }
      break;
      
    case BLEND_SPEED_3X:
      if (record->event.pressed) {
        send_hid_control_message(14, 127);
      } else {
        send_hid_control_message(14, 0);
      }
      break;
      
    case BLEND_UP:
      if (record->event.pressed) {
        blend_up_pressed = true;
        blend_control_timer = timer_read();
        send_hid_control_message(15, 127); // 初回送信
      } else {
        blend_up_pressed = false;
        send_hid_control_message(15, 0);
      }
      break;
      
    case BLEND_TO_100:
      if (record->event.pressed) {
        send_hid_control_message(16, 127);
      } else {
        send_hid_control_message(16, 0);
      }
      break;

  }

  return true;
}



void matrix_scan_user(void) {

  if (long_tap_timer > 0) {
    long_tap_timer++;
  }

  // PL1_BLENDの長押し監視
  if (pl1_blend_pressed && !pl1_blend_hold_triggered) {
    if (timer_elapsed(pl1_blend_timer) >= TAPPING_TERM_PL1) {
      // 300ms経過：ホールドトリガー、ブレンドレイヤーに切り替え
      pl1_blend_hold_triggered = true;
      layer_clear();
      layer_on(_BLEND);
      // LEDは layer_state_set_user で自動処理される
    }
  }

  // BLEND_DOWN/UP連続制御
  if ((blend_down_pressed || blend_up_pressed) && timer_elapsed(blend_control_timer) >= BLEND_CONTROL_INTERVAL) {
    blend_control_timer = timer_read();
    
    if (blend_down_pressed) {
      send_hid_control_message(13, 127);
    }
    if (blend_up_pressed) {
      send_hid_control_message(15, 127);
    }
  }

  // 遅延LED更新処理 (HID送信から20ms後)
  if (timer_elapsed(led_update_timer) > 20) {
    if (pending_default_led) {
      LED_default_set();
      pending_default_led = false;
    } else if (pending_led_update > 0) {
      pending_led_update = 0;
    } else if (pending_blend_ignore_led) {
      // BLEND無視モードLED更新
      if (blend_ignore_mode) {
        sethsv(220, 255, 255, (LED_TYPE *)&led[7]); // 黄色に設定
      } else {
        // 現在のレイヤーに応じて元の色に戻す
        if (IS_LAYER_ON(_BLEND)) {
          sethsv(85, 255, 255, (LED_TYPE *)&led[7]); // ブレンドレイヤーの緑
        } else if (current_playlist == 1) {
          sethsv(0, 255, 255, (LED_TYPE *)&led[7]); // プレイリスト1の赤
        } else {
          sethsv(170, 255, 255, (LED_TYPE *)&led[7]); // プレイリスト2の青
        }
      }
      rgblight_set();
      pending_blend_ignore_led = false;
    }
  }
}
