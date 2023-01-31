/*controll_objct.h*/

/*関数プロトタイプ宣言*/


/*ポンプ(Pump.c)*/
void Pump_drain_water();
void Pump_stop_drain();


/*給湯口*/


/*ランプ*/
/*沸騰(boil)*/
void BoilLamp_turn_on_lamp();
void BoilLamp_turn_off_lamp();

/*保温(keep)*/
void KeepWarmLamp_turn_on_lamp();
void KeepWarmLamp_turn_off_lamp();

/*ロック(lock)*/
void LockLamp_turn_on_lamp();
void LockLamp_turn_off_lamp();


/*水位(water_level)*/
void WaterLevelMeter_show_water_level(unsigned char display_water_level);

/*ブザー*/
void Buzzer_turn_on();
void Buzzer_turn_on_enable();
void Buzzer_turn_off();
void Buzzer_turn_off_enable();
void Buzzer_ring_buzzer(int times);


/*ヒータ*/
void Heater_control(unsigned char power);
void Heater_boil();
void Heater_keep();


/*ヒータ電源*/
void HeaterPower_turn_on();
void HeaterPower_turn_off();


/*ディスプレイ*/
/*timer_display*/
/*
void RTimeDisp_show_remaining_time(int remaining_time);
void RTimeDisp_show_one_time(unsigned char one_time);
void RTimeDisp_show_ten_time(unsigned char ten_time);
*/                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          