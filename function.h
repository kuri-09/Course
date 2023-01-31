/*function.h*/

/*�֐��v���g�^�C�v�錾*/

/*�����@�\*/
void BoilFunction_boil(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER);

/*�ۉ��@�\*/
void KeepWarmFunction_keep_warm(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER);
double KeepWarmFunction_calculate_power(double before_temp, double pid_temp, unsigned int target_temp, unsigned char is_first);

/*�����@�\*/
void SupplyWaterFunction_supply_water(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER);

/*�L�b�`���^�C�}�@�\*/
void KitchenTimerFunction_timer(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER);

/*�G���[*/
void Error_check_error(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER, ERROR_CLASS *ERROR);

