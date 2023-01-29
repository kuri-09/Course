/*マクロ定義*/


/*マクロ*/
#define FILTER 0.9
#define SECOND 1000

/*PID制御*/
#define KC 20.0 //比例ゲイン
#define TC 3.6 //周期
#define T 0.1

#define KP (0.6 * (KC))
#define TI (0.5 * (TC))
#define TD (0.125 * (TC))
