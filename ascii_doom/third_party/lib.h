#ifndef OLC_LIB_INTERFACE_H_
#define OLC_LIB_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	int pressed;
	int released;
	int held;
} key_state_t;

typedef int (*create_fn)();
typedef int (*update_fn)(float);

int olc_initialize(int width, int height, int fontw, int fonth);
int olc_screen_width();
int olc_screen_height();
void olc_register_create(create_fn fn);
void olc_register_update(update_fn fn);
void olc_start();
void olc_deinitialize();
void olc_draw(int x, int y, short ch, short col);
void olc_fill(int x1, int y1, int x2, int y2, short ch, short col);
void olc_draw_string(int x, int y, const char* str, short col);

/**
 * @brief Получение состояния клавиши
 * @param id Идентификатор клавиши (https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)
*/
key_state_t olc_get_key(int id);

enum COLOR
{
    FG_BLACK		= 0x0000,
    FG_DARK_BLUE    = 0x0001,	
    FG_DARK_GREEN   = 0x0002,
    FG_DARK_CYAN    = 0x0003,
    FG_DARK_RED     = 0x0004,
    FG_DARK_MAGENTA = 0x0005,
    FG_DARK_YELLOW  = 0x0006,
    FG_GREY			= 0x0007,
    FG_DARK_GREY    = 0x0008,
    FG_BLUE			= 0x0009,
    FG_GREEN		= 0x000A,
    FG_CYAN			= 0x000B,
    FG_RED			= 0x000C,
    FG_MAGENTA		= 0x000D,
    FG_YELLOW		= 0x000E,
    FG_WHITE		= 0x000F,
    BG_BLACK		= 0x0000,
    BG_DARK_BLUE	= 0x0010,
    BG_DARK_GREEN	= 0x0020,
    BG_DARK_CYAN	= 0x0030,
    BG_DARK_RED		= 0x0040,
    BG_DARK_MAGENTA = 0x0050,
    BG_DARK_YELLOW	= 0x0060,
    BG_GREY			= 0x0070,
    BG_DARK_GREY	= 0x0080,
    BG_BLUE			= 0x0090,
    BG_GREEN		= 0x00A0,
    BG_CYAN			= 0x00B0,
    BG_RED			= 0x00C0,
    BG_MAGENTA		= 0x00D0,
    BG_YELLOW		= 0x00E0,
    BG_WHITE		= 0x00F0,
};

#ifdef __cplusplus
}
#endif

#endif // !OLC_LIB_INTERFACE_H_
