/*function.h*/

/*�֐��v���g�^�C�v�錾*/


/*�����@�\*/
void BoilFunction_boil(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *STATE);

/*�ۉ��@�\*/
void KeepWarmFunction_keep_warm(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *STATE);
double KeepWarmFunction_calculate_power();

/*�����@�\*/
void SupplyWaterFunction_supply_water(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *STATE);

/*�L�b�`���^�C�}�@�\*/
void KitchenTimerFunction_timer(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *STATE);

/*�G���[*/
void Error_check_error(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER, ERROR_CLASS *ERROR);

