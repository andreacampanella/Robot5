#include "mbed.h"
#include "USBHostXpad.h"

#define PLL0CFG_Val 0x00050077 // MSEL = 119, NSEL = 5 for 120MHz


//Remember to leave a valid bin file in the mbed disk

#define serial_debug

/*******************Variables*******************/

volatile int poll = 0;

int16_t Ly_value = 0;
int16_t Ry_value = 0;
int16_t Lx_value = 0;
int16_t Rx_value = 0;

int32_t Ly_value_old = 0;
int16_t Ry_value_old = 0;
int32_t Lx_value_old = 0;
int16_t Rx_value_old = 0;

uint8_t Ly_value_negative = 0;
uint8_t Ry_value_negative = 0;
uint8_t Lx_value_negative = 0;
uint8_t Rx_value_negative = 0;

uint8_t A_Value = 0;
uint8_t B_Value = 0;
uint8_t X_Value = 0;
uint8_t Y_Value = 0;
uint8_t RB_Value = 0;
uint8_t LB_Value = 0;

/*******************Declarations*******************/

#ifdef serial_debug
int g_buttons;
int g_stick_lx;
int g_stick_ly;
int g_stick_rx;
int g_stick_ry;
int g_trigger_l;
int g_trigger_r;
#endif

DigitalOut led_1(LED1);
DigitalOut led_2(LED2);
DigitalOut led_3(LED3);
DigitalOut led_4(LED4);

DigitalOut enable_M1(p21);
DigitalOut dir_M1(p22);

PwmOut Rpwm_M1(p23);
PwmOut Lpwm_M1(p24);

DigitalOut enable_M2(p27);
DigitalOut dir_M2(p28);
PwmOut Rpwm_M2(p25);
PwmOut Lpwm_M2(p26);

Serial pc(USBTX, USBRX); // tx, rx



/*******************Functions*******************/

uint16_t min(uint16_t a, uint16_t b, uint16_t c) {
  uint16_t m = a;
  if (m > b)
    m = b;
  if (m > c)
    m = c;
  return m;
}

float translate(float x, float in_min, float in_max, float out_min,
                float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//Event handler for the xpad task
void onXpadEvent(int buttons, int stick_lx, int stick_ly, int stick_rx,
                 int stick_ry, int trigger_l, int trigger_r) {

#ifdef serial_debug
  g_buttons = buttons;
  g_stick_lx = stick_lx;
  g_stick_ly = stick_ly;
  g_stick_rx = stick_rx;
  g_stick_ry = stick_ry;
  g_trigger_l = trigger_l;
  g_trigger_r = trigger_r;
#endif

  if (buttons == 256)  //LB
  {
    //wait_ms(250);
    LB_Value = !LB_Value;
  }

  if (buttons == 512)  //RB
  {
    //full stop
    enable_M1 = !enable_M1;
    enable_M2 = !enable_M2;
    led_2 = !led_2;
    RB_Value = !RB_Value;
  }

  if (buttons == 4096)  //A
  {
    A_Value = !A_Value;
  }

  if (buttons == 8192)  //B
  {
    B_Value = !B_Value;
    //switch between tank drive and relative drive

  }

  if (buttons == 16384)  //Y
  {
    Y_Value = !Y_Value;
  }

  if (buttons == 32768)  //X
  {
    X_Value = !X_Value;
  }

  //LEFT Y up down

  if (stick_ly <= 4000 && stick_ly >= -4000) {
    Ly_value = 0;
  } else if (stick_ly > 4000) {  //up
    Ly_value_negative = 0;
    Ly_value = stick_ly;
  } else if (stick_ly < -4000) {  //down
    Ly_value_negative = 1;
    Ly_value = stick_ly;
  }

  //RIGHT Y up down

  if (stick_ry <= 4000 && stick_ry >= -4000) {
    Ry_value = 0;
  } else if (stick_ry > 4000) {  //left
    Ry_value_negative = 0;
    Ry_value = stick_ry;
  } else if (stick_ry < -4000) {  //right
    Ry_value_negative = 1;
    Ry_value = stick_ry;
  }

  //LEFT X left right

  if (stick_lx <= 4000 && stick_lx >= -4000) {
    Lx_value = 0;
  } else if (stick_lx > 4000) {  //left
    Lx_value_negative = 0;
    Lx_value = stick_lx;
  } else if (stick_lx < -4000) {  //right
    Lx_value_negative = 1;
    Lx_value = stick_ly;
  }

  //RIGHT X left right

  if (stick_rx <= 4000 && stick_rx >= -4000) {
    Rx_value = 0;
  } else if (stick_rx > 4000) {  //up
    Rx_value_negative = 0;
    Rx_value = stick_rx;
  } else if (stick_rx < -4000) {  //down
    Rx_value_negative = 1;
    Rx_value = stick_rx;
  }

  poll = 0;
}

//Task for the xpad
void xpad_task(void const *) {
  USBHostXpad xpad;

  while (1) {

	if(!xpad.connected()){
		std::printf("Robot 5 : Pad not connected,connecting...\r\n");
		xpad.connect();
		Thread::wait(1000);
		poll++;
		if (poll > 2) {
			std::printf("Robot 5 : Pad not connected,restarting...\r\n");
			xpad.restart();
			poll = 0;
		}
	}
	else{
		xpad.led(USBHostXpad::LED1_ON);
		xpad.attachEvent(onXpadEvent);

	}


  }
}

/*******************Main*******************/

int main() {
	pc.baud(115200);
	led_4 = 1 ;
#ifdef serial_debug
	pc.printf("Robot 5 : Start. \r\n");
#endif

  Thread xpadTask(xpad_task, NULL, osPriorityNormal, 1024 * 4);

  dir_M1 = 1;
  dir_M2 = 1;

  Rpwm_M1.period_us(10);
  Lpwm_M1.period_us(10);

  Rpwm_M2.period_us(10);
  Lpwm_M2.period_us(10);

  while (1) {
    //Tank Drive use the two analog sticks , each one drive one belt.
    if (Ly_value_negative == 0)  //forward
    {
      Lpwm_M1 = 0;
      Rpwm_M1 = translate(Ly_value, 4000, 32767, 0.0, 1.0);
    } else {
      Rpwm_M1 = 0;
      Lpwm_M1 = translate(Ly_value, -4000, -32767, 0.0, 1.0);
    }
    if (Ry_value_negative == 0) {
      Lpwm_M2 = 0;
      Rpwm_M2 = translate(Ry_value, 4000, 32767, 0.0, 1.0);
    } else {
      Rpwm_M2 = 0;
      Lpwm_M2 = translate(Ry_value, -4000, -32767, 0.0, 1.0);
    }

    if (A_Value == 0) {

    }
    if (B_Value == 0) {

    }
    if (Y_Value == 0) {
    }
    if (X_Value == 0) {
    }
    if (LB_Value == 1) {

    }
    if (RB_Value == 1) {

    }

#ifdef serial_debug
    pc.printf("Xpad: %d %-5d %-5d %-5d %-5d %02x %02x\r\b", g_buttons,g_stick_lx, g_stick_ly, g_stick_rx, g_stick_ry, g_trigger_l,g_trigger_r);
#endif
  }
}
