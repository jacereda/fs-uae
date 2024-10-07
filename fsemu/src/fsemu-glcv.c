#if defined FSEMU_GLCV
#define FSEMU_INTERNAL
#include "fsemu-glcv.h"
#include "fsemu-controller.h"
#include "fsemu-screenshot.h"
#include "fsemu-video.h"
#include "fsemu-window.h"
#include "fsemu-layout.h"
#include "fsemu-titlebar.h"
#include "fsemu-monitor.h"
#include "fsemu-mouse.h"
#include "fsemu-time.h"
#include "fsemu-glvideo.h"
#include "glad/glad.h"
#include <dlfcn.h>


#if !defined FSEMU_SDL
void fsemu_controller_init(void)
{
}

void fsemu_controller_update(void)
{
}

void fsemu_screenshot_capture_video_frame(fsemu_video_frame_t *frame)
{
}
#endif

#define CV_EXPLICIT_ENTRY
#define CV_NO_MAIN
#include "../../glcv/src/xlib.c"
//#include "../../glcv/src/wl.c"

#include "fsemu-glcv.h"
#include "fsemu-thread.h"

static void resize(int w, int h) {
	fsemu_window_set_size_2(w, h);
	fsemu_video_set_size_2(w, h);
	fsemu_layout_set_size_2(w, h);
}

static void motion(int x, int y) {
	static int lastx, lasty;
	fsemu_mouse_event_t me = {
		.moved = true,
		.x = x,
		.y = y,
		.rel_x = x - lastx,
		.rel_y = y - lasty,
	};
	/* if (!fsemu_titlebar_use_system()) { */
	/*     fsemu_sdlwindow_handle_cursor(&mouse_event); */
	/* } */
	fsemu_mouse_handle_mouse(&me);
	lastx = x;
	lasty = y;
}

static void mouse(bool state, enum mousebutton button) {
	fsemu_mouse_event_t me = {
		.button = button,
		.state = state,
	};
	fsemu_mouse_handle_mouse(&me);
}

static int down(cvkey k) {
	int handled = 0;
	switch (k) {
	case CVK_MOUSELEFT: mouse(true, FSEMU_MOUSE_LEFT); break;
	case CVK_MOUSEMIDDLE: mouse(true, FSEMU_MOUSE_MIDDLE); break;
	case CVK_MOUSERIGHT: mouse(true, FSEMU_MOUSE_RIGHT); break;
	}
	return handled;
}

static int up(cvkey k) {
        int handled = 0;
        switch (k) {
	case CVK_MOUSELEFT: mouse(false, FSEMU_MOUSE_LEFT); break;
	case CVK_MOUSEMIDDLE: mouse(false, FSEMU_MOUSE_MIDDLE); break;
	case CVK_MOUSERIGHT: mouse(false, FSEMU_MOUSE_RIGHT); break;
        case CVK_ESCAPE: cvQuit(); break;
        case CVK_F: cvFullscreen(); break;
        case CVK_W: cvWindowed(); break;
        default: handled = 0; break;
        }
        return handled;
}

static void* gpa(const char *name) {
	static void * gl;
	if (!gl)
		gl = dlopen("libGL.so", RTLD_LAZY);
	return dlsym(gl, name);
}

extern volatile int fsemu_frame_number_displaying;


static intptr_t handler(const ev * e) {
	static int last;
	TracyCZone(z, true);
	static const int iw = 1280;
	static const int ih = 720;
        intptr_t ret = 1;
        cveventtype t = evType(e);
        switch (t) {
	case CVE_GLINIT:
		gladLoadGLLoader((GLADloadproc)gpa);
		gladLoadGL();
		resize(iw, ih);
		break;
        case CVE_UPDATE:
 		ret = fsemu_frame_number_displaying > last;
		last = fsemu_frame_number_displaying;
		break;
        case CVE_RESIZE: resize(evWidth(e), evHeight(e)); break;
        case CVE_MOTION: motion(evX(e), evY(e)); break;
        case CVE_DOWN: ret = down(evWhich(e)); break;
	case CVE_UP: ret = up(evWhich(e)); break;
        case CVQ_WIDTH: ret = iw; break;
        case CVQ_HEIGHT: ret = ih; break;
        default: ret = 0; break;
        }


	TracyCZoneEnd(z);

        return ret;
}

void fsemu_glcv_init(void) {
	char ** argv = {0};
	event = handler;
	cvinit(0, argv);
	fsemu_titlebar_init();
	fsemu_monitor_init();

}

void fsemu_glcv_work(void) {
	cvtick();
}
#endif
