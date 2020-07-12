#include "lib.h"

#include "olcConsoleGameEngine.h"

#include <memory>
#include <cassert>

class olcConsoleGameEngineImpl : public olc::olcConsoleGameEngine
{
public:
	olcConsoleGameEngineImpl() = default;

	void RegisterCreate(create_fn fn) {
		create_fn_ = fn;
	}

	void RegisterUpdate(update_fn fn) {
		update_fn_ = fn;
	}

private:
	bool OnUserCreate() override
	{
		return create_fn_();
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		return update_fn_(fElapsedTime);
	}

	create_fn create_fn_;
	update_fn update_fn_;
};

std::unique_ptr<olcConsoleGameEngineImpl> g_engine = nullptr;

extern "C" 
{
	int olc_initialize(int width, int height, int fontw, int fonth) {
		g_engine = std::make_unique<olcConsoleGameEngineImpl>();
		return static_cast<int>(g_engine->ConstructConsole(width, height, fontw, fonth));
	}

	int olc_screen_width() {
		return g_engine->ScreenWidth();
	}

	int olc_screen_height() {
		return g_engine->ScreenHeight();
	}

	void olc_register_create(create_fn fn) {
		g_engine->RegisterCreate(fn);
	}

	void olc_register_update(update_fn fn) {
		g_engine->RegisterUpdate(fn);
	}

	void olc_start() {
		g_engine->Start();
	}

	void olc_deinitialize() {
		g_engine = nullptr;
	}

	void olc_draw(int x, int y, short ch, short col) {
		g_engine->Draw(x, y, ch, col);
	}

	void olc_fill(int x1, int y1, int x2, int y2, short ch, short col) {
		g_engine->Fill(x1, y1, x2, y2, ch, col);
	}

	void olc_draw_string(int x, int y, const char* str, short col) {
		size_t size = strlen(str);
		assert(size < 64536); // sanity check
		g_engine->DrawString(x, y, std::wstring(str, str+size), col);
	}

	key_state_t olc_get_key(int id) {
		olc::olcConsoleGameEngine::sKeyState eng_state = g_engine->GetKey(id);
		key_state_t state;
		state.held = eng_state.bHeld;
		state.pressed = eng_state.bPressed;
		state.released = eng_state.bReleased;
		return state;
	}
}
