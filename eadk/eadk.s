.cpu cortex-m7
.fpu fpv5-sp-d16
/*
FIXME: What does this do??
.eabi_attribute 27, 1
.eabi_attribute 28, 1
.eabi_attribute 20, 1
.eabi_attribute 21, 1
.eabi_attribute 23, 3
.eabi_attribute 24, 1
.eabi_attribute 25, 1
.eabi_attribute 26, 1
.eabi_attribute 30, 4
.eabi_attribute 34, 1
.eabi_attribute 18, 4
*/

.thumb
.thumb_func
.syntax unified
.global eadk_backlight_brightness
eadk_backlight_brightness:
  svc #1
  bx lr

.global eadk_backlight_set_brightness
eadk_backlight_set_brightness:
  push {r4, lr}
  svc #2
  mov r4, r0
  uxtb r0, r4
  pop {r4, pc}

.global eadk_battery_is_charging
eadk_battery_is_charging:
  push {r4, lr}
  svc #6
  mov r4, r0
  uxtb r0, r4
  pop {r4, pc}

.global eadk_battery_level
eadk_battery_level:
  push  {r4, lr}
  svc #7
  mov r4, r0
  uxtb r0, r4
  pop {r4, pc}

.global eadk_battery_voltage
eadk_battery_voltage:
  svc 8
  vmov ip, s0
  vmov s0, ip
  bx lr

.global eadk_display_push_rect_uniform
eadk_display_push_rect_uniform:
  sub sp, sp, #8
  add r3, sp, #8
  stmdb r3, {r0, r1}
  svc #18
  add sp, sp, #8
  bx lr

.global eadk_keyboard_scan
eadk_keyboard_scan:
  movs r2, #0
  movs r3, #0
  push {r4, lr}
  mov r4, r0
  strd r2, r3, [r0]
  mov r0, r4
  svc #37
  mov r0, r4
  pop {r4, pc}

.global eadk_keyboard_pop_state
eadk_keyboard_pop_state:
  push {r0, r1, r2, r4, r5, lr}
  movs r3, #0
  movs r2, #0
  mov r4, r0
  mov r5, sp
  strd r2, r3, [sp]
  mov r0, r5
  svc #31
  ldrd r2, r3, [r5]
  mov r0, r4
  strd r2, r3, [r4]
  add sp, #12
  pop {r4, r5, pc}

.global eadk_timing_usleep
eadk_timing_usleep:
  svc #53
  bx lr

.global eadk_timing_msleep
eadk_timing_msleep:
   svc #52
   bx lr

.global eadk_timing_millis
eadk_timing_millis:
  push {r0, r1, r4, lr}
  mov r4, sp
  svc #51
  str r0, [r4, #0]
  str r1, [r4, #4]
  movs r0, #0
  movs r1, #0
  add sp, #8
  pop {r4, pc}

.global eadk_timing_usb_is_plugged
eadk_timing_usb_is_plugged:
push {r4, lr}
   svc #55
   mov r4, r0
   uxtb r0, r4
   pop {r4, pc}

.global eadk_random
eadk_random:
  push {r4, lr}
  svc #43
  mov r4, r0
  pop {r4, pc}
