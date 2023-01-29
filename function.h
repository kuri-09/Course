/*function.h*/

/*関数プロトタイプ宣言*/


/*沸騰機能*/
void BoilFunction_boil(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *STATE);

/*保温機能*/
void KeepWarmFunction_keep_warm(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *STATE);
double KeepWarmFunction_calculate_power();

/*給湯機能*/
void SupplyWaterFunction_supply_water(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *STATE);

/*キッチンタイマ機能*/
void KitchenTimerFunction_timer(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *STATE);

/*エラー*/
void Error_check_error(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER, ERROR_CLASS *ERROR);

