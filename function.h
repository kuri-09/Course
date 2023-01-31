/*function.h*/

/*関数プロトタイプ宣言*/

/*沸騰機能*/
void BoilFunction_boil(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER);

/*保温機能*/
void KeepWarmFunction_keep_warm(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER);
double KeepWarmFunction_calculate_power(double before_temp, double pid_temp, unsigned int target_temp, unsigned char is_first);

/*給湯機能*/
void SupplyWaterFunction_supply_water(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER);

/*キッチンタイマ機能*/
void KitchenTimerFunction_timer(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER);

/*エラー*/
void Error_check_error(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER, ERROR_CLASS *ERROR);

